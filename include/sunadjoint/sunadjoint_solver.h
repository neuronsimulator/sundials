/* -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2024, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------
 * SUNAdjointSolver class definition.
 * ----------------------------------------------------------------*/

#ifndef _SUNADJOINT_SOLVER_H
#define _SUNADJOINT_SOLVER_H

#include <sunadjoint/sunadjoint_checkpointscheme.h>
#include <sundials/sundials_core.h>
#include <sundials/sundials_stepper.h>

#include "sundials/sundials_types.h"

struct SUNAdjointSolver_
{
  SUNStepper adj_stepper;
  SUNStepper fwd_stepper;
  SUNAdjointCheckpointScheme checkpoint_scheme;

  SUNMatrix Jac, JacP;

  SUNJacFn JacFn, JacPFn;
  SUNJacTimesFn JvpFn, JPvpFn, vJpFn, vJPpFn;

  sunrealtype tf;
  int64_t step_idx;

  sunrealtype recompute_t0, recompute_tf;
  N_Vector recompute_y0;
  int64_t recompute_start_step, recompute_end_step;
  sunbooleantype recompute_flag;

  /* counters */
  uint64_t njeval, njpeval, njtimesv, njptimesv, nvtimesj, nvtimesjp, nrecompute;

  void* user_data;
  SUNContext sunctx;
};

typedef struct SUNAdjointSolver_* SUNAdjointSolver;

#ifdef __cplusplus
extern "C" {
#endif

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_Create(SUNStepper fwd_stepper, SUNStepper adj_stepper,
                                   int64_t final_step_idx, N_Vector sf,
                                   sunrealtype tf,
                                   SUNAdjointCheckpointScheme checkpoint_scheme,
                                   SUNContext sunctx,
                                   SUNAdjointSolver* adj_solver);

/*
  Solves the adjoint system.

  :param adj_solver: The adjoint solver object.
  :param tout: The time at which the adjoint solution is desired.
  :param sens: The vector of sensitivity solutions dg/dy0 and dg/dp.
  :param tret: On return, the time reached by the adjoint solver.
  :param stop_reason: On return, an integer code that indicates why the adjoint solver stopped.

  :returns: A SUNErrCode indicating failure or success.
 */
SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_Solve(SUNAdjointSolver adj_solver, sunrealtype tout,
                                  N_Vector sens, sunrealtype* tret,
                                  int* stop_reason);

/*
  Evolves the adjoint system backwards one step.

  :param adj_solver: The adjoint solver object.
  :param tout: The time at which the adjoint solution is desired.
  :param sens: The vector of sensitivity solutions dg/dy0 and dg/dp.
  :param tret: On return, the time reached by the adjoint solver.
  :param stop_reason: On return, an integer code that indicates why the adjoint solver stopped.

  :returns: A SUNErrCode indicating failure or success.
 */
SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_Step(SUNAdjointSolver adj_solver, sunrealtype tout,
                                 N_Vector sens, sunrealtype* tret,
                                 int* stop_reason);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_SetRecompute(SUNAdjointSolver adj_solver,
                                         int64_t start_idx, int64_t stop_idx,
                                         sunrealtype t0, sunrealtype tf,
                                         N_Vector y0);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_SetJacFn(SUNAdjointSolver, SUNJacFn JacFn,
                                     SUNMatrix Jac, SUNJacFn JacPFn,
                                     SUNMatrix JP);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_SetJacTimesVecFn(SUNAdjointSolver, SUNJacTimesFn Jvp,
                                             SUNJacTimesFn JPvp);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_SetVecTimesJacFn(SUNAdjointSolver, SUNJacTimesFn vJp,
                                             SUNJacTimesFn vJPp);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_SetUserData(SUNAdjointSolver, void* user_data);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_PrintAllStats(SUNAdjointSolver adj_solver,
                                          FILE* outfile, SUNOutputFormat fmt);

SUNDIALS_EXPORT
SUNErrCode SUNAdjointSolver_Destroy(SUNAdjointSolver*);

#ifdef __cplusplus
}
#endif
#endif /* _SUNADJOINT_SOLVER_H */