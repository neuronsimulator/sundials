/* ----------------------------------------------------------------------------
 * Programmer(s): Cody J. Balos @ LLNL
 * ----------------------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2022, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * ----------------------------------------------------------------------------
 * We consider the Kepler problem. We choose one body to be the center of our
 * coordinate system and then we use the coordinates q = (q1, q2) to represent
 * the position of the second body relative to the first (center). This yields
 * the ODE:
 *    dq/dt = [ p1 ]
 *            [ p2 ]
 *    dp/dt = [ -q1 / (q1^2 + q2^2)^(3/2) ]
 *          = [ -q2 / (q1^2 + q2^2)^(3/2) ]
 * with the initial conditions
 *    q(0) = [ 1 - e ],  p(0) = [        0          ]
 *           [   0   ]          [ sqrt((1+e)/(1-e)) ]
 * where e = 0.6 is the eccentricity.
 *
 * The Hamiltonian for the system,
 *    H(p,q) = 1/2 * (p1^2 + p2^2) - 1/sqrt(q1^2 + q2^2)
 * is conserved as well as the angular momentum,
 *    L(p,q) = q1*p2 - q2*p1.
 *
 * By default We solve the problem by letting y = [ q, p ]^T then using a 4th
 * order symplectic integrator via the SPRKStep time-stepper of ARKODE with a
 * fixed time-step size.
 *
 * The program also accepts command line arguments to change the method
 * used and time-stepping strategy. The program can be run like so
 *     ./ark_kepler [step mode] [method family] [method order/variant] [dt]
 * [compensated sums] where [step mode] = 0 uses a fixed time step dt [step
 * mode] = 1 uses adaptive time stepping [method family] = 0 indicates a SPRK
 * method should be used [method family] = 1 indicates an ERK method should be
 * used [method order] in {1, 2, 22, 222, 3, 33, 4, 44, 5, 6, 8, 10} indicates
 * the method order, and for 2nd, 3rd, and 4th order SPRK, the variant of the
 * method family to use. I.e., when method family = 1, then: 1 - Symplectic
 * Euler, 2 - 2nd order Leapfrog, 22 - 2nd order Pseudo Leapfrog, 222 - 2nd
 * order McLachlan, 3 - 3rd order Ruth, 33 - 3rd order McLachlan, 4 - 4th order
 * Candy-Rozmus, 44 - 4th order McLachlan, 5 - 5th order McLachlan, 6 - 6th
 * order Yoshida, 8 - 8th order McLachlan, 10 - 10th order Sofroniou When method
 * family = 1, then method order just is the order of the ERK method. [dt] -
 * time step size for fixed-step time stepping, or when using adaptivity the
 *      constant which bounds the error like O(eps^p) where p is the method
 * order. [compensated sums] = 0, dont use compensated summation for greater
 * accuracy when using SPRK methods [compensated sums] = 1, use compensated
 * summation for greater accuracy when using SPRK methods
 *
 * References:
 *    Ernst Hairer, Christain Lubich, Gerhard Wanner
 *    Geometric Numerical Integration: Structure-Preserving
 *    Algorithms for Ordinary Differential Equations
 *    Springer, 2006,
 *    ISSN 0179-3632
 * --------------------------------------------------------------------------*/

#include <arkode/arkode_arkstep.h> /* prototypes for ARKStep fcts., consts */
#include <arkode/arkode_sprk.h>
#include <arkode/arkode_sprkstep.h> /* prototypes for MRIStep fcts., consts */
#include <math.h>
#include <nvector/nvector_serial.h> /* serial N_Vector type, fcts., macros  */
#include <stdio.h>
#include <sundials/sundials_math.h> /* def. math fcns, 'sunrealtype'           */
#include <sundials/sundials_nonlinearsolver.h>
#include <sundials/sundials_nvector.h>
#include <sundials/sundials_types.h>
#include <sunnonlinsol/sunnonlinsol_fixedpoint.h>

#include "arkode/arkode.h"

static int check_retval(void* returnvalue, const char* funcname, int opt);

static void InitialConditions(N_Vector y0, sunrealtype ecc);
static sunrealtype Hamiltonian(N_Vector yvec);
static sunrealtype AngularMomentum(N_Vector y);

static int dydt(sunrealtype t, N_Vector y, N_Vector ydot, void* user_data);
static int velocity(sunrealtype t, N_Vector y, N_Vector ydot, void* user_data);
static int force(sunrealtype t, N_Vector y, N_Vector ydot, void* user_data);
static int rootfn(sunrealtype t, N_Vector y, sunrealtype* gout, void* user_data);

