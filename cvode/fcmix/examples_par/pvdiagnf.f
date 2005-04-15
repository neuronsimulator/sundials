C     ----------------------------------------------------------------
C     $Revision: 1.12 $
C     $Date: 2005-04-15 00:40:32 $
C     ----------------------------------------------------------------
C     Diagonal ODE example. Nonstiff case: alpha = 10/NEQ.
C     ----------------------------------------------------------------
C
C Include MPI-Fortran header file for MPI_COMM_WORLD, MPI types.
C
      INCLUDE "mpif.h"
C
      INTEGER IER, MYPE, NPES, NOUT, LNST, LNFE, LNNI, LNCF, LNETF
      INTEGER METH, ITMETH, IATOL, INOPT, ITASK, IOUT
      INTEGER*4 NEQ, NLOCAL, I, NST, NFE, NNI, NCFN, NETF
      INTEGER*4 IOPT(40)
      DOUBLE PRECISION Y, ROPT, ATOL, RTOL, DTOUT, T, ALPHA, TOUT
      DOUBLE PRECISION ERMAX, ERRI, GERMAX
      DIMENSION Y(128), ROPT(40)
C
      DATA ATOL/1.0D-10/, RTOL/1.0D-5/, DTOUT/0.1D0/, NOUT/10/
      DATA LNST/4/, LNFE/5/, LNNI/7/, LNCF/8/, LNETF/9/
C
      COMMON /PCOM/ ALPHA, NLOCAL, MYPE
