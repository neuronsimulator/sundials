/*---------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds @ SMU
 *---------------------------------------------------------------
 * LLNS/SMU Copyright Start
 * Copyright (c) 2017, Southern Methodist University and 
 * Lawrence Livermore National Security
 *
 * This work was performed under the auspices of the U.S. Department 
 * of Energy by Southern Methodist University and Lawrence Livermore 
 * National Laboratory under Contract DE-AC52-07NA27344.
 * Produced at Southern Methodist University and the Lawrence 
 * Livermore National Laboratory.
 *
 * All rights reserved.
 * For details, see the LICENSE file.
 * LLNS/SMU Copyright End
 *---------------------------------------------------------------
 * This is the implementation file for ARKode's temporal 
 * interpolation utility.
 *--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "arkode_impl.h"
#include <sundials/sundials_math.h>
#include <sundials/sundials_types.h>

#if defined(SUNDIALS_EXTENDED_PRECISION)
#define RSYM ".32Lg"
#else
#define RSYM ".16g"
#endif

#define NO_DEBUG_OUTPUT
#ifdef DEBUG_OUTPUT
#include <nvector/nvector_serial.h>
#endif


/*---------------------------------------------------------------
 arkInterpCreate:

 This routine creates an ARKodeInterpMem structure, through 
 cloning an input template N_Vector.  This returns a non-NULL 
 structure if no errors occurred, or a NULL value otherwise.
---------------------------------------------------------------*/
ARKodeInterpMem arkInterpCreate(void* arkode_mem)
{
  ARKodeMem ark_mem;
  ARKodeInterpMem interp_mem;

  /* access ARKodeMem structure */
  if (arkode_mem == NULL)  return(NULL);
  ark_mem = (ARKodeMem) arkode_mem;
  
  /* allocate structure */
  interp_mem = (ARKodeInterpMem) malloc(sizeof(struct ARKodeInterpMemRec));
  if (interp_mem == NULL)  return(NULL);
  memset(interp_mem, 0, sizeof(struct ARKodeInterpMemRec));

  /* set interpolation order based on user request (if possible) */
  if ((ark_mem->dense_q < 0) || (ark_mem->dense_q > 3)) {
    interp_mem->order = QDENSE_DEF;
  } else {
    interp_mem->order = ark_mem->dense_q;
  }

  /* vector allocation */
  if (!arkAllocVec(ark_mem, ark_mem->yn, &interp_mem->fold)) {
    arkInterpFree(&interp_mem); return(NULL);
  }
  if (!arkAllocVec(ark_mem, ark_mem->yn, &interp_mem->fnew)) {
    arkInterpFree(&interp_mem); return(NULL);
  }
  if (!arkAllocVec(ark_mem, ark_mem->yn, &interp_mem->yold)) {
    arkInterpFree(&interp_mem); return(NULL);
  }

  /* set ynew pointer to ark_mem->yn */
  interp_mem->ynew = ark_mem->yn;

  /* update workspace sizes */
  ark_mem->lrw += ARK_INTERP_LRW;
  ark_mem->liw += ARK_INTERP_LIW;
  
  /* copy ark_mem->yn into yold */
  N_VScale(ONE, ark_mem->yn, interp_mem->yold);

  /* initialize time values */
  interp_mem->told = ark_mem->tcur;
  interp_mem->tnew = ark_mem->tcur;
  interp_mem->h    = RCONST(0.0);
  
  return(interp_mem);
}


/*---------------------------------------------------------------
 arkInterpResize:

 This routine resizes the internal vectors in an ARKodeInterpMem 
 structure.
---------------------------------------------------------------*/
int arkInterpResize(void* arkode_mem, ARKodeInterpMem interp_mem, 
                    ARKVecResizeFn resize, void *resize_data,
                    sunindextype lrw_diff, sunindextype liw_diff,
                    N_Vector y0)
{
  int ier;
  ARKodeMem ark_mem;

  /* access ARKodeMem structure */
  if (arkode_mem == NULL)  return(ARK_MEM_NULL);
  ark_mem = (ARKodeMem) arkode_mem;

  /* resize vectors */
  if (interp_mem == NULL)  return(ARK_SUCCESS);
  if (interp_mem->fold != NULL) {
    ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                       liw_diff, y0, &interp_mem->fold);
    if (ier != ARK_SUCCESS)  return(ier);
  }
  if (interp_mem->fnew != NULL) {
    ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                       liw_diff, y0, &interp_mem->fnew);
    if (ier != ARK_SUCCESS)  return(ier);
  }
  if (interp_mem->yold != NULL) {
    ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                       liw_diff, y0, &interp_mem->yold);
    if (ier != ARK_SUCCESS)  return(ier);
  }

  /* update yold with current solution */
  N_VScale(ONE, y0, interp_mem->yold);

  /* reinitialize time values */
  interp_mem->told = ark_mem->tcur;
  interp_mem->tnew = ark_mem->tcur;
  interp_mem->h    = RCONST(0.0);
  
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
 arkInterpFree:

 This routine frees an ARKodeInterpMem structure.
