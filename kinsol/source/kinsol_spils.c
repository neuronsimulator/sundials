/*
 * -----------------------------------------------------------------
 * $Revision: 1.1 $
 * $Date: 2006-02-02 00:36:32 $
 * -----------------------------------------------------------------
 * Programmer(s): Radu Serban and Aaron Collier @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2002, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see sundials/kinsol/LICENSE.
 * -----------------------------------------------------------------
 * This is the implementation file for the KINSPILS linear solvers.
 * -----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "kinsol_impl.h"
#include "kinsol_spils_impl.h"

#include "sundials_math.h"

/*
 * -----------------------------------------------------------------
 * private constants
 * -----------------------------------------------------------------
 */

#define ZERO RCONST(0.0)
#define ONE  RCONST(1.0)
#define TWO  RCONST(2.0)


/*
 * -----------------------------------------------------------------
 * readability replacements
 * -----------------------------------------------------------------
 */

#define lrw1           (kin_mem->kin_lrw1)
#define liw1           (kin_mem->kin_liw1)
#define func           (kin_mem->kin_func)
#define f_data         (kin_mem->kin_f_data)
#define printfl        (kin_mem->kin_printfl)
#define lmem           (kin_mem->kin_lmem)
#define uu             (kin_mem->kin_uu)
#define fval           (kin_mem->kin_fval)
#define uscale         (kin_mem->kin_uscale)
#define fscale         (kin_mem->kin_fscale)
#define sqrt_relfunc   (kin_mem->kin_sqrt_relfunc)
#define eps            (kin_mem->kin_eps)
#define errfp          (kin_mem->kin_errfp)
#define infofp         (kin_mem->kin_infofp)
#define vtemp1         (kin_mem->kin_vtemp1)
#define vec_tmpl       (kin_mem->kin_vtemp1)
#define vtemp2         (kin_mem->kin_vtemp2)

#define ils_type       (kinspils_mem->s_type)
#define pretype        (kinspils_mem->s_pretype)
#define gstype         (kinspils_mem->s_gstype)
#define nli            (kinspils_mem->s_nli)
#define npe            (kinspils_mem->s_npe)
#define nps            (kinspils_mem->s_nps)
#define ncfl           (kinspils_mem->s_ncfl)
#define njtimes        (kinspils_mem->s_njtimes)
#define nfes           (kinspils_mem->s_nfes)
#define new_uu         (kinspils_mem->s_new_uu)
#define last_flag      (kinspils_mem->s_last_flag)


/*
 * -----------------------------------------------------------------
 * Function : KINSpilsSetMaxRestarts
 * -----------------------------------------------------------------
 */

int KINSpilsSetMaxRestarts(void *kinmem, int maxrs)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsSetMaxRestarts", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsSetMaxRestarts", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;

  /* check for legal maxrs */

  if (maxrs < 0) {
    KINProcessError(kin_mem, KINSPILS_ILL_INPUT, "KINSPILS", "KINSpilsSetMaxRestarts", MSGS_NEG_MAXRS);
    return(KINSPILS_ILL_INPUT);
  }
  kinspils_mem->s_maxlrst = maxrs;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsSetPreconditioner
 * -----------------------------------------------------------------
 */

int KINSpilsSetPreconditioner(void *kinmem,
			      KINSpilsPrecSetupFn pset,
			      KINSpilsPrecSolveFn psolve,
			      void *P_data)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsSetPreconditioner", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsSetPreconditioner", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;

  kinspils_mem->s_pset   = pset;
  kinspils_mem->s_psolve = psolve;
  kinspils_mem->s_P_data = P_data;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsSetJacTimesVecFn
 * -----------------------------------------------------------------
 */

int KINSpilsSetJacTimesVecFn(void *kinmem,
			     KINSpilsJacTimesVecFn jtimes,
			     void *J_data)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsSetJacTimesVecFn", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsSetJacTimesVecFn", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;

  kinspils_mem->s_jtimes = jtimes;
  kinspils_mem->s_J_data = J_data;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetWorkSpace
 * -----------------------------------------------------------------
 */

