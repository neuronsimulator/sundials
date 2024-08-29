/*-----------------------------------------------------------------
 * Programmer(s): Mustafa Aggul @ SMU
 *---------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2024, Lawrence Livermore National Security
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
 * The following is a simple example problem with analytical
 * solution,
 *    dy/dt = (lambda - alpha*cos((10 - t)/10*pi)*y + 1/(1+t^2) 
 *          - (lambda - alpha*cos((10 - t)/10*pi)*atan(t)
 * for t in the interval [0.0, 10.0], with initial condition: y=0.
 *
 * The stiffness of the problem is directly proportional to the
 * value of "lambda - alpha*cos((10 - t)/10*pi)". This value should 
 * be negative to result in a well-posed ODE; for values with magnitude 
 * larger than 100 the problem becomes quite stiff.
 *
 * This program solves the problem with the LSRK method.
 * Output is printed every 1.0 units of time (10 total).
 * Run statistics (optional outputs) are printed at the end.
 *-----------------------------------------------------------------*/

/* Header files */
#include <arkode/arkode_lsrkstep.h> /* prototypes for ARKStep fcts., consts */
#include <math.h>
#include <nvector/nvector_serial.h> /* serial N_Vector types, fcts., macros */
#include <stdio.h>
#include <sundials/sundials_math.h> /* def. of SUNRsqrt, etc. */
#include <sundials/sundials_types.h> /* definition of type sunrealtype          */

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
static int f(sunrealtype t, N_Vector y, N_Vector ydot, void* user_data);

/* User-supplied Dominated Eigenvalue Called by the Solver */
static int DomEig(sunrealtype t, N_Vector y, sunrealtype* lambdaR, sunrealtype* lambdaI, void* user_data);

/* Private function to check function return values */
static int check_flag(void* flagvalue, const char* funcname, int opt);

/* Private function to check computed solution */
static int check_ans(N_Vector y, sunrealtype t, sunrealtype rtol,
                     sunrealtype atol);

/* Private function to compute error */
static int compute_error(N_Vector y, sunrealtype t);

