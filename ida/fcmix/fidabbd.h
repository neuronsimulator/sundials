/*
 * -----------------------------------------------------------------
 * $Revision: 1.5 $
 * $Date: 2005-08-15 18:06:46 $
 * ----------------------------------------------------------------- 
 * Programmer(s): Aaron Collier @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2005, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see sundials/ida/LICENSE.
 * -----------------------------------------------------------------
 * This is the Fortran interface include file for the BBD
 * preconditioner (IDABBDPRE)
 * -----------------------------------------------------------------
 */

/*
 * ==============================================================================
 *
 *                   FIDABBD Interface Package
 *
 * The FIDABBD Interface Package is a package of C functions which,
 * together with the FIDA Interface Package, support the use of the
 * IDA solver (parallel MPI version) with the IDABBDPRE preconditioner module,
 * for the solution of DAE systems in a mixed Fortran/C setting.  The
 * combination of IDA and IDABBDPRE solves DAE systems with the SPGMR
 * (scaled preconditioned GMRES), SPBCG (scaled preconditioned Bi-CGSTAB), or
 * SPTFQMR (scaled preconditioned TFQMR) method for the linear systems that arise,
 * and with a preconditioner that is block-diagonal with banded blocks.  While
 * IDA and IDABBDPRE are written in C, it is assumed here that the user's
 * calling program and user-supplied problem-defining routines are written in
 * Fortran.
 *
 * The user-callable functions in this package, with the corresponding
 * IDA and IDABBDPRE functions, are as follows: 
 *   FIDABBDININT   interfaces to IDABBDPrecAlloc
 *   FIDABBDSPGMR   interfaces to IDABBDSpgmr and IDASpgmrSet*
 *   FIDABBDSPBCG   interfaces to IDABBDSpbcg and IDASpbcgSet*
 *   FIDABBDSPTFQMR interfaces to IDABBDSptfqmr and IDASptfqmrSet*
 *   FIDABBDREINIT  interfaces to IDABBDPrecReInit
 *   FIDABBDOPT     accesses optional outputs
 *   FIDABBDFREE    interfaces to IDABBDPrecFree
 *
 * In addition to the Fortran residual function FIDARESFUN, the
 * user-supplied functions used by this package, are listed below,
 * each with the corresponding interface function which calls it (and its
 * type within IDABBDPRE or IDA):
 *   FIDAGLOCFN  is called by the interface function FIDAgloc of type IDABBDLocalFn
 *   FIDACOMMFN  is called by the interface function FIDAcfn of type IDABBDCommFn
 *   FIDAJTIMES  (optional) is called by the interface function FIDAJtimes of 
 *               type IDASpilsJacTimesVecFn
 * (The names of all user-supplied routines here are fixed, in order to
 * maximize portability for the resulting mixed-language program.)
 *
 * Important note on portability:
 * In this package, the names of the interface functions, and the names of
 * the Fortran user routines called by them, appear as dummy names
 * which are mapped to actual values by a series of definitions in the
 * header file fidabbd.h.
 *
 * ==============================================================================
 *
 *               Usage of the FIDA/FIDABBD Interface Packages
 *
 * The usage of the combined interface packages FIDA and FIDABBD requires
 * calls to several interface functions, and a few different user-supplied
 * routines which define the problem to be solved and indirectly define
 * the preconditioner.  These function calls and user routines are
 * summarized separately below.
 *
 * Some details are omitted, and the user is referred to the IDA user document 
 * for more complete information.
 *
 * (1) User-supplied residual routine: FIDARESFUN
 * The user must in all cases supply the following Fortran routine
 *       SUBROUTINE FIDARESFUN (T, Y, YP, R, IER)
 *       INTEGER IER
 *       DIMENSION T, Y(*), YP(*), R(*)
 * It must set the R array to F(t,y,y'), the residual of the DAE 
 * system, as a function of T = t, the array Y = y, and the array YP = y'.
 * Here Y, YP and R are distributed vectors.
 *
 * (2) User-supplied routines to define preconditoner: FIDAGLOCFN and FIDACOMMFN
 *
 * The routines in the IDABBDPRE module provide a preconditioner matrix
 * for IDA that is block-diagonal with banded blocks.  The blocking
 * corresponds to the distribution of the dependent variable vectors y and y'
 * among the processes.  Each preconditioner block is generated from the
 * Jacobian of the local part (associated with the current process) of a given
 * function G(t,y,y') approximating F(t,y,y').  The blocks are generated by a
 * difference quotient scheme independently by each process, utilizing
 * an assumed banded structure with given half-bandwidths.  A separate
 * pair of half-bandwidths defines the band matrix retained.
 *
 * (2.1) Local approximate function FIDAGLOCFN.
 * The user must supply a subroutine of the form
 *       SUBROUTINE FIDAGLOCFN (NLOC, T, YLOC, YPLOC, GLOC, IER)
 *       INTEGER NLOC, IER
 *       DIMENSION T, YLOC(*), YPLOC(*), GLOC(*)
 * to compute the function G(t,y,y') which approximates the residual
 * function F(t,y,y').  This function is to be computed locally, i.e., without 
 * interprocess communication.  (The case where G is mathematically
 * identical to F is allowed.)  It takes as input the local vector length
 * NLOC, the independent variable value T = t, and the local realtype
 * dependent variable arrays YLOC and YPLOC.  It is to compute the local part
 * of G(t,y,y') and store this in the realtype array GLOC.
 *
 * (2.2) Communication function FIDACOMMF.
 * The user must also supply a subroutine of the form
 *       SUBROUTINE FIDACOMMFN (NLOC, T, YLOC, YPLOC, IER)
 *       INTEGER NLOC, IER
 *       DIMENSION T, YLOC(*), YPLOC(*)
 * which is to perform all interprocess communication necessary to
 * evaluate the approximate residual function G described above.
 * This function takes as input the local vector length NLOC, the
 * independent variable value T = t, and the local real dependent
 * variable arrays YLOC and YPLOC.  It is expected to save communicated
 * data in  work space defined by the user, and made available to FIDAGLOCFN.
 * Each call to the FIDACOMMFN is preceded by a call to FIDARESFUN with
 * the same (t,y,y') arguments.  Thus FIDACOMMFN can omit any
 * communications done by FIDARESFUN if relevant to the evaluation of G.
 *
 * (3) Optional user-supplied Jacobian-vector product routine: FIDAJTIMES
 * As an option when using the SPGMR/SPBCG/SPTFQMR linear solver, the user may
 * supply a routine that computes the product of the system Jacobian J = df/dy
 * and a given vector v.  If supplied, it must have the following form:
 *       SUBROUTINE FIDAJTIMES (T, Y, YP, R, V, FJV, CJ, EWT, H, WK1, WK2, IER)
 *       INTEGER IER
 *       DIMENSION T, V(*), FJV(*), Y(*), YP(*), R(*), CJ, H, EWT(*),
 *      1          WK1(*), WK2(*)
 * This routine must compute the product vector Jv, where the vector v is stored
 * in V, and store the product in FJV.  On return, set IER = 0 if FIDAJTIMES was
 * successful, and nonzero otherwise.
 *
 * (4) Initialization:  FNVINITP, FIDAMALLOC, FIDABBDINIT.
 *
 * (4.1) To initialize the parallel machine environment, the user must make 
 * one of the following calls:
 *        CALL FNVINITP (KEY, NLOCAL, NGLOBAL, IER)
 *                     -or-
 *        CALL FNVINITP (COMM, KEY, NLOCAL, NGLOBAL, IER)
 * The arguments are:
 * COMM = MPI communicator (e.g., MPI_COMM_WORLD)
 * KEY = 3 for IDA
 * NLOCAL  = local size of vectors on this processor
 * NGLOBAL = the system size, and the global size of vectors (the sum 
 *           of all values of NLOCAL)
 * IER     = return completion flag. Values are 0 = success, -1 = failure.
 * NOTE: The COMM argument passed to the FNVINITP routine is only supported if
 * the MPI implementation used to build SUNDIALS includes the MPI_Comm_f2c
 * function from the MPI-2 specification.  To check if the function is supported
 * look for the line "#define SUNDIALS_MPI_COMM_F2C 1" in the sundials_config.h
 * header file.
 *
 * (4.2) To set various problem and solution parameters and allocate
 * internal memory, make the following call:
 *       CALL FIDAMALLOC(T0, Y0, YP0, IATOL, RTOL, ATOL, ID, CONSTR,
 *      1                IOUT, ROUT, IER)
 * The arguments are:
 * T0    = initial value of t
 * Y0    = array of initial conditions, y(t0)
 * YP0   = value of y'(t0)
 * IATOL = type for absolute tolerance ATOL: 1 = scalar, 2 = array.
 *         If IATOL = 3, then the user must supply a routine FIDAEWT to compute
 *         the error weight vector.
 * RTOL  = relative tolerance (scalar)
 * ATOL  = absolute tolerance (scalar or array)
 * IOUT  = array of length at least 21 for integer optional inputs and outputs
 *          (declare as INTEGER*4 or INTEGER*8 according to C type long int)
 * ROUT  = array of length 6 for real optional inputs and outputs
 *
 *         The optional outputs are:
 *
 *           LENRW   = IOUT( 1) -> IDAGetWorkSpace
 *           LENIW   = IOUT( 2) -> IDAGetWorkSpace
 *           NST     = IOUT( 3) -> IDAGetNumSteps
 *           NRE     = IOUT( 4) -> IDAGetNumResEvals
 *           NETF    = IOUT( 5) -> IDAGetNumErrTestFails
 *           NCFN    = IOUT( 6) -> IDAGetNumNonlinSolvConvFails
 *           NNI     = IOUT( 7) -> IDAGetNumNonlinSolvIters
 *           NSETUPS = IOUT( 8) -> IDAGetNumLinSolvSetups
 *           KLAST   = IOUT( 9) -> IDAGetLastOrder
 *           KCUR    = IOUT(10) -> IDAGetCurrentOrder
 *           NBCKTRK = IOUT(11) -> IDAGetNumBacktrackOps
 *           NGE     = IOUT(12) -> IDAGetNumGEvals
 *
 *           HINUSED = ROUT( 1) -> IDAGetActualInitStep
 *           HLAST   = ROUT( 2) -> IDAGetLastStep
 *           HCUR    = ROUT( 3) -> IDAGetCurrentStep
 *           TCUR    = ROUT( 4) -> IDAGetCurrentTime
 *           TOLSFAC = ROUT( 5) -> IDAGetTolScaleFactor
 *           UNITRND = ROUT( 6) -> UNIT_ROUNDOFF
 *
 * IER   = return completion flag.  Values are 0 = SUCCESS, and -1 = failure.
 *         See printed message for details in case of failure.
 *
 * If the user program includes the FIDAEWT routine for the evaluation of the 
 * error weights, the following call must be made
 *       CALL FIDAEWTSET (FLAG, IER)
 * with FLAG = 1 to specify that FIDAEWT is provided.
 * The return flag IER is 0 if successful, and nonzero otherwise.
 *
 * (4.3) To allocate memory and initialize data associated with the IDABBDPRE
 * preconditioner, make the following call:
 *       CALL FIDABBDINIT(NLOCAL, MUDQ, MLDQ, MU, ML, DQRELY, IER)
 * The arguments are:
 * NLOCAL    = local size of vectors
 * MUDQ,MLDQ = upper and lower half-bandwidths to be used in the computation
 *             of the local Jacobian blocks by difference quotients.
 *             These may be smaller than the true half-bandwidths of the
 *             Jacobian of the local block of g, when smaller values may
 *             provide greater efficiency.
 * MU, ML    = upper and lower half-bandwidths of the band matrix that 
 *             is retained as an approximation of the local Jacobian block.
 *             These may be smaller than MUDQ and MLDQ.
 * DQRELY    = relative increment factor in y for difference quotients
 *             (optional). 0.0 indicates the default, sqrt(UNIT_ROUNDOFF).
 * IER       = return completion flag: IER=0: success, IER<0: an error occured
 *
 * (4.4A) To specify the SPTFQMR linear system solver and use it with the IDABBDPRE
 * preconditioner, make the following call:
 *       CALL FIDABBDSPTFQMR(MAXL, EPLIFAC, DQINCFAC, IER)
 * the arguments are:
 * MAXL      = maximum Krylov subspace dimension; 0 indicates default.
 * EPLIFAC   = factor in the linear iteration convergence test constant
 * DQINCFAC  = factor in the increments to y used in the difference quotient
 *             approximations to matrix-vector products Jv
 * IER       = return completion flag: IER=0: success, IER<0: an error occured
 *
 * (4.4B) To specify the SPBCG linear system solver and use it with the IDABBDPRE
 * preconditioner, make the following call:
 *       CALL FIDABBDSPBCG(MAXL, EPLIFAC, DQINCFAC, IER)
 * the arguments are:
 * MAXL      = maximum Krylov subspace dimension; 0 indicates default.
 * EPLIFAC   = factor in the linear iteration convergence test constant
 * DQINCFAC  = factor in the increments to y used in the difference quotient
 *             approximations to matrix-vector products Jv
 * IER       = return completion flag: IER=0: success, IER<0: an error occured
 *
 * (4.4C) To specify the SPGMR linear system solver and use it with the IDABBDPRE
 * preconditioner, make the following call:
 *       CALL FIDABBDSPGMR(MAXL, IGSTYPE, MAXRS, EPLIFAC, DQINCFAC, IER)
 *
 * the arguments are:
 * MAXL      = maximum Krylov subspace dimension; 0 indicates default.
 * IGSTYPE   = Gram-schmidt process type: 1 = modified G-S, 1 = classical G-S.
 * MAXRS     = maximum number of GMRES restarts
 * EPLIFAC   = factor in the linear iteration convergence test constant
 * DQINCFAC  = factor in the increments to y used in the difference quotient
 *             approximations to matrix-vector products Jv
 * IER       = return completion flag: IER=0: success, IER<0: an error occured
 *
 * (4.5A) To specify whether TFQMR should use the supplied FIDAJTIMES or the 
 * internal finite difference approximation, make the call
 *        CALL FIDASPTFQMRSETJAC(FLAG, IER)
 * where FLAG=0 for finite differences approxaimtion or
 *       FLAG=1 to use the supplied routine FIDAJTIMES
 *
 * (4.5B) To specify whether Bi-CGSTAB should use the supplied FIDAJTIMES or the 
 * internal finite difference approximation, make the call
 *        CALL FIDASPBCGSETJAC(FLAG, IER)
 * where FLAG=0 for finite differences approxaimtion or
 *       FLAG=1 to use the supplied routine FIDAJTIMES
 *
 * (4.5C) To specify whether GMRES should use the supplied FIDAJTIMES or the 
 * internal finite difference approximation, make the call
 *        CALL FIDASPGMRSETJAC(FLAG, IER)
 * where FLAG=0 for finite differences approxaimtion or
 *       FLAG=1 to use the supplied routine FIDAJTIMES
 *
 * (5) Re-initialization: FIDAREINIT, FIDABBDREINIT
 * If a sequence of problems of the same size is being solved using the SPGMR or
 * SPBCG linear solver in combination with the IDABBDPRE preconditioner, then the
 * IDA package can be reinitialized for the second and subsequent problems
 * so as to avoid further memory allocation.  First, in place of the call
 * to FIDAMALLOC, make the following call:
 *       CALL FIDAREINIT(T0, Y0, YP0, IATOL, RTOL, ATOL, ID, CONSTR, IER)
 * The arguments have the same names and meanings as those of FIDAMALLOC.
 * FIDAREINIT performs the same initializations as FIDAMALLOC, but does no
 * memory allocation for IDA data structures, using instead the existing
 * internal memory created by the previous FIDAMALLOC call.  Following the call
 * to FIDAREINIT, a call to FIDABBDINIT may or may not be needed.  If the input
 * arguments are the same, no FIDABBDINIT call is needed.  If there is a change
 * in input arguments other than MU, ML or MAXL, then the user program should call
 * FIDABBDREINIT.  The arguments of the FIDABBDREINIT routine have the
 * same names and meanings as FIDABBDINIT.  Finally, if the value of MU, ML, or
 * MAXL is being changed, then a call to FIDABBDINIT must be made.
 *
 * (6) The solver: FIDASOLVE
 * To solve the DAE system, make the following call:
 *       CALL FIDASOLVE (TOUT, TRET, Y, YP, ITASK, IER)
 * The arguments are:
 * TOUT  = next value of t at which a solution is desired (input)
 * TRET  = value of t reached by the solver on output
 * Y     = array containing the computed solution on output
 * YP    = array containing current value of y'
 * ITASK = task indicator: 1 = normal mode (overshoot TOUT and interpolate)
 *         2 = one-step mode (return after each internal step taken)
 *         3 = normal tstop mode (like 1, but integration never proceeds past 
 *             TSTOP,  which must be specified through a call to FIDASETRIN
 *             using the key 'STOP_TIME'
 *         4 = one step tstop (like 2, but integration never goes past TSTOP)
 * IER   = completion flag: 0 = success, 1 = tstop return, 2 = root return, 
 *         values -1 ... -10 are various failure modes (see IDA manual).
 * The current values of the optional outputs are available in IOUT and ROUT.
 *
 * (7) Optional outputs: FIDABBDOPT
 * Optional outputs specific to the SPGMR/SPBCG/SPTFQMR solver are available 
 * in IOUT(13)...IOUT(21)
 *
 * To obtain the optional outputs associated with the IDABBDPRE module, make
 * the following call:
 *       CALL FIDABBDOPT (LENRPW, LENIPW, NGE)
 * The arguments returned are:
 * LENRPW = length of real preconditioner work space, in realtype words.
 *          This size is local to the current process.
 * LENIPW = length of integer preconditioner work space, in integer words.
 *          This size is local to the current process.
 * NGE    = number of G(t,y,y') evaluations (calls to FIDAGLOCFN) so far.
 *
 * (8) Memory freeing: FIDABBDFREE and FIDAFREE
 * To the free the internal memory created by the calls to FNVINITP,
 * FIDAMALLOC, and FIDABBDINIT, make the following calls, in this order:
 *       CALL FIDABBDFREE
 *       CALL FIDAFREE
 *
 * ==============================================================================
 */