---------------------------------------------------------------*/
void arkInterpFree(ARKodeInterpMem *interp_mem)
{
  if (*interp_mem != NULL) {
    if ((*interp_mem)->fold != NULL) N_VDestroy((*interp_mem)->fold);
    if ((*interp_mem)->fnew != NULL) N_VDestroy((*interp_mem)->fnew);
    if ((*interp_mem)->yold != NULL) N_VDestroy((*interp_mem)->yold);
    free(*interp_mem);
  }
}


/*---------------------------------------------------------------
 arkPrintInterpMem

 This routine outputs the temporal interpolation memory structure 
 to a specified file pointer.
---------------------------------------------------------------*/
void arkPrintInterpMem(ARKodeInterpMem interp_mem, FILE *outfile)
{
  if (interp_mem != NULL) {
    fprintf(outfile, "ark_interp: order = %d\n", interp_mem->order);
    fprintf(outfile, "ark_interp: told = %"RSYM"\n", interp_mem->told);
    fprintf(outfile, "ark_interp: tnew = %"RSYM"\n", interp_mem->tnew);
    fprintf(outfile, "ark_interp: h = %"RSYM"\n", interp_mem->h);
#ifdef DEBUG_OUTPUT
    if (interp_mem->fold != NULL) {
      fprintf(outfile, "ark_interp: fold:\n");
      N_VPrint_Serial(interp_mem->fold);
    }
    if (interp_mem->fnew != NULL) {
      fprintf(outfile, "ark_interp: fnew:\n");
      N_VPrint_Serial(interp_mem->fnew);
    }
    if (interp_mem->yold != NULL) {
      fprintf(outfile, "ark_interp: yold:\n");
      N_VPrint_Serial(interp_mem->yold);
    }
    if (interp_mem->ynew != NULL) {
      fprintf(outfile, "ark_interp: ynew:\n");
      N_VPrint_Serial(interp_mem->ynew);
    }
#endif    
  }
}