int KINSpilsGetWorkSpace(void *kinmem, long int *lenrwSG, long int *leniwSG)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;
  int maxl;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetWorkSpace", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetWorkSpace", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;

  maxl = kinspils_mem->s_maxl;

  switch(ils_type) {
  case SPILS_SPGMR:
    *lenrwSG = lrw1 * (maxl + 3) + (maxl * (maxl + 4)) + 1;
    *leniwSG = liw1 * (maxl + 3);
    break;
  case SPILS_SPBCG:
    *lenrwSG = lrw1 * 7;
    *leniwSG = liw1 * 7;
    break;
  case SPILS_SPTFQMR:
    *lenrwSG = lrw1 * 11;
    *leniwSG = liw1 * 11;
    break;
  }


  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetNumPrecEvals
 * -----------------------------------------------------------------
 */

int KINSpilsGetNumPrecEvals(void *kinmem, long int *npevals)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetNumPrecEvals", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetNumPrecEvals", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;
  *npevals = npe;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetNumPrecSolves
 * -----------------------------------------------------------------
 */

int KINSpilsGetNumPrecSolves(void *kinmem, long int *npsolves)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetNumPrecSolves", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetNumPrecSolves", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;
  *npsolves = nps;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetNumLinIters
 * -----------------------------------------------------------------
 */

int KINSpilsGetNumLinIters(void *kinmem, long int *nliters)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetNumLinIters", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetNumLinIters", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;
  *nliters = nli;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetNumConvFails
 * -----------------------------------------------------------------
 */

int KINSpilsGetNumConvFails(void *kinmem, long int *nlcfails)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetNumConvFails", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetNumConvFails", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;
  *nlcfails = ncfl;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetNumJtimesEvals
 * -----------------------------------------------------------------
 */

int KINSpilsGetNumJtimesEvals(void *kinmem, long int *njvevals)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetNumJtimesEvals", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetNumJtimesEvals", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;
  *njvevals = njtimes;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetNumFuncEvals
 * -----------------------------------------------------------------
 */

int KINSpilsGetNumFuncEvals(void *kinmem, long int *nfevalsS)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetNumFuncEvals", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetNumFuncEvals", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;
  *nfevalsS = nfes;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsGetLastFlag
 * -----------------------------------------------------------------
 */