#ifndef _FIDABBD_H
#define _FIDABBD_H

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

#include "nvector.h"
#include "sundialstypes.h"

#if defined(F77_FUNC)

#define FIDA_BBDINIT    F77_FUNC(fidabbdinit, FIDABBDINIT)
#define FIDA_BBDSPTFQMR F77_FUNC(fidabbdsptfqmr, FIDABBDSPTFQMR)
#define FIDA_BBDSPBCG   F77_FUNC(fidabbdspbcg, FIDABBDSPBCG)
#define FIDA_BBDSPGMR   F77_FUNC(fidabbdspgmr, FIDABBDSPGMR)
#define FIDA_BBDREINIT  F77_FUNC(fidabbdreinit, FIDABBDREINIT)
#define FIDA_BBDOPT     F77_FUNC(fidabbdopt, FIDABBDOPT)
#define FIDA_BBDFREE    F77_FUNC(fidabbdfree, FIDABBDFREE)
#define FIDA_GLOCFN     F77_FUNC(fidaglocfn, FIDAGLOCFN)
#define FIDA_COMMFN     F77_FUNC(fidacommfn, FIDACOMMFN)

#elif defined(SUNDIALS_UNDERSCORE_NONE) && defined(SUNDIALS_CASE_LOWER)

#define FIDA_BBDINIT    fidabbdinit
#define FIDA_BBDSPTFQMR fidabbdsptfqmr
#define FIDA_BBDSPBCG   fidabbdspbcg
#define FIDA_BBDSPGMR   fidabbdspgmr
#define FIDA_BBDREINIT  fidabbdreinit
#define FIDA_BBDOPT     fidabbdopt
#define FIDA_BBDFREE    fidabbdfree
#define FIDA_GLOCFN     fidaglocfn
#define FIDA_COMMFN     fidacommfn