/*---------------------------------------------------------------
 arkInterpInit

 This routine performs the following steps:
 1. Sets tnew and told to the input time
 1. Copies ark_mem->yn into yold
 2. Calls the full RHS routine to fill fnew
 3. Copies fnew into fold
---------------------------------------------------------------*/
int arkInterpInit(void* arkode_mem, ARKodeInterpMem interp,
                  realtype tnew)
{
  int ier;
  ARKodeMem ark_mem;

  /* access ARKodeMem structure */
  if (arkode_mem == NULL)  return(ARK_MEM_NULL);
  ark_mem = (ARKodeMem) arkode_mem;

  /* return with success if no interpolation structure is allocated */
  if (interp == NULL)  return(ARK_SUCCESS);
  
  /* initialize time values */
  interp->told = tnew;
  interp->tnew = tnew;
  interp->h    = RCONST(0.0);
  
  /* copy current solution into yold */
  N_VScale(ONE, ark_mem->yn, interp->yold);

  /* fill fnew */
  ier = ark_mem->step_fullrhs(ark_mem, tnew, interp->ynew, 
                              interp->fnew, 0);
  if (ier != 0)  return(ARK_RHSFUNC_FAIL);

  /* copy fnew into fold */
  N_VScale(ONE, interp->fnew, interp->fold);
  
  /* return with success */
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
 arkInterpUpdate

 This routine performs the following steps:
 1. Copies ynew into yold, and swaps the fnew <-> fold pointers, 
    so that yold and fold contain the previous values
 2. Calls the full RHS routine to fill fnew, using ark_mem->ycur 
    for the time-evolved solution (since ynew==ark_mem->yn 
    has not been updated yet).

 Note: if forceRHS==SUNTRUE, then any previously-stored RHS 
 function data in the time step module is suspect, and all RHS 
 function(s) require recomputation; we therefore signal the 
 fullrhs function with a corresponding flag.
---------------------------------------------------------------*/
int arkInterpUpdate(void* arkode_mem, ARKodeInterpMem interp,
                    realtype tnew, booleantype forceRHS)
{
  int ier, mode;
  N_Vector tempvec;
  ARKodeMem ark_mem;

  /* access ARKodeMem structure */
  if (arkode_mem == NULL)  return(ARK_MEM_NULL);
  ark_mem = (ARKodeMem) arkode_mem;

  /* return with success if no interpolation structure is allocated */
  if (interp == NULL)  return(ARK_SUCCESS);
  
  /* copy ynew into yold */
  N_VScale(ONE, interp->ynew, interp->yold);

  /* swap fold & fnew N_Vector pointers */
  tempvec = interp->fold;
  interp->fold = interp->fnew;
  interp->fnew = tempvec;

  /* update time values */
  interp->told = interp->tnew;
  interp->tnew = tnew;
  interp->h    = ark_mem->h;
  
  /* determine mode for calling fullrhs */
  mode = (forceRHS) ? 0 : 1;
  
  /* fill fnew */
  ier = ark_mem->step_fullrhs(ark_mem, tnew, ark_mem->ycur,
                              interp->fnew, mode);
  if (ier != 0)  return(ARK_RHSFUNC_FAIL);

  /* return with success */
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkInterpEvaluate

  This routine evaluates a temporal interpolation/extrapolation 
  based on the data in the interpolation structure:
     yold = y(told)
     ynew = y(tnew)
     fold = f(told, yold)
     fnew = f(told, ynew)
  This typically consists of using a cubic Hermite interpolating 
  formula with this data.  If greater polynomial order than 3 is 
  requested, then we can bootstrap up to a 5th-order accurate 
  interpolant.  For lower order interpolants than cubic, we use:
     {yold,ynew,fnew} for quadratic
     {yold,ynew} for linear
     {0.5*(yold+ynew)} for constant.
 
  Derivatives have lower accuracy than the interpolant
  itself, losing one order per derivative.  We will provide 
  derivatives up to d = min(5,q).

  The input 'tau' specifies the time at which to return derivative
  information, the formula is 
               t = told + tau*(tnew-told),
  where h = tnew-told, i.e. values 0<tau<1 provide interpolation, 
  other values result in extrapolation.
---------------------------------------------------------------*/
int arkInterpEvaluate(void* arkode_mem, ARKodeInterpMem interp,
                      realtype tau, int d, int order, N_Vector yout)
{
  /* local variables */
  int q;
  realtype h, a0, a1, a2, a3, tau2, tau3;
  ARKodeMem ark_mem;

  /* access ARKodeMem structure */
  if (arkode_mem == NULL)  return(ARK_MEM_NULL);
  ark_mem = (ARKodeMem) arkode_mem;

  /* set constants */
  tau2 = tau*tau;
  tau3 = tau*tau2;
  h = interp->h;
  
  /* determine polynomial order q */
  q = SUNMAX(order, 0);        /* respect lower bound  */
  q = SUNMIN(q, 3);            /* respect max possible */

  /* check that d is possible */
  /* if ((d > SUNMIN(5,q)) || (d < 0)) { */
  if ((d > SUNMIN(3,q)) || (d < 0)) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "arkDenseEval", "Requested illegal derivative.");
    return (ARK_ILL_INPUT);
  }

  /* build polynomial based on order */
  switch (q) {

  case(0):    /* constant interpolant, yout = 0.5*(yn+yp) */
    N_VLinearSum(HALF, interp->yold, HALF, interp->ynew, yout);
    break;

  case(1):    /* linear interpolant */
    if (d == 0) {
      a0 = -tau;
      a1 = ONE+tau;
    } else {  /* d=1 */
      a0 = -ONE/h;
      a1 =  ONE/h;
    }
    N_VLinearSum(a0, interp->yold, a1, interp->ynew, yout);
    break;

  case(2):    /* quadratic interpolant */
    if (d == 0) {
      a0 = tau2;
      a1 = ONE -tau2;
      a2 = h*(tau2 + tau);
    } else if (d == 1) {
      a0 = TWO*tau/h;
      a1 = -TWO*tau/h;
      a2 = (ONE + TWO*tau);
    } else {  /* d == 2 */
      a0 = TWO/h/h;
      a1 = -TWO/h/h;
      a2 = TWO/h;
    }
    N_VLinearSum(a0, interp->yold, a1, interp->ynew, yout);
    N_VLinearSum(a2, interp->fnew, ONE, yout, yout);
    break;

  case(3):    /* cubic interpolant */
    if (d == 0) {
      a0 = THREE*tau2 + TWO*tau3;
      a1 = ONE - THREE*tau2 - TWO*tau3;
      a2 = h*(tau2 + tau3);
      a3 = h*(tau + TWO*tau2 + tau3);
    } else if (d == 1) {
      a0 = (SIX*tau + SIX*tau2)/h;
      a1 = -(SIX*tau + SIX*tau2)/h;
      a2 = TWO*tau + THREE*tau2;
      a3 = ONE + FOUR*tau + THREE*tau2;
    } else if (d == 2) {
      a0 = (SIX + TWELVE*tau)/h/h;
      a1 = -(SIX + TWELVE*tau)/h/h;
      a2 = (TWO + SIX*tau)/h;
      a3 = (FOUR + SIX*tau)/h;
    } else {  /* d == 3 */
      a0 = TWELVE/h/h/h;
      a1 = -TWELVE/h/h/h;
      a2 = SIX/h/h;
      a3 = SIX/h/h;
    }
    N_VLinearSum(a0, interp->yold, a1, interp->ynew, yout);
    N_VLinearSum(a2, interp->fold, ONE, yout, yout);
    N_VLinearSum(a3, interp->fnew, ONE, yout, yout);
    break;

  default:
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkDenseEval", 
                    "Illegal polynomial order");
    return (ARK_ILL_INPUT);
  }

  return(ARK_SUCCESS);
}


/*===============================================================
   EOF
===============================================================*/