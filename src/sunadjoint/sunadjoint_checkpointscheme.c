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
 * SUNAdjointCheckpointScheme class definition.
 * ----------------------------------------------------------------*/

#include <sunadjoint/sunadjoint_checkpointscheme.h>
#include <sundials/sundials_core.h>

#include "sundials/priv/sundials_errors_impl.h"
#include "sundials/sundials_errors.h"

SUNErrCode SUNAdjointCheckpointScheme_NewEmpty(
  SUNContext sunctx, SUNAdjointCheckpointScheme* check_scheme_ptr)
{
  SUNFunctionBegin(sunctx);

  SUNAdjointCheckpointScheme check_scheme = NULL;
  check_scheme                            = malloc(sizeof(*check_scheme));
  SUNAssert(check_scheme, SUN_ERR_MALLOC_FAIL);

  check_scheme->sunctx         = sunctx;
  check_scheme->content        = NULL;
  check_scheme->ops            = NULL;
  check_scheme->root_data_node = NULL;

  SUNAdjointCheckpointScheme_Ops ops = NULL;
  ops                                = malloc(sizeof(*ops));
  SUNAssert(ops, SUN_ERR_MALLOC_FAIL);

  ops->shouldWeSave   = NULL;
  ops->insert         = NULL;
  ops->insertVector   = NULL;
  ops->shouldWeDelete = NULL;
  ops->remove         = NULL;
  ops->removeRange    = NULL;
  ops->load           = NULL;
  ops->loadVector     = NULL;
  ops->destroy        = NULL;

  return SUN_SUCCESS;
}

SUNErrCode SUNAdjointCheckpointScheme_ShouldWeSave(
  SUNAdjointCheckpointScheme check_scheme, sunindextype step_num,
  sunindextype stage_num, sunrealtype t, sunbooleantype* yes_or_no)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->shouldWeSave)
  {
    return check_scheme->ops->shouldWeSave(check_scheme, step_num, stage_num, t,
                                           yes_or_no);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_Insert(
  SUNAdjointCheckpointScheme check_scheme, sunindextype step_num,
  sunindextype stage_num, sunrealtype t, SUNDataNode state)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->insert)
  {
    return check_scheme->ops->insert(check_scheme, step_num, stage_num, t, state);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_InsertVector(
  SUNAdjointCheckpointScheme check_scheme, sunindextype step_num,
  sunindextype stage_num, sunrealtype t, N_Vector state)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->insertVector)
  {
    return check_scheme->ops->insertVector(check_scheme, step_num, stage_num, t,
                                           state);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_ShouldWeDelete(
  SUNAdjointCheckpointScheme check_scheme, sunindextype step_num,
  sunindextype stage_num, sunbooleantype* yes_or_no)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->shouldWeDelete)
  {
    return check_scheme->ops->shouldWeDelete(check_scheme, step_num, stage_num,
                                             yes_or_no);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_Remove(
  SUNAdjointCheckpointScheme check_scheme, sunindextype step_num,
  sunindextype stage_num, SUNDataNode* out)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->remove)
  {
    return check_scheme->ops->remove(check_scheme, step_num, stage_num, out);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_Load(SUNAdjointCheckpointScheme check_scheme,
                                           sunindextype step_num,
                                           sunindextype stage_num,
                                           SUNDataNode* out)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->load)
  {
    return check_scheme->ops->load(check_scheme, step_num, stage_num, out);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_LoadVector(
  SUNAdjointCheckpointScheme check_scheme, sunindextype step_num,
  sunindextype stage_num, N_Vector* out)
{
  SUNFunctionBegin(check_scheme->sunctx);
  if (check_scheme->ops->loadVector)
  {
    return check_scheme->ops->loadVector(check_scheme, step_num, stage_num, out);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}

SUNErrCode SUNAdjointCheckpointScheme_Destroy(
  SUNAdjointCheckpointScheme* check_scheme_ptr)
{
  SUNFunctionBegin((*check_scheme_ptr)->sunctx);
  if ((*check_scheme_ptr)->ops->destroy)
  {
    return (*check_scheme_ptr)->ops->destroy(check_scheme_ptr);
  }
  return SUN_ERR_NOT_IMPLEMENTED;
}