/* Main Program */
int main(void)
{
  /* general problem parameters */
  sunrealtype T0     = SUN_RCONST(0.0);    /* initial time */
  sunrealtype Tf     = SUN_RCONST(10.0);   /* final time */
  sunrealtype dTout  = SUN_RCONST(1.0);    /* time between outputs */
  sunindextype NEQ   = 1;                  /* number of dependent vars. */
  sunrealtype reltol = SUN_RCONST(1.0e-8); /* tolerances */
  sunrealtype abstol = SUN_RCONST(1.0e-8);
  sunrealtype lambda = SUN_RCONST(-1.0e+6); /* stiffness parameter 1*/
  sunrealtype alpha  = SUN_RCONST(1.0e+2);  /* stiffness parameter 2*/
  sunrealtype UserData[2];
  UserData[0] = lambda;
  UserData[1] = alpha;

  /* general problem variables */
  int flag;                /* reusable error-checking flag */
  N_Vector y       = NULL; /* empty vector for storing solution */
  void* arkode_mem = NULL; /* empty ARKode memory structure */
  FILE *UFID, *FID;
  sunrealtype t, tout;

  /* Create the SUNDIALS context object for this simulation */
  SUNContext ctx;
  flag = SUNContext_Create(SUN_COMM_NULL, &ctx);
  if (check_flag(&flag, "SUNContext_Create", 1)) { return 1; }

  /* Initial diagnostics output */
  printf("\nAnalytical ODE test problem with a variable Jacobian:");
  printf("\nThe stiffness of the problem is directly proportional to");
  printf("\n\"lambda - alpha*cos((10 - t)/10*pi)\"\n\n");
  printf("    lambda = %" GSYM "\n", lambda);
  printf("     alpha = %" GSYM "\n", alpha);
  printf("    reltol = %.1" ESYM "\n", reltol);
  printf("    abstol = %.1" ESYM "\n\n", abstol);

  /* Initialize data structures */
  y = N_VNew_Serial(NEQ, ctx); /* Create serial vector for solution */
  if (check_flag((void*)y, "N_VNew_Serial", 0)) { return 1; }
  NV_Ith_S(y, 0) = SUN_RCONST(0.0); /* Specify initial condition */

  /* Call LSRKStepCreate to initialize the ARK timestepper module and
     specify the right-hand side function in y'=f(t,y), the inital time
     T0, and the initial dependent variable vector y. */
  arkode_mem = LSRKStepCreate(f, NULL, T0, y, ctx);
  if (check_flag((void*)arkode_mem, "ARKStepCreate", 0)) { return 1; }

  /* Set routines */
  flag = ARKodeSetUserData(arkode_mem,
                           (void*)&UserData); /* Pass lambda to user functions */
  if (check_flag(&flag, "ARKodeSetUserData", 1)) { return 1; }

  /* Specify tolerances */
  flag = ARKodeSStolerances(arkode_mem, reltol, abstol);
  if (check_flag(&flag, "ARKStepSStolerances", 1)) { return 1; }

  /* Specify user provided spectral radius */
  flag = LSRKStepSetDomEigFn(arkode_mem, DomEig);
  if (check_flag(&flag, "LSRKStepSetDomEigFn", 1)) { return 1; }

  /* Specify after how many successful steps DomEig is recomputed */
  flag = LSRKStepSetDomEigFrequency(arkode_mem, 25);
  if (check_flag(&flag, "LSRKStepSetDomEigFrequency", 1)) { return 1; }

  /* Specify max number of stages allowed */
  flag = LSRKStepSetMaxStageNum(arkode_mem, 200);
  if (check_flag(&flag, "LSRKStepSetMaxStageNum", 1)) { return 1; }

  /* Specify max number of steps allowed */
  flag = ARKodeSetMaxNumSteps(arkode_mem, 1000);
  if (check_flag(&flag, "ARKodeSetMaxNumSteps", 1)) { return 1; }

  /* Specify safety factor for user provided DomEig */
  flag = LSRKStepSetDomEigSafetyFactor(arkode_mem, 1.01);
  if (check_flag(&flag, "LSRKStepSetDomEigSafetyFactor", 1)) { return 1; }

  /* Specify the LSRK method */
  flag = LSRKStepSetMethod(arkode_mem, ARKODE_LSRK_RKC);
  if (check_flag(&flag, "LSRKStepSetMethod", 1)) { return 1; }

  /* Open output stream for results, output comment line */
  UFID = fopen("solution.txt", "w");
  fprintf(UFID, "# t u\n");

  /* output initial condition to disk */
  fprintf(UFID, " %.16" ESYM " %.16" ESYM "\n", T0, NV_Ith_S(y, 0));

  /* Main time-stepping loop: calls ARKodeEvolve to perform the integration, then
     prints results.  Stops when the final time has been reached */
  t    = T0;
  tout = T0 + dTout;
  printf("        t           u\n");
  printf("   ---------------------\n");
  while (Tf - t > 1.0e-15)
  {
    flag = ARKodeEvolve(arkode_mem, tout, y, &t, ARK_NORMAL); /* call integrator */
    if (check_flag(&flag, "LSRKodeEvolve", 1)) { break; }
    printf("  %10.6" FSYM "  %10.6" FSYM "\n", t,
           NV_Ith_S(y, 0)); /* access/print solution */
    fprintf(UFID, " %.16" ESYM " %.16" ESYM "\n", t, NV_Ith_S(y, 0));
    if (flag >= 0)
    { /* successful solve: update time */
      tout += dTout;
      tout = (tout > Tf) ? Tf : tout;
    }
    else
    { /* unsuccessful solve: break */
      fprintf(stderr, "Solver failure, stopping integration\n");
      break;
    }
  }
  printf("   ---------------------\n");
  fclose(UFID);

  /* Print final statistics */
  printf("\nFinal Statistics:\n");
  flag = ARKodePrintAllStats(arkode_mem, stdout, SUN_OUTPUTFORMAT_TABLE);

  /* Print final statistics to a file in CSV format */
  FID  = fopen("ark_analytic_nonlin_stats.csv", "w");
  flag = ARKodePrintAllStats(arkode_mem, FID, SUN_OUTPUTFORMAT_CSV);
  fclose(FID);

  /* check the solution error */
  flag = check_ans(y, t, reltol, abstol);
  flag = compute_error(y, t);

  /* Clean up and return */
  N_VDestroy(y);            /* Free y vector */
  ARKodeFree(&arkode_mem); /* Free integrator memory */
  SUNContext_Free(&ctx);    /* Free context */

  return flag;
}