#elif defined(SUNDIALS_UNDERSCORE_NONE) && defined(SUNDIALS_CASE_UPPER)

#define FIDA_BBDINIT    FIDABBDINIT
#define FIDA_BBDSPTFQMR FIDABBDSPTFQMR
#define FIDA_BBDSPBCG   FIDABBDSPBCG
#define FIDA_BBDSPGMR   FIDABBDSPGMR
#define FIDA_BBDREINIT  FIDABBDREINIT
#define FIDA_BBDOPT     FIDABBDOPT
#define FIDA_BBDFREE    FIDABBDFREE
#define FIDA_GLOCFN     FIDAGLOCFN
#define FIDA_COMMFN     FIDACOMMFN

#elif defined(SUNDIALS_UNDERSCORE_ONE) && defined(SUNDIALS_CASE_LOWER)

#define FIDA_BBDINIT    fidabbdinit_
#define FIDA_BBDSPTFQMR fidabbdsptfqmr_
#define FIDA_BBDSPBCG   fidabbdspbcg_
#define FIDA_BBDSPGMR   fidabbdspgmr_
#define FIDA_BBDREINIT  fidabbdreinit_
#define FIDA_BBDOPT     fidabbdopt_
#define FIDA_BBDFREE    fidabbdfree_
#define FIDA_GLOCFN     fidaglocfn_
#define FIDA_COMMFN     fidacommfn_

