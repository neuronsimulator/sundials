/*---------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds @ SMU
 *---------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2022, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 *---------------------------------------------------------------
 * Example problem:
 *
 * The following test simulates the Robertson problem,
 * corresponding to the kinetics of an autocatalytic reaction.
 * This is an ODE system with 3 components, Y = [u,v,w], satisfying
 * the equations,
 *    du/dt = -0.04*u + 1e4*v*w
 *    dv/dt = 0.04*u - 1e4*v*w - 3e7*v^2
 *    dw/dt = 3e7*v^2
 * for t in the interval [0.0, 1e11], with initial conditions
 * Y0 = [1,0,0].
 *
 * While integrating the system, we use the rootfinding feature
 * to find the times at which either u=1e-4 or w=1e-2.
 *
 * This program solves the problem with one of the solvers, ERK,
 * DIRK or ARK.  For DIRK and ARK, implicit subsystems are solved
 * using a Newton iteration with the dense SUNLinearSolver, and a
 * user-supplied Jacobian routine.
 *
 * 100 outputs are printed at equal intervals, and run statistics
 * are printed at the end.
 *---------------------------------------------------------------*/

/* Header files */
#include <stdio.h>
#include <math.h>
#include <arkode/arkode_arkstep.h>      /* prototypes for ARKStep fcts., consts */
#include <nvector/nvector_serial.h>     /* serial N_Vector types, fcts., macros */
#include <sunmatrix/sunmatrix_dense.h>  /* access to dense SUNMatrix            */
#include <sunlinsol/sunlinsol_dense.h>  /* access to dense SUNLinearSolver      */
#include <sundials/sundials_types.h>    /* defs. of 'realtype', 'sunindextype'  */

#if defined(SUNDIALS_EXTENDED_PRECISION)
#define GSYM "Lg"
#define ESYM "Le"
#define FSYM "Lf"
#else
#define GSYM "g"
#define ESYM "e"
#define FSYM "f"
#endif

/* User-supplied Functions Called by the Solver */
static int f(realtype t, N_Vector y, N_Vector ydot, void *user_data);
static int Jac(realtype t, N_Vector y, N_Vector fy, SUNMatrix J,
               void *user_data, N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);
static int g(realtype t, N_Vector y, realtype *gout, void *user_data);

/* Private function to check function return values */
static int check_flag(void *flagvalue, const char *funcname, int opt);

