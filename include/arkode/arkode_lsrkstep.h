/* -----------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds and Mustafa Aggul @ SMU
 * -----------------------------------------------------------------
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
 * This is the header file for the ARKODE LSRKStep module.
 * -----------------------------------------------------------------*/

#ifndef _LSRKSTEP_H
#define _LSRKSTEP_H

#include <arkode/arkode.h>

#ifdef __cplusplus /* wrapper to enable C++ usage */
extern "C" {
#endif

#define STAGE_MAX_LIMIT               1000000
#define DOM_EIG_SAFETY_DEFAULT        SUN_RCONST(1.01)
#define DOM_EIG_FREQ_DEFAULT          25
#define RETRY_CONTRACTION_FAC_DEFAULT SUN_RCONST(0.9)

typedef int (*ARKDomEigFn)(sunrealtype t, N_Vector y, N_Vector fn,
                           sunrealtype* lambdaR, sunrealtype* lambdaI,
                           void* user_data, N_Vector temp1, N_Vector temp2,
                           N_Vector temp3);

/* ------------------
 * LSRKStep Constants
 * ------------------ */

typedef enum
{
  ARKODE_LSRK_RKC_2    = 0, /* ensure enum is int */
  ARKODE_LSRK_RKL_2    = 1,
  ARKODE_LSRK_SSP_S_2  = 3,
  ARKODE_LSRK_SSP_S_3  = 4,
  ARKODE_LSRK_SSP_10_4 = 5
} ARKODE_LSRKMethodType;

/* -------------------
 * Exported Functions
 * ------------------- */

/* Creation and Reinitialization functions */

SUNDIALS_EXPORT void* LSRKStepCreateSTS(ARKRhsFn rhs, sunrealtype t0,
                                        N_Vector y0, SUNContext sunctx);

SUNDIALS_EXPORT void* LSRKStepCreateSSP(ARKRhsFn rhs, sunrealtype t0,
                                        N_Vector y0, SUNContext sunctx);

SUNDIALS_EXPORT int LSRKStepReInitSTS(void* arkode_mem, ARKRhsFn rhs,
                                      sunrealtype t0, N_Vector y0);

SUNDIALS_EXPORT int LSRKStepReInitSSP(void* arkode_mem, ARKRhsFn rhs,
                                      sunrealtype t0, N_Vector y0);

/* Optional input functions -- must be called AFTER a creation routine above */

SUNDIALS_EXPORT int LSRKStepSetMethod(void* arkode_mem,
                                      ARKODE_LSRKMethodType method);

SUNDIALS_EXPORT int LSRKStepSetMethodByName(void* arkode_mem,
                                            const char* emethod);

SUNDIALS_EXPORT int LSRKStepSetDomEigFn(void* arkode_mem, ARKDomEigFn dom_eig);

SUNDIALS_EXPORT int LSRKStepSetDomEigFrequency(void* arkode_mem, int nsteps);

SUNDIALS_EXPORT int LSRKStepSetMaxNumStages(void* arkode_mem,
                                            int stage_max_limit);

SUNDIALS_EXPORT int LSRKStepSetDomEigSafetyFactor(void* arkode_mem,
                                                  sunrealtype dom_eig_safety);

SUNDIALS_EXPORT int LSRKStepSetReTryContractionFactor(
  void* arkode_mem, sunrealtype retry_contraction_fac);

SUNDIALS_EXPORT int LSRKStepSetSSPStageNum(void* arkode_mem, int num_of_stages);

/* Optional output functions */

SUNDIALS_EXPORT int LSRKStepGetNumRhsEvals(void* arkode_mem, int num_rhs_fn,
                                           long int* f_evals);

SUNDIALS_EXPORT int LSRKStepGetNumDomEigUpdates(void* arkode_mem,
                                                long int* dom_eig_num_evals);

SUNDIALS_EXPORT int LSRKStepGetMaxNumStages(void* arkode_mem, int* stage_max);

#ifdef __cplusplus
}
#endif

#endif