#elif defined(SUNDIALS_UNDERSCORE_ONE) && defined(SUNDIALS_CASE_UPPER)

#define FIDA_BBDINIT    FIDABBDINIT_
#define FIDA_BBDSPTFQMR FIDABBDSPTFQMR_
#define FIDA_BBDSPBCG   FIDABBDSPBCG_
#define FIDA_BBDSPGMR   FIDABBDSPGMR_
#define FIDA_BBDREINIT  FIDABBDREINIT_
#define FIDA_BBDOPT     FIDABBDOPT_
#define FIDA_BBDFREE    FIDABBDFREE_
#define FIDA_GLOCFN     FIDAGLOCFN_
#define FIDA_COMMFN     FIDACOMMFN_

#elif defined(SUNDIALS_UNDERSCORE_TWO) && defined(SUNDIALS_CASE_LOWER)

#define FIDA_BBDINIT    fidabbdinit__
#define FIDA_BBDSPTFQMR fidabbdsptfqmr__
#define FIDA_BBDSPBCG   fidabbdspbcg__
#define FIDA_BBDSPGMR   fidabbdspgmr__
#define FIDA_BBDREINIT  fidabbdreinit__
#define FIDA_BBDOPT     fidabbdopt__
#define FIDA_BBDFREE    fidabbdfree__
#define FIDA_GLOCFN     fidaglocfn__
#define FIDA_COMMFN     fidacommfn__