/* Main Program */
int main()
{
  /* general problem parameters */
  realtype T0 = RCONST(0.0);     /* initial time */
  realtype T1 = RCONST(0.4);     /* first output time */
  realtype TMult = RCONST(10.0); /* output time multiplication factor */
  int Nt = 12;                   /* total number of output times */
  sunindextype NEQ = 3;              /* number of dependent vars. */
  realtype reltol;
  int rootsfound[2];
  long int nst, nst_a, nfe, nfi, nsetups;
  long int nje, nfeLS, nni, ncfn, netf, nge;
  int flag, rtflag;              /* reusable error-checking flags */
  FILE *UFID;
  realtype t, tout;
  int iout;

  /* general problem variables */
  N_Vector y = NULL;             /* empty vector for storing solution */
  N_Vector atols = NULL;         /* empty vector for absolute tolerances */
  SUNMatrix A = NULL;            /* empty matrix for linear solver */
  SUNLinearSolver LS = NULL;     /* empty linear solver object */
  void *arkode_mem = NULL;       /* empty ARKode memory structure */

  /* set up the initial conditions */
  realtype u0 = RCONST(1.0);
  realtype v0 = RCONST(0.0);
  realtype w0 = RCONST(0.0);

  /* Create the SUNDIALS context object for this simulation */
  SUNContext ctx;
  flag = SUNContext_Create(NULL, &ctx);
  if (check_flag(&flag, "SUNContext_Create", 1)) return 1;

  /* Initial problem output */
  printf("\nRobertson ODE test problem (with rootfinding):\n");
  printf("    initial conditions:  u0 = %"GSYM",  v0 = %"GSYM",  w0 = %"GSYM"\n",u0,v0,w0);

  /* Initialize data structures */
  y = N_VNew_Serial(NEQ, ctx);        /* Create serial vector for solution */
  if (check_flag((void *) y, "N_VNew_Serial", 0)) return 1;
  atols = N_VClone(y);    /* Create serial vector absolute tolerances */
  if (check_flag((void *) atols, "N_VNew_Serial", 0)) return 1;
  NV_Ith_S(y,0) = u0;            /* Set initial conditions into y */
  NV_Ith_S(y,1) = v0;
  NV_Ith_S(y,2) = w0;

  /* Call ARKStepCreate to initialize the ARK timestepper module and
     specify the right-hand side function in y'=f(t,y), the inital time
     T0, and the initial dependent variable vector y.  Note: since this
     problem is fully implicit, we set f_E to NULL and f_I to f. */
  arkode_mem = ARKStepCreate(NULL, f, T0, y, ctx);
  if (check_flag((void *)arkode_mem, "ARKStepCreate", 0)) return 1;

  /* Set tolerances */
  reltol = RCONST(1.0e-4);
  NV_Ith_S(atols,0) = RCONST(1.0e-8);
  NV_Ith_S(atols,1) = RCONST(1.0e-11);
  NV_Ith_S(atols,2) = RCONST(1.0e-8);

  /* Set routines */
  flag = ARKStepSetMaxErrTestFails(arkode_mem, 20);        /* Increase max error test fails */
  if (check_flag(&flag, "ARKStepSetMaxErrTestFails", 1)) return 1;
  flag = ARKStepSetMaxNonlinIters(arkode_mem, 8);          /* Increase max nonlinear iterations  */
  if (check_flag(&flag, "ARKStepSetMaxNonlinIters", 1)) return 1;
  flag = ARKStepSetNonlinConvCoef(arkode_mem, 1.e-7);      /* Update nonlinear solver convergence coeff. */
  if (check_flag(&flag, "ARKStepSetNonlinConvCoef", 1)) return 1;
  flag = ARKStepSetMaxNumSteps(arkode_mem, 100000);        /* Increase max number of steps */
  if (check_flag(&flag, "ARKStepSetMaxNumSteps", 1)) return 1;
  flag = ARKStepSetPredictorMethod(arkode_mem, 1);         /* Specify maximum-order predictor */
  if (check_flag(&flag, "ARKStepSetPredictorMethod", 1)) return 1;
  flag = ARKStepSVtolerances(arkode_mem, reltol, atols);   /* Specify tolerances */
  if (check_flag(&flag, "ARKStepSStolerances", 1)) return 1;

  /* Specify the root-finding function, having 2 equations */
  flag = ARKStepRootInit(arkode_mem, 2, g);
  if (check_flag(&flag, "ARKStepRootInit", 1)) return 1;

  /* Initialize dense matrix data structure and solver */
  A = SUNDenseMatrix(NEQ, NEQ, ctx);
  if (check_flag((void *)A, "SUNDenseMatrix", 0)) return 1;
  LS = SUNLinSol_Dense(y, A, ctx);
  if (check_flag((void *)LS, "SUNLinSol_Dense", 0)) return 1;

  /* Linear solver interface */
  flag = ARKStepSetLinearSolver(arkode_mem, LS, A);        /* Attach matrix and linear solver */
  if (check_flag(&flag, "ARKStepSetLinearSolver", 1)) return 1;
  flag = ARKStepSetJacFn(arkode_mem, Jac);                 /* Set the Jacobian routine */
  if (check_flag(&flag, "ARKStepSetJacFn", 1)) return 1;

  /* Open output stream for results, output comment line */
  UFID = fopen("solution.txt","w");
  fprintf(UFID,"# t u v w\n");

  /* output initial condition to disk */
  fprintf(UFID," %.16"ESYM" %.16"ESYM" %.16"ESYM" %.16"ESYM"\n",
          T0, NV_Ith_S(y,0), NV_Ith_S(y,1), NV_Ith_S(y,2));

  /* Main time-stepping loop: calls ARKStepEvolve to perform the integration, then
     prints results.  Stops when the final time has been reached */
  t = T0;
  printf("        t             u             v             w\n");
  printf("   -----------------------------------------------------\n");
  printf("  %12.5"ESYM"  %12.5"ESYM"  %12.5"ESYM"  %12.5"ESYM"\n",
      t, NV_Ith_S(y,0), NV_Ith_S(y,1), NV_Ith_S(y,2));
  tout = T1;
  iout = 0;
  while(1) {

    flag = ARKStepEvolve(arkode_mem, tout, y, &t, ARK_NORMAL);     /* call integrator */
    if (check_flag(&flag, "ARKStepEvolve", 1)) break;
    printf("  %12.5"ESYM"  %12.5"ESYM"  %12.5"ESYM"  %12.5"ESYM"\n",  t,        /* access/print solution */
        NV_Ith_S(y,0), NV_Ith_S(y,1), NV_Ith_S(y,2));
    fprintf(UFID," %.16"ESYM" %.16"ESYM" %.16"ESYM" %.16"ESYM"\n",
            t, NV_Ith_S(y,0), NV_Ith_S(y,1), NV_Ith_S(y,2));
    if (flag == ARK_ROOT_RETURN) {                          /* check if a root was found */
      rtflag = ARKStepGetRootInfo(arkode_mem, rootsfound);
      if (check_flag(&rtflag, "ARKStepGetRootInfo", 1)) return 1;
      printf("      rootsfound[] = %3d %3d\n",
          rootsfound[0], rootsfound[1]);
    }
    if (flag >= 0) {                                        /* successful solve: update output time */
      iout++;
      tout *= TMult;
    } else {                                                /* unsuccessful solve: break */
      fprintf(stderr,"Solver failure, stopping integration\n");
      break;
    }
    if (iout == Nt) break;                                  /* stop after enough outputs */
  }
  printf("   -----------------------------------------------------\n");
  fclose(UFID);

  /* Print some final statistics */
  flag = ARKStepGetNumSteps(arkode_mem, &nst);
  check_flag(&flag, "ARKStepGetNumSteps", 1);
  flag = ARKStepGetNumStepAttempts(arkode_mem, &nst_a);
  check_flag(&flag, "ARKStepGetNumStepAttempts", 1);
  flag = ARKStepGetNumRhsEvals(arkode_mem, &nfe, &nfi);
  check_flag(&flag, "ARKStepGetNumRhsEvals", 1);
  flag = ARKStepGetNumLinSolvSetups(arkode_mem, &nsetups);
  check_flag(&flag, "ARKStepGetNumLinSolvSetups", 1);
  flag = ARKStepGetNumErrTestFails(arkode_mem, &netf);
  check_flag(&flag, "ARKStepGetNumErrTestFails", 1);
  flag = ARKStepGetNumNonlinSolvIters(arkode_mem, &nni);
  check_flag(&flag, "ARKStepGetNumNonlinSolvIters", 1);
  flag = ARKStepGetNumNonlinSolvConvFails(arkode_mem, &ncfn);
  check_flag(&flag, "ARKStepGetNumNonlinSolvConvFails", 1);
  flag = ARKStepGetNumJacEvals(arkode_mem, &nje);
  check_flag(&flag, "ARKStepGetNumJacEvals", 1);
  flag = ARKStepGetNumLinRhsEvals(arkode_mem, &nfeLS);
  check_flag(&flag, "ARKStepGetNumLinRhsEvals", 1);
  flag = ARKStepGetNumGEvals(arkode_mem, &nge);
  check_flag(&flag, "ARKStepGetNumGEvals", 1);

  printf("\nFinal Solver Statistics:\n");
  printf("   Internal solver steps = %li (attempted = %li)\n",
         nst, nst_a);
  printf("   Total RHS evals:  Fe = %li,  Fi = %li\n", nfe, nfi);
  printf("   Total linear solver setups = %li\n", nsetups);
  printf("   Total RHS evals for setting up the linear system = %li\n", nfeLS);
  printf("   Total number of Jacobian evaluations = %li\n", nje);
  printf("   Total number of Newton iterations = %li\n", nni);
  printf("   Total root-function g evals = %li\n", nge);
  printf("   Total number of nonlinear solver convergence failures = %li\n", ncfn);
  printf("   Total number of error test failures = %li\n", netf);

  /* Clean up and return with successful completion */
  N_VDestroy(y);               /* Free y vector */
  N_VDestroy(atols);           /* Free atols vector */
  ARKStepFree(&arkode_mem);    /* Free integrator memory */
  SUNLinSolFree(LS);           /* Free linear solver */
  SUNMatDestroy(A);            /* Free A matrix */
  SUNContext_Free(&ctx);       /* Free context */

  return 0;
}

