/* -----------------------------------------------------------------------------
 * Programmer(s): Steven B. Roberts @ LLNL
 * -----------------------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2024, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------------------
 * Unit tests on several ODEs with analytical solutions to verify the
 * ForcingStep module.
 * ---------------------------------------------------------------------------*/

#include <arkode/arkode_arkstep.h>
#include <arkode/arkode_forcingstep.h>
#include <nvector/nvector_serial.h>

#if defined(SUNDIALS_EXTENDED_PRECISION)
#define GSYM "Lg"
#else
#define GSYM "g"
#endif

/* RHS function for f_1(t, y) = t / y */
static int f_forward_1(const sunrealtype t, const N_Vector y,
                       const N_Vector ydot, void* const user_data)
{
  N_VInv(y, ydot);
  N_VScale(t, ydot, ydot);
  return 0;
}

/* RHS function for f_2(t, y) = 1 / y */
static int f_forward_2(const sunrealtype t, const N_Vector y,
                       const N_Vector ydot, void* const user_data)
{
  N_VInv(y, ydot);
  return 0;
}

/* Integrates the ODE
 * 
 * y' = [t / y] - [1 / y]
 * 
 * with initial condition y(0) = 1 and partitioning specified by the square
 * brackets. We integrate to t = 1 and check the error against the exact
 * solution y(t) = |t + 1|.
 */
static int test_forward(SUNContext ctx)
{
  const sunrealtype t0         = SUN_RCONST(0.0);
  const sunrealtype tf         = SUN_RCONST(1.0);
  const sunrealtype dt         = SUN_RCONST(1.0e-4);
  const sunrealtype local_tol  = SUN_RCONST(1.0e-6);
  const sunrealtype global_tol = 10 * local_tol;

  const N_Vector y = N_VNew_Serial(1, ctx);
  N_VConst(SUN_RCONST(1.0), y);

  void* parititon_mem[] = {ARKStepCreate(f_forward_1, NULL, t0, y, ctx),
                           ARKStepCreate(f_forward_2, NULL, t0, y, ctx)};
  ARKodeSStolerances(parititon_mem[0], local_tol, local_tol);
  ARKodeSStolerances(parititon_mem[1], local_tol, local_tol);

  SUNStepper steppers[] = {NULL, NULL};
  ARKStepCreateSUNStepper(parititon_mem[0], &steppers[0]);
  ARKStepCreateSUNStepper(parititon_mem[1], &steppers[1]);

  void* arkode_mem = ForcingStepCreate(steppers[0], steppers[1], t0, y, ctx);
  ARKodeSetFixedStep(arkode_mem, dt);
  ARKodeSetMaxNumSteps(arkode_mem, -1);

  sunrealtype tret = t0;
  ARKodeEvolve(arkode_mem, tf, y, &tret, ARK_NORMAL);

  const sunrealtype exact_solution     = SUN_RCONST(2.0);
  const sunrealtype numerical_solution = NV_Ith_S(y, 0);
  if (SUNRCompareTol(exact_solution, numerical_solution, global_tol))
  {
    const sunrealtype err = numerical_solution - exact_solution;
    fprintf(stderr,
            "Forward direction solution failed with an error of %" GSYM "\n",
            err);
    return 1;
  }

  N_VDestroy(y);
  ARKodeFree(&parititon_mem[0]);
  SUNStepper_Destroy(&steppers[0]);
  ARKodeFree(&parititon_mem[1]);
  SUNStepper_Destroy(&steppers[1]);
  ARKodeFree(&arkode_mem);

  return 0;
}

/* Error handling function which prints the error and exits the program */
static void err_fn(const int line, const char* const func, const char* const file,
                   const char* const msg, const SUNErrCode err_code,
                   void* const err_user_data, const SUNContext ctx)
{
  fprintf(stderr, "Error at line %i of %s in %s: %s\n", line, func, file, msg);
  exit(err_code);
}

int main()
{
  SUNContext ctx = NULL;
  SUNErrCode err = SUNContext_Create(SUN_COMM_NULL, &ctx);
  if (err != SUN_SUCCESS)
  {
    fprintf(stderr, "Failed to create the SUNContext\n");
    return 1;
  }

  err = SUNContext_PushErrHandler(ctx, err_fn, NULL);
  if (err != SUN_SUCCESS)
  {
    fprintf(stderr, "Failed to add error handler\n");
    return 1;
  }

  err = test_forward(ctx);

  SUNContext_Free(&ctx);

  if (err == 0) { printf("Success\n"); }
  else { printf("%d Test Failures\n", err); }

  return 0;
}