static sunrealtype Q(N_Vector yvec, sunrealtype alpha);
static sunrealtype G(N_Vector yvec, sunrealtype alpha);
static int Adapt(N_Vector y, sunrealtype t, sunrealtype h1, sunrealtype h2,
                 sunrealtype h3, sunrealtype e1, sunrealtype e2, sunrealtype e3,
                 int q, int p, sunrealtype* hnew, void* user_data);
static sunrealtype ControlError(N_Vector yvec, void* user_data);

typedef struct
{
  sunrealtype ecc;

  /* for time-step control */
  sunrealtype eps;
  sunrealtype alpha;
  sunrealtype rho_0;
  sunrealtype rho_nphalf;
  sunrealtype rho_n;
  sunrealtype Q0;

  FILE* hhist_fp;
} * UserData;

int main(int argc, char* argv[])
{
  SUNContext sunctx;
  N_Vector y;
  SUNNonlinearSolver NLS;
  UserData udata;
  sunrealtype tout, tret;
  sunrealtype H0, L0;
  void* arkode_mem;
  FILE *conserved_fp, *solution_fp, *times_fp;
  int argi, iout, retval;
  int rootsfound = 0;

  NLS = NULL;
  y   = NULL;

  /* Default problem parameters */
  const sunrealtype T0  = SUN_RCONST(0.0);
  sunrealtype Tf        = SUN_RCONST(50.0);
  sunrealtype dt        = SUN_RCONST(1e-2);
  const sunrealtype ecc = SUN_RCONST(0.6);

  /* Default integrator Options */
  int step_mode              = 0;
  int method                 = 0;
  int order                  = 4;
  int use_compsums           = 0;
  const sunrealtype dTout    = 10*dt; // SUN_RCONST(1.);
  const int num_output_times = (int)ceil(Tf / dTout);

  printf("\n   Begin Kepler Problem\n\n");

  /* Parse CLI args */
  argi = 0;
  if (argc > 1) { step_mode = atoi(argv[++argi]); }
  if (argc > 2) { method = atoi(argv[++argi]); }
  if (argc > 3) { order = atoi(argv[++argi]); }
  if (argc > 4) { dt = atof(argv[++argi]); }
  if (argc > 5) { use_compsums = atoi(argv[++argi]); }

  /* Allocate and fill udata structure */
  udata      = (UserData)malloc(sizeof(*udata));
  udata->ecc = ecc;
  /* Adaptivity controller parameters */
  /* Controller's integral gain. Increasing this will result in a higher
     rate of change in the step size, while decreasing it will result in
     a lower rate of change. */
  udata->alpha = SUN_RCONST(3.0) / SUN_RCONST(2.0);
  /* Controller's set-point. The error in the Hamiltonian is bounded by
   * O(eps^p) where p is the method order. */
  udata->eps = dt;

  /* Create the SUNDIALS context object for this simulation */
  retval = SUNContext_Create(NULL, &sunctx);
  if (check_retval(&retval, "SUNContext_Create", 1)) return 1;

  /* Allocate our state vector */
  y = N_VNew_Serial(4, sunctx);

  /* Fill the initial conditions */
  InitialConditions(y, ecc);

  /* Create SPRKStep integrator */
  if (method == 0)
  {
    arkode_mem = SPRKStepCreate(force, velocity, T0, y, sunctx);

    /* Enable temporal root-finding */
    SPRKStepRootInit(arkode_mem, 1, rootfn);
    if (check_retval(&retval, "SPRKStepRootInit", 1)) return 1;

    switch (order)
    {
    case 1:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticEuler());
      fprintf(stdout, "Using symplectic Euler O(h^1)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 2:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticLeapfrog2());
      fprintf(stdout, "Using symplectic Leapfrog O(h^2)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 22:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticPseudoLeapfrog2());
      fprintf(stdout, "Using symplectic Pseudo Leapfrog O(h^2)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 222:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticMcLachlan2());
      fprintf(stdout, "Using symplectic McLachlan O(h^2)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 3:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticRuth3());
      fprintf(stdout, "Using symplectic Ruth O(h^3)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 33:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticMcLachlan3());
      fprintf(stdout, "Using symplectic McLachlan O(h^3)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 4:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticCandyRozmus4());
      fprintf(stdout, "Using symplectic Candy-Rozmus O(h^4)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 44:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticMcLachlan4());
      fprintf(stdout, "Using symplectic McLachlan O(h^4)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 5:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticMcLachlan5());
      fprintf(stdout, "Using symplectic McLachlan O(h^5)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 6:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticYoshida6());
      fprintf(stdout, "Using symplectic Yoshida O(h^6)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 8:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticMcLachlan8());
      fprintf(stdout, "Using symplectic McLachlan O(h^8)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    case 10:
      retval = SPRKStepSetMethod(arkode_mem, ARKodeSymplecticSofroniou10());
      fprintf(stdout, "Using symplectic Sofroniou O(h^10)\n");
      if (check_retval(&retval, "SPRKStepSetMethod", 1)) return 1;
      break;
    default: fprintf(stderr, "Not a valid method\n"); return 1;
    }

    retval = SPRKStepSetUseCompensatedSums(arkode_mem, use_compsums);
    if (check_retval(&retval, "SPRKStepSetUseCompensatedSums", 1)) return 1;

    if (step_mode == 0)
    {
      retval = SPRKStepSetFixedStep(arkode_mem, dt);
      if (check_retval(&retval, "SPRKStepSetFixedStep", 1)) return 1;

      retval = SPRKStepSetMaxNumSteps(arkode_mem, ((long int)ceil(Tf / dt)) + 1);
      if (check_retval(&retval, "SPRKStepSetMaxNumSteps", 1)) return 1;
    }
    else
    {
      /* Adaptivity based on https://doi.org/10.1137/04060699 (Hairer and
       * Soderlind, 2005). */
      retval = SPRKStepSetAdaptivityFn(arkode_mem, Adapt, udata);
      if (check_retval(&retval, "SPRKStepSetAdaptivityFn", 1)) return 1;

      /* Compute the initial advance of rho_nphalf */
      udata->rho_0      = SUN_RCONST(1.0) / Q(y, udata->alpha);
      udata->rho_nphalf = udata->rho_0 +
                          udata->eps * G(y, udata->alpha) / SUN_RCONST(2.0);
      retval = SPRKStepSetInitStep(arkode_mem, udata->eps / udata->rho_nphalf);
      if (check_retval(&retval, "SPRKStepSetInitStep", 1)) return 1;

      /* Set the max number of time steps to something large. */
      retval = SPRKStepSetMaxNumSteps(arkode_mem, 100000000);
      if (check_retval(&retval, "SPRKStepSetMaxNumSteps", 1)) return 1;
    }

    retval = SPRKStepSetUserData(arkode_mem, (void*)udata);
    if (check_retval(&retval, "SPRKStepSetUserData", 1)) return 1;
  }
  else if (method >= 1)
  {
    if (method == 1)
    {
      arkode_mem = ARKStepCreate(dydt, NULL, T0, y, sunctx);

      retval = ARKStepSetOrder(arkode_mem, order);
      if (check_retval(&retval, "ARKStepSetOrder", 1)) return 1;
    }
    else
    {
      arkode_mem = ARKStepCreate(velocity, force, T0, y, sunctx);

      retval = ARKStepSetOrder(arkode_mem, order);
      if (check_retval(&retval, "ARKStepSetOrder", 1)) return 1;

      NLS = SUNNonlinSol_FixedPoint(y, 0, sunctx);
      ARKStepSetNonlinearSolver(arkode_mem, NLS);
    }

    ARKStepRootInit(arkode_mem, 1, rootfn);
    if (check_retval(&retval, "ARKStepRootInit", 1)) return 1;

    retval = ARKStepSetUserData(arkode_mem, (void*)udata);
    if (check_retval(&retval, "ARKStepSetUserData", 1)) return 1;

    retval = ARKStepSetMaxNumSteps(arkode_mem, 1000000);
    if (check_retval(&retval, "ARKStepSetMaxNumSteps", 1)) return 1;

    if (step_mode == 0) { retval = ARKStepSetFixedStep(arkode_mem, dt); }
    else
    {
      retval = ARKStepSStolerances(arkode_mem, dt, dt);
      if (check_retval(&retval, "ARKStepSStolerances", 1)) return 1;
    }
  }

  /* Open output files */
  if (method == 0)
  {
    const char* fmt1 = "ark_kepler_conserved_sprk-%d-dt-%.2e.txt";
    const char* fmt2 = "ark_kepler_solution_sprk-%d-dt-%.2e.txt";
    const char* fmt3 = "ark_kepler_times_sprk-%d-dt-%.2e.txt";
    const char* fmt4 = "ark_kepler_hhist_sprk-%d-dt-%.2e.txt";
    char fname[64];
    sprintf(fname, fmt1, order, dt);
    conserved_fp = fopen(fname, "w+");
    sprintf(fname, fmt2, order, dt);
    solution_fp = fopen(fname, "w+");
    sprintf(fname, fmt3, order, dt);
    times_fp = fopen(fname, "w+");
    sprintf(fname, fmt4, order, dt);
    udata->hhist_fp = fopen(fname, "w+");
  }
  else
  {
    const char* fmt1 = "ark_kepler_conserved_erk-%d-dt-%.2e.txt";
    const char* fmt2 = "ark_kepler_solution_erk-%d-dt-%.2e.txt";
    const char* fmt3 = "ark_kepler_times_erk-%d-dt-%.2e.txt";
    char fname[64];
    sprintf(fname, fmt1, order, dt);
    conserved_fp = fopen(fname, "w+");
    sprintf(fname, fmt2, order, dt);
    solution_fp = fopen(fname, "w+");
    sprintf(fname, fmt3, order, dt);
    times_fp = fopen(fname, "w+");
  }

  /* Print out starting energy, momentum before integrating */
  tret      = T0;
  tout      = T0 + dTout;
  H0        = Hamiltonian(y);
  L0        = AngularMomentum(y);
  udata->Q0 = Q(y, udata->alpha);
  fprintf(stdout,
          "t = %.4Lf, H(p,q) = %.16Lf, L(p,q) = %.16Lf, Q(p,q) = %.16Lf\n",
          tret, H0, L0, udata->Q0);
  fprintf(times_fp, "%.16Lf\n", tret);
  fprintf(conserved_fp, "%.16Lf, %.16Lf\n", H0, L0);
  N_VPrintFile(y, solution_fp);

  /* Do integration */
  if (method == 0)
  {
    for (iout = 0; iout < num_output_times; iout++)
    {
      sunrealtype hlast = SUN_RCONST(0.0);

      SPRKStepSetStopTime(arkode_mem, tout);
      retval = SPRKStepEvolve(arkode_mem, tout, y, &tret, ARK_NORMAL);

      if (retval == ARK_ROOT_RETURN)
      {
        fprintf(stdout, "ROOT RETURN:\t");
        SPRKStepGetRootInfo(arkode_mem, &rootsfound);
        fprintf(stdout, "t = %.4Lf g[0] = %3d, y[0] = %3Lg, y[1] = %3Lg\n", tret,
                rootsfound, N_VGetArrayPointer(y)[0], N_VGetArrayPointer(y)[1]);
        fprintf(stdout, "t = %.4Lf, H(p,q)-H0 = %.16Lf, L(p,q)-L0 = %.16Lf, Q(p,q)-Q0 = %.16Lf\n",
                tret, Hamiltonian(y) - H0, AngularMomentum(y) - L0,
                ControlError(y, udata));

        /* Continue to tout */
        retval = SPRKStepEvolve(arkode_mem, tout, y, &tret, ARK_NORMAL);
      }

      /* Output current integration status */
      fprintf(stdout, "t = %.4Lf, H(p,q)-H0 = %.16Lf, L(p,q)-L0 = %.16Lf, Q(p,q)-Q0 = %.16Lf\n",
              tret, Hamiltonian(y) - H0, AngularMomentum(y) - L0,
              ControlError(y, udata));
      fprintf(times_fp, "%.16Lf\n", tret);
      fprintf(conserved_fp, "%.16Lf, %.16Lf\n", Hamiltonian(y),
              AngularMomentum(y));

      SPRKStepGetLastStep(arkode_mem, &hlast);
      fprintf(udata->hhist_fp, "%.16Lf, %.16Lf\n", hlast, ControlError(y, udata));
      N_VPrintFile(y, solution_fp);

      /* Check if the solve was successful, if so, update the time and continue
       */
      if (retval >= 0)
      {
        tout += dTout;
        tout = (tout > Tf) ? Tf : tout;
      }
      else
      {
        fprintf(stderr, "Solver failure, stopping integration\n");
        break;
      }
    }
  }
  else
  {
    for (iout = 0; iout < num_output_times; iout++)
    {
      ARKStepSetStopTime(arkode_mem, tout);
      retval = ARKStepEvolve(arkode_mem, tout, y, &tret, ARK_NORMAL);

      if (retval == ARK_ROOT_RETURN)
      {
        fprintf(stdout, "ROOT RETURN:\t");
        ARKStepGetRootInfo(arkode_mem, &rootsfound);
        fprintf(stdout, "t = %.4Lf g[0] = %3d, y[0] = %3Lg, y[1] = %3Lg\n", tret,
                rootsfound, N_VGetArrayPointer(y)[0], N_VGetArrayPointer(y)[1]);
        fprintf(stdout, "t = %.4Lf, H(p,q)-H0 = %.16Lf, L(p,q)-L0 = %.16Lf, Q(p,q)-Q0 = %.16Lf\n",
                tret, Hamiltonian(y) - H0, AngularMomentum(y) - L0,
                ControlError(y, udata));

        /* Continue to tout */
        retval = ARKStepEvolve(arkode_mem, tout, y, &tret, ARK_NORMAL);
      }

      /* Output current integration status */
      fprintf(stdout, "t = %.4Lf, H(p,q)-H0 = %.16Lf, L(p,q)-L0 = %.16Lf, Q(p,q)-Q0 = %.16Lf\n",
              tret, Hamiltonian(y) - H0, AngularMomentum(y) - L0,
              ControlError(y, udata));
      fprintf(times_fp, "%.16Lf\n", tret);
      fprintf(conserved_fp, "%.16Lf, %.16Lf\n", Hamiltonian(y),
              AngularMomentum(y));
      N_VPrintFile(y, solution_fp);

      /* Check if the solve was successful, if so, update the time and continue
       */
      if (retval >= 0)
      {
        tout += dTout;
        tout = (tout > Tf) ? Tf : tout;
      }
      else
      {
        fprintf(stderr, "Solver failure, stopping integration\n");
        break;
      }
    }
  }

  if (udata->hhist_fp) { fclose(udata->hhist_fp); }
  free(udata);
  fclose(times_fp);
  fclose(conserved_fp);
  fclose(solution_fp);
  if (NLS) { SUNNonlinSolFree(NLS); }
  N_VDestroy(y);
  if (method == 0)
  {
    SPRKStepPrintAllStats(arkode_mem, stdout, SUN_OUTPUTFORMAT_TABLE);
    SPRKStepFree(&arkode_mem);
  }
  else
  {
    ARKStepPrintAllStats(arkode_mem, stdout, SUN_OUTPUTFORMAT_TABLE);
    ARKStepFree(&arkode_mem);
  }

  SUNContext_Free(&sunctx);

  return 0;
}

void InitialConditions(N_Vector y0vec, sunrealtype ecc)
{
  const sunrealtype zero = SUN_RCONST(0.0);
  const sunrealtype one  = SUN_RCONST(1.0);
  sunrealtype* y0        = N_VGetArrayPointer(y0vec);

  y0[0] = one - ecc;
  y0[1] = zero;
  y0[2] = zero;
  y0[3] = SUNRsqrt((one + ecc) / (one - ecc));
}

void Solution(N_Vector yvec, UserData user_data) {}

sunrealtype Hamiltonian(N_Vector yvec)
{
  sunrealtype H              = 0.0;
  sunrealtype* y             = N_VGetArrayPointer(yvec);
  const sunrealtype sqrt_qTq = SUNRsqrt(y[0] * y[0] + y[1] * y[1]);
  const sunrealtype pTp      = y[2] * y[2] + y[3] * y[3];

  H = SUN_RCONST(0.5) * pTp - SUN_RCONST(1.0) / sqrt_qTq;

  return H;
}

sunrealtype AngularMomentum(N_Vector yvec)
{
  sunrealtype L        = 0.0;
  sunrealtype* y       = N_VGetArrayPointer(yvec);
  const sunrealtype q1 = y[0];
  const sunrealtype q2 = y[1];
  const sunrealtype p1 = y[2];
  const sunrealtype p2 = y[3];

  L = q1 * p2 - q2 * p1;

  return L;
}

int dydt(sunrealtype t, N_Vector yvec, N_Vector ydotvec, void* user_data)
{
  int retval = 0;

  retval += force(t, yvec, ydotvec, user_data);
  retval += velocity(t, yvec, ydotvec, user_data);

  return retval;
}

int velocity(sunrealtype t, N_Vector yvec, N_Vector ydotvec, void* user_data)
{
  sunrealtype* y       = N_VGetArrayPointer(yvec);
  sunrealtype* ydot    = N_VGetArrayPointer(ydotvec);
  const sunrealtype p1 = y[2];
  const sunrealtype p2 = y[3];

  ydot[0] = p1;
  ydot[1] = p2;
  // ydot[2] = ydot[3] = SUN_RCONST(0.0);

  return 0;
}

int force(sunrealtype t, N_Vector yvec, N_Vector ydotvec, void* user_data)
{
  UserData udata             = (UserData)user_data;
  sunrealtype* y             = N_VGetArrayPointer(yvec);
  sunrealtype* ydot          = N_VGetArrayPointer(ydotvec);
  const sunrealtype q1       = y[0];
  const sunrealtype q2       = y[1];
  const sunrealtype sqrt_qTq = SUNRsqrt(q1 * q1 + q2 * q2);

  // ydot[0] = ydot[1] = SUN_RCONST(0.0);
  ydot[2] = -q1 / SUNRpowerR(sqrt_qTq, SUN_RCONST(3.0));
  ydot[3] = -q2 / SUNRpowerR(sqrt_qTq, SUN_RCONST(3.0));

  return 0;
}

int rootfn(sunrealtype t, N_Vector yvec, sunrealtype* gout, void* user_data)
{
  UserData udata       = (UserData)user_data;
  sunrealtype* y       = N_VGetArrayPointer(yvec);
  const sunrealtype q1 = y[0];
  const sunrealtype q2 = y[1];

  /* We want to know when the body crosses the position (0.36, -0.22) */
  gout[0] = (q1 - SUN_RCONST(0.36)) + (q2 + SUN_RCONST(0.22));

  return 0;
}

/* Functions needed to implement the step density integrating controller
   proposed by Hairer and Soderlind in https://doi.org/10.1137/04060699. */

sunrealtype G(N_Vector yvec, sunrealtype alpha)
{
  sunrealtype* y       = N_VGetArrayPointer(yvec);
  const sunrealtype q1 = y[0];
  const sunrealtype q2 = y[1];
  const sunrealtype p1 = y[2];
  const sunrealtype p2 = y[3];

  const sunrealtype pTq = p1 * q1 + p2 * q2;
  const sunrealtype qTq = q1 * q1 + q2 * q2;

  return (-alpha * pTq / qTq);
}

sunrealtype Q(N_Vector yvec, sunrealtype alpha)
{
  sunrealtype* y       = N_VGetArrayPointer(yvec);
  const sunrealtype q1 = y[0];
  const sunrealtype q2 = y[1];

  const sunrealtype qTq = q1 * q1 + q2 * q2;

  return SUNRpowerR(qTq, alpha / SUN_RCONST(2.0));
}

int Adapt(N_Vector y, sunrealtype t, sunrealtype h1, sunrealtype h2,
          sunrealtype h3, sunrealtype e1, sunrealtype e2, sunrealtype e3, int q,
          int p, sunrealtype* hnew, void* user_data)
{
  UserData udata = (UserData)user_data;

  /* When we enter this function, we are have already computed y_n+1 and are
   * preparing for the next step. */
  sunrealtype Gyn   = G(y, udata->alpha);
  udata->rho_n      = udata->rho_nphalf + udata->eps * Gyn / SUN_RCONST(2.0);
  udata->rho_nphalf = udata->rho_n + udata->eps * Gyn / SUN_RCONST(2.0);

  *hnew = udata->eps / udata->rho_nphalf;

  // fprintf(stderr, "<<< hnew  =%g\n", (double) *hnew);

  return 0;
}

sunrealtype ControlError(N_Vector yvec, void* user_data)
{
  UserData udata = (UserData)user_data;
  return udata->rho_n * Q(yvec, udata->alpha) - udata->rho_0 * udata->Q0;
}

/* Check function return value...
    opt == 0 means SUNDIALS function allocates memory so check if
             returned NULL pointer
    opt == 1 means SUNDIALS function returns a retval so check if
             retval < 0
    opt == 2 means function allocates memory so check if returned
             NULL pointer
*/
int check_retval(void* returnvalue, const char* funcname, int opt)
{
  int* retval;

  /* Check if SUNDIALS function returned NULL pointer - no memory allocated */
  if (opt == 0 && returnvalue == NULL)
  {
    fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n",
            funcname);
    return 1;
  }

  /* Check if retval < 0 */
  else if (opt == 1)
  {
    retval = (int*)returnvalue;
    if (*retval < 0)
    {
      fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed with retval = %d\n\n",
              funcname, *retval);
      return 1;
    }
  }

  /* Check if function returned NULL pointer - no memory allocated */
  else if (opt == 2 && returnvalue == NULL)
  {
    fprintf(stderr, "\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n",
            funcname);
    return 1;
  }

  return 0;
}