/*-------------------------------
 * Functions called by the solver
 *-------------------------------*/

/* f routine to compute the ODE RHS function f(t,y). */
static int f(realtype t, N_Vector y, N_Vector ydot, void *user_data)
{
  realtype u = NV_Ith_S(y,0);     /* access current solution */
  realtype v = NV_Ith_S(y,1);
  realtype w = NV_Ith_S(y,2);

  /* Fill in the ODE RHS function */
  NV_Ith_S(ydot,0) = -0.04*u + 1.e4*v*w;
  NV_Ith_S(ydot,1) = 0.04*u - 1.e4*v*w - 3.e7*v*v;
  NV_Ith_S(ydot,2) = 3.e7*v*v;

  return 0;                      /* Return with success */
}

/* Jacobian routine to compute J(t,y) = df/dy. */
static int Jac(realtype t, N_Vector y, N_Vector fy, SUNMatrix J,
               void *user_data, N_Vector tmp1, N_Vector tmp2, N_Vector tmp3)
{
  realtype v = NV_Ith_S(y,1);    /* access current solution */
  realtype w = NV_Ith_S(y,2);
  SUNMatZero(J);                 /* initialize Jacobian to zero */

  /* Fill in the Jacobian of the ODE RHS function */
  SM_ELEMENT_D(J,0,0) = -0.04;
  SM_ELEMENT_D(J,0,1) = 1.e4*w;
  SM_ELEMENT_D(J,0,2) = 1.e4*v;

  SM_ELEMENT_D(J,1,0) = 0.04;
  SM_ELEMENT_D(J,1,1) = -1.e4*w - 6.e7*v;
  SM_ELEMENT_D(J,1,2) = -1.e4*v;

  SM_ELEMENT_D(J,2,1) = 6.e7*v;

  return 0;                      /* Return with success */
}