/*-------------------------------
 * Functions called by the solver
 *-------------------------------*/

/* f routine to compute the ODE RHS function f(t,y). */
static int f(sunrealtype t, N_Vector y, N_Vector ydot, void* user_data)
{
  sunrealtype* rdata = (sunrealtype*)user_data; /* cast user_data to sunrealtype */
  sunrealtype lambda = rdata[0]; /* set shortcut for stiffness parameter 1 */
  sunrealtype alpha  = rdata[1]; /* set shortcut for stiffness parameter 2 */
  sunrealtype u      = NV_Ith_S(y, 0); /* access current solution value */

  /* fill in the RHS function: "NV_Ith_S" accesses the 0th entry of ydot */
  NV_Ith_S(ydot, 0) = (lambda - alpha * cos((10 - t) / 10 * acos(-1))) * u +
                      SUN_RCONST(1.0) / (SUN_RCONST(1.0) + t * t) -
                      (lambda - alpha * cos((10 - t) / 10 * acos(-1))) * atan(t);

  return 0; /* return with success */
}

/* DomEig routine to estimate the dominated eigenvalue */
static int DomEig(sunrealtype t, N_Vector y, sunrealtype* lambdaR, sunrealtype* lambdaI, void* user_data)
{
  sunrealtype* rdata = (sunrealtype*)user_data; /* cast user_data to sunrealtype */
  sunrealtype lambda = rdata[0]; /* set shortcut for stiffness parameter 1 */
  sunrealtype alpha  = rdata[1]; /* set shortcut for stiffness parameter 2 */
  *lambdaR           = (lambda - alpha * cos((10 - t) / 10 *
                                        acos(-1))); /* access current solution value */
  *lambdaI           = 0.0;                                     

  return 0; /* return with success */
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
static int check_flag(void* flagvalue, const char* funcname, int opt)
{
  int* errflag;

  /* Check if SUNDIALS function returned NULL pointer - no memory allocated */
  if (opt == 0 && flagvalue == NULL)
  {
    fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n",
            funcname);
    return 1;
  }

  /* Check if flag < 0 */
  else if (opt == 1)
  {
    errflag = (int*)flagvalue;
    if (*errflag < 0)
    {
      fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed with flag = %d\n\n",
              funcname, *errflag);
      return 1;
    }
  }

  /* Check if function returned NULL pointer - no memory allocated */
  else if (opt == 2 && flagvalue == NULL)
  {
    fprintf(stderr, "\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n",
            funcname);
    return 1;
  }

  return 0;
}

/* check the computed solution */
static int check_ans(N_Vector y, sunrealtype t, sunrealtype rtol, sunrealtype atol)
{
  int passfail = 0;          /* answer pass (0) or fail (1) flag     */
  sunrealtype ans, err, ewt; /* answer data, error, and error weight */

  /* compute solution error */
  ans = atan(t);
  ewt = SUN_RCONST(1.0) / (rtol * fabs(ans) + atol);
  err = ewt * fabs(NV_Ith_S(y, 0) - ans);

  /* is the solution within the tolerances? */
  passfail = (err < SUN_RCONST(1.0)) ? 0 : 1;

  if (passfail)
  {
    fprintf(stdout, "\nSUNDIALS_WARNING: check_ans error=%" GSYM "\n\n", err);
  }

  return (passfail);
}

/* check the error */
static int compute_error(N_Vector y, sunrealtype t)
{
  sunrealtype ans, err; /* answer data, error */

  /* compute solution error */
  ans = atan(t);
  err = fabs(NV_Ith_S(y, 0) - ans);

  fprintf(stdout, "\nACCURACY at the final time = %" GSYM "\n", err);
}

/*---- end of file ----*/