C
C Get NPES and MYPE.  Requires initialization of MPI.
      CALL MPI_INIT(IER)
      IF (IER .NE. 0) THEN
        WRITE(6,5) IER
 5      FORMAT(///' MPI_ERROR: MPI_INIT returned IER = ', I5)
        STOP
        ENDIF
      CALL MPI_COMM_SIZE(MPI_COMM_WORLD, NPES, IER)
      IF (IER .NE. 0) THEN
        WRITE(6,6) IER
 6      FORMAT(///' MPI_ERROR: MPI_COMM_SIZE returned IER = ', I5)
        CALL MPI_ABORT(MPI_COMM_WORLD, 1, IER)
        STOP
        ENDIF
      CALL MPI_COMM_RANK(MPI_COMM_WORLD, MYPE, IER)
      IF (IER .NE. 0) THEN
        WRITE(6,7) IER
 7      FORMAT(///' MPI_ERROR: MPI_COMM_RANK returned IER = ', I5)
        CALL MPI_ABORT(MPI_COMM_WORLD, 1, IER)
        STOP
        ENDIF
C
C Set input arguments.
      NLOCAL = 2
      NEQ = NPES * NLOCAL
      T = 0.0D0
      METH = 1
      ITMETH = 1
      IATOL = 1
      INOPT = 0
      ITASK = 1
c Set parameter ALPHA
      ALPHA  = 10.0D0 / NEQ
C
      DO 10 I = 1, NLOCAL
  10    Y(I) = 1.0D0
C
      IF (MYPE .EQ. 0) THEN
        WRITE(6,11) NEQ, ALPHA
  11    FORMAT('Diagonal test problem:'//' NEQ = ', I3, /
     1         ' parameter alpha = ', F8.3)
        WRITE(6,12)
  12    FORMAT(' ydot_i = -alpha*i * y_i (i = 1,...,NEQ)')
        WRITE(6,13) RTOL, ATOL
  13    FORMAT(' RTOL, ATOL = ', 2E10.1)
        WRITE(6,14)
  14    FORMAT(' Method is ADAMS/FUNCTIONAL')
        WRITE(6,15) NPES
  15    FORMAT(' Number of processors = ', I3//)
        ENDIF
C
      CALL FNVINITP(1, NLOCAL, NEQ, IER)
C
      IF (IER .NE. 0) THEN
        WRITE(6,20) IER
  20    FORMAT(///' SUNDIALS_ERROR: FNVINITP returned IER = ', I5)
        CALL MPI_FINALIZE(IER)
        STOP
        ENDIF
C
      CALL FCVMALLOC(T, Y, METH, ITMETH, IATOL, RTOL, ATOL,
     1               INOPT, IOPT, ROPT, IER)
C
      IF (IER .NE. 0) THEN
        WRITE(6,30) IER
  30    FORMAT(///' SUNDIALS_ERROR: FCVMALLOC returned IER = ', I5)
        CALL MPI_ABORT(MPI_COMM_WORLD, 1, IER)
        STOP
        ENDIF
C
C Loop through tout values, call solver, print output, test for failure.
      TOUT = DTOUT
      DO 70 IOUT = 1, NOUT
C
        CALL FCVODE(TOUT, T, Y, ITASK, IER)
C
        IF (MYPE .EQ. 0) WRITE(6,40) T, IOPT(LNST), IOPT(LNFE)
  40    FORMAT(' t = ', D10.2, 5X, 'no. steps = ', I5,
     &         '   no. f-s = ', I5)
C
        IF (IER .NE. 0) THEN
          WRITE(6,60) IER, IOPT(26)
  60      FORMAT(///' SUNDIALS_ERROR: FCVODE returned IER = ', I5, /,
     &           '                 Linear Solver returned IER = ', I5)
          CALL MPI_ABORT(MPI_COMM_WORLD, 1, IER)
          STOP
          ENDIF
C
        TOUT = TOUT + DTOUT
  70    CONTINUE
C
C Get max. absolute error in the local vector.
      ERMAX = 0.0D0
      DO 75 I = 1, NLOCAL
        ERRI  = Y(I) - EXP(-ALPHA * (MYPE * NLOCAL + I) * T)
        ERMAX = MAX(ERMAX, ABS(ERRI))
  75    CONTINUE
C Get global max. error from MPI_REDUCE call.
      CALL MPI_REDUCE(ERMAX, GERMAX, 1, MPI_DOUBLE_PRECISION, MPI_MAX,
     1                0, MPI_COMM_WORLD, IER)
      IF (IER .NE. 0) THEN
        WRITE(6,80) IER
  80    FORMAT(///' MPI_ERROR: MPI_REDUCE returned IER = ', I5)
        CALL MPI_ABORT(MPI_COMM_WORLD, 1, IER)
        STOP
        ENDIF
      IF (MYPE .EQ. 0) WRITE(6,85) GERMAX
  85  FORMAT(/'Max. absolute error is ', E10.2/)
C
C Print final statistics.
      NST = IOPT(LNST)
      NFE = IOPT(LNFE)
      NNI = IOPT(LNNI)
      NCFN = IOPT(LNCF)
      NETF = IOPT(LNETF)
      IF (MYPE .EQ. 0) WRITE (6,90) NST, NFE, NNI, NCFN, NETF
  90  FORMAT(/'Final statistics:'//
     &       ' number of steps = ', I5, 5X, /,
     &       ' number of f evals. = ', I5/
     &       ' number of nonlinear iters. = ', I5/
     &       ' number of nonlinear conv. failures = ', I3/
     &       ' number of error test failures = ', I3)
C
C Free the memory and finalize MPI.
      CALL FCVFREE
      CALL MPI_FINALIZE(IER)
      IF (IER .NE. 0) THEN
        WRITE(6,95) IER
 95     FORMAT(///' MPI_ERROR: MPI_FINALIZE returned IER = ', I5)
        STOP
        ENDIF
C
      STOP
      END
C
      SUBROUTINE FCVFUN(T, Y, YDOT)
C Routine for right-hand side function f
      IMPLICIT NONE
C
      INTEGER MYPE
      INTEGER*4 NLOCAL, I
      DOUBLE PRECISION Y, YDOT, ALPHA, T
      DIMENSION Y(*), YDOT(*)
C
      COMMON /PCOM/ ALPHA, NLOCAL, MYPE
C
      DO 10 I = 1, NLOCAL
  10    YDOT(I) = -ALPHA * (MYPE * NLOCAL + I) * Y(I)
C
      RETURN
      END