/* g routine to compute the root-finding function g(t,y). */
static int g(realtype t, N_Vector y, realtype *gout, void *user_data)
{
  realtype u = NV_Ith_S(y,0);    /* access current solution */
  realtype w = NV_Ith_S(y,2);

  gout[0] = u - RCONST(0.0001);  /* check for u == 1e-4 */
  gout[1] = w - RCONST(0.01);    /* check for w == 1e-2 */

  return 0;                      /* Return with success */
}

/*-------------------------------
 * Private helper functions
 *-------------------------------*/

/* Check function return value...
    opt == 0 means SUNDIALS function allocates memory so check if
             returned NULL pointer
    opt == 1 means SUNDIALS function returns a flag so check if
             flag >= 0
    opt == 2 means function allocates memory so check if returned
             NULL pointer
*/
static int check_flag(void *flagvalue, const char *funcname, int opt)
{
  int *errflag;

  /* Check if SUNDIALS function returned NULL pointer - no memory allocated */
  if (opt == 0 && flagvalue == NULL) {
    fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n",
            funcname);
    return 1; }

  /* Check if flag < 0 */
  else if (opt == 1) {
    errflag = (int *) flagvalue;
    if (*errflag < 0) {
      fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed with flag = %d\n\n",
              funcname, *errflag);
      return 1; }}

  /* Check if function returned NULL pointer - no memory allocated */
  else if (opt == 2 && flagvalue == NULL) {
    fprintf(stderr, "\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n",
            funcname);
    return 1; }

  return 0;
}


/*---- end of file ----*/
