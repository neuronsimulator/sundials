/*
 * -----------------------------------------------------------------
 * $Revision: 1.5 $
 * $Date: 2006-05-31 15:33:48 $
 * ----------------------------------------------------------------- 
 * Programmer(s): Alan C. Hindmarsh and Radu Serban @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2002, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see sundials/ida/LICENSE.
 * -----------------------------------------------------------------
 * This is the implementation file for the IDA banded linear
 * solver module, IDABAND. This module uses standard banded
 * matrix techniques to solve the linear systems generated by the
 * (nonlinear) Newton iteration process. The user may either
 * supply a banded Jacobian routine or use the routine supplied
 * with this module (IDABandDQJac).
 * -----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ida_impl.h"
#include "ida_band_impl.h"

#include "sundials_math.h"

/* Constants */

#define ZERO         RCONST(0.0)
#define ONE          RCONST(1.0)
#define TWO          RCONST(2.0)

/* IDABAND linit, lsetup, lsolve, and lfree routines */
 
static int IDABandInit(IDAMem IDA_mem);

static int IDABandSetup(IDAMem IDA_mem, N_Vector yyp, N_Vector ypp,
                        N_Vector rrp, N_Vector tmp1,
                        N_Vector tmp2, N_Vector tmp3);

static int IDABandSolve(IDAMem IDA_mem, N_Vector b, N_Vector weight,
                        N_Vector ycur, N_Vector ypcur, N_Vector rrcur);

static int IDABandFree(IDAMem IDA_mem);