#elif defined(SUNDIALS_UNDERSCORE_TWO) && defined(SUNDIALS_CASE_UPPER)

#define FIDA_BBDINIT    FIDABBDINIT__
#define FIDA_BBDSPTFQMR FIDABBDSPTFQMR__
#define FIDA_BBDSPBCG   FIDABBDSPBCG__
#define FIDA_BBDSPGMR   FIDABBDSPGMR__
#define FIDA_BBDREINIT  FIDABBDREINIT__
#define FIDA_BBDOPT     FIDABBDOPT__
#define FIDA_BBDFREE    FIDABBDFREE__
#define FIDA_GLOCFN     FIDAGLOCFN__
#define FIDA_COMMFN     FIDACOMMFN__

#endif

/* Prototypes of exported functions */

void FIDA_BBDINIT(long int *Nloc, long int *mudq, long int *mldq,
		  long int *mu, long int *ml, realtype *dqrely, int *ier);
void FIDA_BBDSPTFQMR(int *maxl, realtype *eplifac, realtype *dqincfac, int *ier);
void FIDA_BBDSPBCG(int *maxl, realtype *eplifac, realtype *dqincfac, int *ier);
void FIDA_BBDSPGMR(int *maxl, int *gstype, int *maxrs,
		   realtype *eplifac, realtype *dqincfac, int *ier);
void FIDA_BBDREINIT(long int *Nloc, long int *mudq, long int *mldq,
		    realtype *dqrely, int *ier);
void FIDA_BBDOPT(long int *lenrpw, long int *lenipw, long int *nge);
void FIDA_BBDFREE(void);

/* Prototypes: Functions Called by the IDABBD Module */

int FIDAgloc(long int Nloc, realtype t, N_Vector yy, N_Vector yp,
	     N_Vector gval, void *res_data);
int FIDAcfn(long int Nloc, realtype t, N_Vector yy, N_Vector yp,
	    void *res_data);

void *IDABBD_Data;

#ifdef __cplusplus
}
#endif

#endif