int KINSpilsGetLastFlag(void *kinmem, int *flag)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;

  /* return immediately if kinmem is NULL */

  if (kinmem == NULL) {
    KINProcessError(NULL, KINSPILS_MEM_NULL, "KINSPILS", "KINSpilsGetLastFlag", MSGS_KINMEM_NULL);
    return(KINSPILS_MEM_NULL);
  }
  kin_mem = (KINMem) kinmem;

  if (lmem == NULL) {
    KINProcessError(kin_mem, KINSPILS_LMEM_NULL, "KINSPILS", "KINSpilsGetLastFlag", MSGS_LMEM_NULL);
    return(KINSPILS_LMEM_NULL);
  }
  kinspils_mem = (KINSpilsMem) lmem;

  *flag = last_flag;

  return(KINSPILS_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * additional readability replacements
 * -----------------------------------------------------------------
 */

#define maxl    (kinspils_mem->s_maxl)
#define maxlrst (kinspils_mem->s_maxlrst)
#define pset    (kinspils_mem->s_pset)
#define psolve  (kinspils_mem->s_psolve)
#define P_data  (kinspils_mem->s_P_data)
#define jtimes  (kinspils_mem->s_jtimes)
#define J_data  (kinspils_mem->s_J_data)

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsAtimes
 * -----------------------------------------------------------------
 * This routine coordinates the generation of the matrix-vector
 * product z = J*v by calling either KINSpilsDQJtimes, which uses
 * a difference quotient approximation for J*v, or by calling the
 * user-supplied routine KINSpilsJacTimesVecFn if it is non-null.
 * -----------------------------------------------------------------
 */

int KINSpilsAtimes(void *kinsol_mem, N_Vector v, N_Vector z)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;
  int ret;

  kin_mem = (KINMem) kinsol_mem;
  kinspils_mem = (KINSpilsMem) lmem;

  ret = jtimes(v, z, uu, &new_uu, J_data);
  njtimes++;

  return(ret);
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsPSolve
 * -----------------------------------------------------------------
 * This routine interfaces between the generic SpgmrSolve routine
 * and the user's psolve routine. It passes to psolve all required
 * state information from kinsol_mem. Its return value is the same
 * as that returned by psolve. Note that the generic SPGMR solver
 * guarantees that KINSpilsPSolve will not be called in the case in
 * which preconditioning is not done. This is the only case in which
 * the user's psolve routine is allowed to be NULL.
 * -----------------------------------------------------------------
 */

int KINSpilsPSolve(void *kinsol_mem, N_Vector r, N_Vector z, int lrdummy)
{
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;
  int ret;

  kin_mem = (KINMem) kinsol_mem;
  kinspils_mem = (KINSpilsMem) lmem;

  /* copy the rhs into z before the psolve call */   
  /* Note: z returns with the solution */

  N_VScale(ONE, r, z);

  /* this call is counted in nps within the KINSpilsSolve routine */

  ret = psolve(uu, uscale, fval, fscale, z, P_data, vtemp1);

  return(ret);     
}

/*
 * -----------------------------------------------------------------
 * Function : KINSpilsDQJtimes
 * -----------------------------------------------------------------
 * This routine generates the matrix-vector product z = J*v using a
 * difference quotient approximation. The approximation is 
 * J*v = [func(uu + sigma*v) - func(uu)]/sigma. Here sigma is based
 * on the dot products (uscale*uu, uscale*v) and
 * (uscale*v, uscale*v), the L1Norm(uscale*v), and on sqrt_relfunc
 * (the square root of the relative error in the function). Note
 * that v in the argument list has already been both preconditioned
 * and unscaled.
 * -----------------------------------------------------------------
 */

int KINSpilsDQJtimes(N_Vector v, N_Vector Jv,
                     N_Vector u, booleantype *new_u, 
                     void *jac_data)
{
  realtype sigma, sigma_inv, sutsv, sq1norm, sign, vtv;
  KINMem kin_mem;
  KINSpilsMem kinspils_mem;
  int retval;

  /* jac_data is kin_mem */

  kin_mem = (KINMem) jac_data;
  kinspils_mem = (KINSpilsMem) lmem;

  /* scale the vector v and put Du*v into vtemp1 */

  N_VProd(v, uscale, vtemp1);

  /* scale u and put into Jv (used as a temporary storage) */

  N_VProd(u, uscale, Jv);

  /* compute dot product (Du*u).(Du*v) */

  sutsv = N_VDotProd(Jv, vtemp1);

  /* compute dot product (Du*v).(Du*v) */

  vtv = N_VDotProd(vtemp1, vtemp1);

  sq1norm = N_VL1Norm(vtemp1);

  sign = (sutsv >= ZERO) ? ONE : -ONE ;
 
  /*  this expression for sigma is from p. 469, Brown and Saad paper */

  sigma = sign*sqrt_relfunc*MAX(ABS(sutsv),sq1norm)/vtv; 

  sigma_inv = ONE/sigma;

  /* compute the u-prime at which to evaluate the function func */

  N_VLinearSum(ONE, u, sigma, v, vtemp1);
 
  /* call the system function to calculate func(u+sigma*v) */

  retval = func(vtemp1, vtemp2, f_data);    
  nfes++;

  /* finish the computation of the difference quotient */

  N_VLinearSum(sigma_inv, vtemp2, -sigma_inv, fval, Jv);

  return(0);
}