static int IDABandDQJac(long int Neq, long int mupper, long int mlower,
                        realtype tt, N_Vector yy, N_Vector yp, N_Vector rr,
                        realtype c_j, void *jac_data, BandMat Jac,
                        N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

/* Readability Replacements */

#define res         (IDA_mem->ida_res)
#define rdata       (IDA_mem->ida_rdata)
#define uround      (IDA_mem->ida_uround)
#define tn          (IDA_mem->ida_tn)
#define hh          (IDA_mem->ida_hh)
#define cj          (IDA_mem->ida_cj)
#define cjratio     (IDA_mem->ida_cjratio)
#define ewt         (IDA_mem->ida_ewt)
#define constraints (IDA_mem->ida_constraints)
#define nre         (IDA_mem->ida_nre)
#define iopt        (IDA_mem->ida_iopt)
#define linit       (IDA_mem->ida_linit)
#define lsetup      (IDA_mem->ida_lsetup)
#define lsolve      (IDA_mem->ida_lsolve)
#define lperf       (IDA_mem->ida_lperf)
#define lfree       (IDA_mem->ida_lfree)
#define lmem        (IDA_mem->ida_lmem)
#define setupNonNull (IDA_mem->ida_setupNonNull)
#define vec_tmpl     (IDA_mem->ida_tempv1)

#define neq         (idaband_mem->b_neq)
#define ml          (idaband_mem->b_mlower)
#define mu          (idaband_mem->b_mupper)
#define jac         (idaband_mem->b_jac)
#define JJ          (idaband_mem->b_J)
#define storage_mu  (idaband_mem->b_storage_mu)
#define pivots      (idaband_mem->b_pivots)
#define nje         (idaband_mem->b_nje)
#define nreB        (idaband_mem->b_nreB)
#define jacdata     (idaband_mem->b_jdata)
#define last_flag   (idaband_mem->b_last_flag)
                  
/*
 * -----------------------------------------------------------------
 * IDABand
 * -----------------------------------------------------------------
 * This routine initializes the memory record and sets various function
 * fields specific to the IDABAND linear solver module.
 * IDABand first calls the existing lfree routine if this is not NULL.
 * Then it sets the ida_linit, ida_lsetup, ida_lsolve, ida_lperf, and
 * ida_lfree fields in (*IDA_mem) to be IDABandInit, IDABandSetup,
 * IDABandSolve, NULL, and IDABandFree, respectively.
 * It allocates memory for a structure of type IDABandMemRec and sets
 * the ida_lmem field in (*IDA_mem) to the address of this structure.
 * It sets setupNonNull in (*IDA_mem) to TRUE, sets the b_jdata field in
 * the IDABandMemRec structure to be the input parameter jdata, and sets
 * the b_jac field to be:
 *   (1) the input parameter bjac, if bjac != NULL, or
 *   (2) IDABandDQJac, if bjac == NULL.
 * Finally, it allocates memory for JJ and pivots.
 * IDABand returns IDABAND_SUCCESS = 0, IDABAND_LMEM_FAIL = -1,
 * or IDABAND_ILL_INPUT = -2.
 *
 * NOTE: The band linear solver assumes a serial implementation
 *       of the NVECTOR package. Therefore, IDABand will first 
 *       test for a compatible N_Vector internal representation by
 *       checking that the N_VGetArrayPointer function exists
 * -----------------------------------------------------------------
 */

int IDABand(void *ida_mem, long int Neq, 
            long int mupper, long int mlower)
{
  IDAMem IDA_mem;
  IDABandMem idaband_mem;
  int flag;

  /* Return immediately if ida_mem is NULL. */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDABAND_MEM_NULL, "IDABAND", "IDABand", MSGB_IDAMEM_NULL);
    return(IDABAND_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  /* Test if the NVECTOR package is compatible with the BAND solver */
  if(vec_tmpl->ops->nvgetarraypointer == NULL) {
    IDAProcessError(IDA_mem, IDABAND_ILL_INPUT, "IDABAND", "IDABand", MSGB_BAD_NVECTOR);
    return(IDABAND_ILL_INPUT);
  }

  /* Test mlower and mupper for legality. */
  if ((mlower < 0) || (mupper < 0) || (mlower >= Neq) || (mupper >= Neq)) {
    IDAProcessError(IDA_mem, IDABAND_ILL_INPUT, "IDABAND", "IDABand", MSGB_BAD_SIZES);
    return(IDABAND_ILL_INPUT);
  }

  if (lfree != NULL) flag = lfree((IDAMem) ida_mem);

  /* Set five main function fields in ida_mem. */
  linit  = IDABandInit;
  lsetup = IDABandSetup;
  lsolve = IDABandSolve;
  lperf  = NULL;
  lfree  = IDABandFree;

  /* Get memory for IDABandMemRec. */
  idaband_mem = NULL;
  idaband_mem = (IDABandMem) malloc(sizeof(IDABandMemRec));
  if (idaband_mem == NULL) {
    IDAProcessError(IDA_mem, IDABAND_MEM_FAIL, "IDABAND", "IDABand", MSGB_MEM_FAIL);
    return(IDABAND_MEM_FAIL);
  }

  /* Set default Jacobian routine and Jacobian data */
  jac = IDABandDQJac;
  jacdata = IDA_mem;
  last_flag = IDABAND_SUCCESS;

  setupNonNull = TRUE;

  /* Store problem size */
  neq = Neq;

  idaband_mem->b_mlower = mlower;
  idaband_mem->b_mupper = mupper;
    
  /* Set extended upper half-bandwidth for JJ (required for pivoting). */
  storage_mu = MIN(Neq-1, mupper + mlower);

  /* Allocate memory for JJ and pivot array. */
  JJ = NULL;
  JJ = BandAllocMat(Neq, mupper, mlower, storage_mu);
  if (JJ == NULL) {
    IDAProcessError(IDA_mem, IDABAND_MEM_FAIL, "IDABAND", "IDABand", MSGB_MEM_FAIL);
    free(idaband_mem); idaband_mem = NULL;
    return(IDABAND_MEM_FAIL);
  }

  pivots = NULL;
  pivots = BandAllocPiv(Neq);
  if (pivots == NULL) {
    IDAProcessError(IDA_mem, IDABAND_MEM_FAIL, "IDABAND", "IDABand", MSGB_MEM_FAIL);
    BandFreeMat(JJ);
    free(idaband_mem); idaband_mem = NULL;
    return(IDABAND_MEM_FAIL);
  }  
  
  /* Attach linear solver memory to the integrator memory */
  lmem = idaband_mem;

  return(IDABAND_SUCCESS);
}

/*
 * -----------------------------------------------------------------
 * IDABandSet* and IDABandGet*
 * -----------------------------------------------------------------
 */

int IDABandSetJacFn(void *ida_mem, IDABandJacFn bjac, void *jac_data)
{
  IDAMem IDA_mem;
  IDABandMem idaband_mem;

  /* Return immediately if ida_mem is NULL */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDABAND_MEM_NULL, "IDABAND", "IDABandSetJacFn", MSGB_IDAMEM_NULL);
    return(IDABAND_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  if (lmem == NULL) {
    IDAProcessError(IDA_mem, IDABAND_LMEM_NULL, "IDABAND", "IDABandSetJacFn", MSGB_LMEM_NULL);
    return(IDABAND_LMEM_NULL);
  }
  idaband_mem = (IDABandMem) lmem;

  jac = bjac;
  if (bjac != NULL) jacdata = jac_data;

  return(IDABAND_SUCCESS);
}

int IDABandGetWorkSpace(void *ida_mem, long int *lenrwLS, long int *leniwLS)
{
  IDAMem IDA_mem;
  IDABandMem idaband_mem;

  /* Return immediately if ida_mem is NULL */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDABAND_MEM_NULL, "IDABAND", "IDABandGetWorkSpace", MSGB_IDAMEM_NULL);
    return(IDABAND_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  if (lmem == NULL) {
    IDAProcessError(IDA_mem, IDABAND_LMEM_NULL, "IDABAND", "IDABandGetWorkSpace", MSGB_LMEM_NULL);
    return(IDABAND_LMEM_NULL);
  }
  idaband_mem = (IDABandMem) lmem;

  *lenrwLS = neq*(storage_mu + ml + 1);
  *leniwLS = neq;

  return(IDABAND_SUCCESS);
}

int IDABandGetNumJacEvals(void *ida_mem, long int *njevals)
{
  IDAMem IDA_mem;
  IDABandMem idaband_mem;

  /* Return immediately if ida_mem is NULL */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDABAND_MEM_NULL, "IDABAND", "IDABandGetNumJacEvals", MSGB_IDAMEM_NULL);
    return(IDABAND_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  if (lmem == NULL) {
    IDAProcessError(IDA_mem, IDABAND_LMEM_NULL, "IDABAND", "IDABandGetNumJacEvals", MSGB_LMEM_NULL);
    return(IDABAND_LMEM_NULL);
  }
  idaband_mem = (IDABandMem) lmem;

  *njevals = nje;

  return(IDABAND_SUCCESS);
}

int IDABandGetNumResEvals(void *ida_mem, long int *nrevalsLS)
{
  IDAMem IDA_mem;
  IDABandMem idaband_mem;

  /* Return immediately if ida_mem is NULL */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDABAND_MEM_NULL, "IDABAND", "IDABandGetNumResEvals", MSGB_IDAMEM_NULL);
    return(IDABAND_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  if (lmem == NULL) {
    IDAProcessError(IDA_mem, IDABAND_LMEM_NULL, "IDABAND", "IDABandGetNumResEvals", MSGB_LMEM_NULL);
    return(IDABAND_LMEM_NULL);
  }
  idaband_mem = (IDABandMem) lmem;

  *nrevalsLS = nreB;

  return(IDABAND_SUCCESS);
}

int IDABandGetLastFlag(void *ida_mem, int *flag)
{
  IDAMem IDA_mem;
  IDABandMem idaband_mem;

  /* Return immediately if ida_mem is NULL */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDABAND_MEM_NULL, "IDABAND", "IDABandGetLastFlag", MSGB_IDAMEM_NULL);
    return(IDABAND_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  if (lmem == NULL) {
    IDAProcessError(IDA_mem, IDABAND_LMEM_NULL, "IDABAND", "IDABandGetLastFlag", MSGB_LMEM_NULL);
    return(IDABAND_LMEM_NULL);
  }
  idaband_mem = (IDABandMem) lmem;

  *flag = last_flag;

  return(IDABAND_SUCCESS);
}

char *IDABandGetReturnFlagName(int flag)
{
  char *name;

  name = (char *)malloc(30*sizeof(char));

  switch(flag) {
  case IDABAND_SUCCESS:
    sprintf(name,"IDABAND_SUCCESS");
    break;   
  case IDABAND_MEM_NULL:
    sprintf(name,"IDABAND_MEM_NULL");
    break;
  case IDABAND_LMEM_NULL:
    sprintf(name,"IDABAND_LMEM_NULL");
    break;
  case IDABAND_ILL_INPUT:
    sprintf(name,"IDABAND_ILL_INPUT");
    break;
  case IDABAND_MEM_FAIL:
    sprintf(name,"IDABAND_MEM_FAIL");
    break;
  case IDABAND_JACFUNC_UNRECVR:
    sprintf(name,"IDABAND_JACFUNC_UNRECVR");
    break;
  case IDABAND_JACFUNC_RECVR:
    sprintf(name,"IDABAND_JACFUNC_RECVR");
    break;
  default:
    sprintf(name,"NONE");
  }

  return(name);
}

/*
 * -----------------------------------------------------------------
 * IDABAND interface functions
 * -----------------------------------------------------------------
 */

/*
  This routine does remaining initializations specific to the IDABAND
  linear solver module.  It returns 0.
*/

static int IDABandInit(IDAMem IDA_mem)
{
  IDABandMem idaband_mem;

  idaband_mem = (IDABandMem) lmem;

  /* Initialize nje and nreB */
  nje  = 0;
  nreB = 0;

  if (jac == NULL) {
    jac = IDABandDQJac;
    jacdata = IDA_mem;
  }

  last_flag = 0;
  return(0);
}


/*
  This routine does the setup operations for the IDABAND linear 
  solver module.  It calls the Jacobian evaluation routine,
  updates counters, and calls the band LU factorization routine.
  The return value is either
     IDABAND_SUCCESS = 0  if successful,
     +1  if the jac routine failed recoverably or the
         LU factorization failed, or
     -1  if the jac routine failed unrecoverably.
*/

static int IDABandSetup(IDAMem IDA_mem, N_Vector yyp, N_Vector ypp,
                        N_Vector rrp, N_Vector tmp1, N_Vector tmp2,
                        N_Vector tmp3)
{
  int retval;
  long int retfac;
  IDABandMem idaband_mem;
  
  idaband_mem = (IDABandMem) lmem;

  /* Increment nje counter. */
  nje++;

  /* Zero out JJ; call Jacobian routine jac; return if it failed. */
  BandZero(JJ);
  retval = jac(neq, mu, ml, tn, yyp, ypp, rrp, cj,
               jacdata, JJ, tmp1, tmp2, tmp3);
  if (retval < 0) {
    IDAProcessError(IDA_mem, IDABAND_JACFUNC_UNRECVR, "IDABAND", "IDABandSetup", MSGB_JACFUNC_FAILED);
    last_flag = IDABAND_JACFUNC_UNRECVR;
    return(-1);
  }
  if (retval > 0) {
    last_flag = IDABAND_JACFUNC_RECVR;
    return(+1);
  }

  /* Do LU factorization of JJ; return success or fail flag. */
  retfac = BandFactor(JJ, pivots);
  
  if (retfac != 0) {
    last_flag = retfac;
    return(+1);
  }
  last_flag = IDABAND_SUCCESS;
  return(0);
}
/*
  This routine handles the solve operation for the IDABAND linear
  solver module.  It calls the band backsolve routine, scales the
  solution vector according to cjratio, then returns IDABAND_SUCCESS = 0.
*/

static int IDABandSolve(IDAMem IDA_mem, N_Vector b, N_Vector weight,
                        N_Vector ycur, N_Vector ypcur, N_Vector rrcur)
{
  IDABandMem idaband_mem;
  realtype *bd;

  idaband_mem = (IDABandMem) lmem;
  
  bd = N_VGetArrayPointer(b);
  BandBacksolve(JJ, pivots, bd);

  /* Scale the correction to account for change in cj. */
  if (cjratio != ONE) N_VScale(TWO/(ONE + cjratio), b, b);
  
  last_flag = 0;
  return(0);
}

/*
  This routine frees memory specific to the IDABAND linear solver.
*/

static int IDABandFree(IDAMem IDA_mem)
{
  IDABandMem idaband_mem;

  idaband_mem = (IDABandMem) lmem;
  
  BandFreeMat(JJ);
  BandFreePiv(pivots);
  free(lmem); lmem = NULL;

  return(0);

}

/*
 * -----------------------------------------------------------------
 * IDABAND private routines
 * -----------------------------------------------------------------
 */

/*
  This routine generates a banded difference quotient approximation JJ
  to the DAE system Jacobian J.  It assumes that a band matrix of type
  BandMat is stored column-wise, and that elements within each column
  are contiguous.  The address of the jth column of JJ is obtained via
  the macros BAND_COL and BAND_COL_ELEM. The columns of the Jacobian are 
  constructed using mupper + mlower + 1 calls to the res routine, and
  appropriate differencing.
  The return value is either IDABAND_SUCCESS = 0, or the nonzero value returned
  by the res routine, if any.
*/

static int IDABandDQJac(long int Neq, long int mupper, long int mlower,
                        realtype tt, N_Vector yy, N_Vector yp, N_Vector rr,
                        realtype c_j, void *jac_data, BandMat Jac,
                        N_Vector tmp1, N_Vector tmp2, N_Vector tmp3)
{
  realtype inc, inc_inv, yj, ypj, srur, conj, ewtj;
  realtype *y_data, *yp_data, *ewt_data, *cns_data = NULL;
  realtype *ytemp_data, *yptemp_data, *rtemp_data, *r_data, *col_j;
  int group;
  
  N_Vector rtemp, ytemp, yptemp;
  long int i, j, i1, i2, width, ngroups;
  int retval = IDABAND_SUCCESS;

  IDAMem IDA_mem;
  IDABandMem idaband_mem;

  /* jac_data points to IDA_mem */
  IDA_mem = (IDAMem) jac_data;
  idaband_mem = (IDABandMem) lmem;

  rtemp = tmp1; /* Rename work vector for use as the perturbed residual. */

  ytemp = tmp2; /* Rename work vector for use as a temporary for yy. */


  yptemp= tmp3; /* Rename work vector for use as a temporary for yp. */

  /* Obtain pointers to the data for all eight vectors used.  */

  ewt_data = N_VGetArrayPointer(ewt);
  r_data   = N_VGetArrayPointer(rr);
  y_data   = N_VGetArrayPointer(yy);
  yp_data  = N_VGetArrayPointer(yp);

  rtemp_data  = N_VGetArrayPointer(rtemp);
  ytemp_data  = N_VGetArrayPointer(ytemp);
  yptemp_data = N_VGetArrayPointer(yptemp);

  if (constraints != NULL) cns_data = N_VGetArrayPointer(constraints);

  /* Initialize ytemp and yptemp. */

  N_VScale(ONE, yy, ytemp);
  N_VScale(ONE, yp, yptemp);

  /* Compute miscellaneous values for the Jacobian computation. */

  srur = RSqrt(uround);
  width = mlower + mupper + 1;
  ngroups = MIN(width, neq);

  /* Loop over column groups. */
  for (group=1; group <= ngroups; group++) {

    /* Increment all yy[j] and yp[j] for j in this group. */

    for (j=group-1; j<Neq; j+=width) {
        yj = y_data[j];
        ypj = yp_data[j];
        ewtj = ewt_data[j];

        /* Set increment inc to yj based on sqrt(uround)*abs(yj), with
           adjustments using ypj and ewtj if this is small, and a further
           adjustment to give it the same sign as hh*ypj. */

        inc = MAX( srur * MAX( ABS(yj), ABS(hh*ypj) ) , ONE/ewtj );

        if (hh*ypj < ZERO) inc = -inc;
        inc = (yj + inc) - yj;

        /* Adjust sign(inc) again if yj has an inequality constraint. */

        if (constraints != NULL) {
          conj = cns_data[j];
          if (ABS(conj) == ONE)      {if((yj+inc)*conj <  ZERO) inc = -inc;}
          else if (ABS(conj) == TWO) {if((yj+inc)*conj <= ZERO) inc = -inc;}
        }

        /* Increment yj and ypj. */

        ytemp_data[j] += inc;
        yptemp_data[j] += cj*inc;
    }

    /* Call res routine with incremented arguments. */

    retval = res(tt, ytemp, yptemp, rtemp, rdata);
    nreB++;
    if (retval != IDABAND_SUCCESS) break;

    /* Loop over the indices j in this group again. */

    for (j=group-1; j<Neq; j+=width) {

      /* Reset ytemp and yptemp components that were perturbed. */

      yj = ytemp_data[j]  = y_data[j];
      ypj = yptemp_data[j] = yp_data[j];
      col_j = BAND_COL(Jac, j);
      ewtj = ewt_data[j];
      
      
      /* Set increment inc exactly as above. */
      
      inc = MAX( srur * MAX( ABS(yj), ABS(hh*ypj) ) , ONE/ewtj );
      if (hh*ypj < ZERO) inc = -inc;
      inc = (yj + inc) - yj;
      if (constraints != NULL) {
        conj = cns_data[j];
        if (ABS(conj) == ONE)      {if((yj+inc)*conj <  ZERO) inc = -inc;}
        else if (ABS(conj) == TWO) {if((yj+inc)*conj <= ZERO) inc = -inc;}
      }
      
      /* Load the difference quotient Jacobian elements for column j. */

      inc_inv = ONE/inc;
      i1 = MAX(0, j-mupper);
      i2 = MIN(j+mlower,neq-1);
      
      for (i=i1; i<=i2; i++) 
            BAND_COL_ELEM(col_j,i,j) = inc_inv*(rtemp_data[i]-r_data[i]);
    }
    
  }
  
  return(retval);
  
}
