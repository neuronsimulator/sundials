/*
 * -----------------------------------------------------------------
 * $Revision: 1.5 $
 * $Date: 2006-11-22 00:12:50 $
 * ----------------------------------------------------------------- 
 * Programmer(s): Alan C. Hindmarsh and Radu Serban @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2002, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see the LICENSE file.
 * -----------------------------------------------------------------
 * This is the implementation file for the IDAS banded linear
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

#include <idas/idas_band.h>
#include "idas_direct_impl.h"
#include "idas_impl.h"

#include <sundials/sundials_math.h>

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

/* IDABAND lfreeB function */

static void IDABandFreeB(IDAadjMem IDAADJ_mem);

/* 
 * ================================================================
 *
 *                   PART I - forward problems
 *
 * ================================================================
 */

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
#define linit       (IDA_mem->ida_linit)
#define lsetup      (IDA_mem->ida_lsetup)
#define lsolve      (IDA_mem->ida_lsolve)
#define lperf       (IDA_mem->ida_lperf)
#define lfree       (IDA_mem->ida_lfree)
#define lmem        (IDA_mem->ida_lmem)
#define setupNonNull (IDA_mem->ida_setupNonNull)
#define vec_tmpl     (IDA_mem->ida_tempv1)

#define mtype       (idadls_mem->d_type)
#define neq         (idadls_mem->d_n)
#define ml          (idadls_mem->d_ml)
#define mu          (idadls_mem->d_mu)
#define bjac        (idadls_mem->d_bjac)
#define JJ          (idadls_mem->d_J)
#define smu         (idadls_mem->d_smu)
#define pivots      (idadls_mem->d_pivots)
#define nje         (idadls_mem->d_nje)
#define nreDQ       (idadls_mem->d_nreDQ)
#define jacdata     (idadls_mem->d_J_data)
#define last_flag   (idadls_mem->d_last_flag)
                  
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
 * It allocates memory for a structure of type IDADlsMemRec and sets
 * the ida_lmem field in (*IDA_mem) to the address of this structure.
 * It sets setupNonNull in (*IDA_mem) to TRUE, sets the d_jacdata field in
 * the IDADlsMemRec structure to be the input parameter jdata, and sets
 * the d_bjac field to be:
 *   (1) the input parameter bjac, if bjac != NULL, or
 *   (2) IDABandDQJac, if bjac == NULL.
 * Finally, it allocates memory for JJ and pivots.
 * IDABand returns IDADIRECT_SUCCESS = 0, IDADIRECT_LMEM_FAIL = -1,
 * or IDADIRECT_ILL_INPUT = -2.
 *
 * NOTE: The band linear solver assumes a serial implementation
 *       of the NVECTOR package. Therefore, IDABand will first 
 *       test for a compatible N_Vector internal representation by
 *       checking that the N_VGetArrayPointer function exists
 * -----------------------------------------------------------------
 */

int IDABand(void *ida_mem, int Neq, int mupper, int mlower)
{
  IDAMem IDA_mem;
  IDADlsMem idadls_mem;
  int flag;

  /* Return immediately if ida_mem is NULL. */
  if (ida_mem == NULL) {
    IDAProcessError(NULL, IDADIRECT_MEM_NULL, "IDASBAND", "IDABand", MSGD_IDAMEM_NULL);
    return(IDADIRECT_MEM_NULL);
  }
  IDA_mem = (IDAMem) ida_mem;

  /* Test if the NVECTOR package is compatible with the BAND solver */
  if(vec_tmpl->ops->nvgetarraypointer == NULL) {
    IDAProcessError(IDA_mem, IDADIRECT_ILL_INPUT, "IDASBAND", "IDABand", MSGD_BAD_NVECTOR);
    return(IDADIRECT_ILL_INPUT);
  }

  /* Test mlower and mupper for legality. */
  if ((mlower < 0) || (mupper < 0) || (mlower >= Neq) || (mupper >= Neq)) {
    IDAProcessError(IDA_mem, IDADIRECT_ILL_INPUT, "IDASBAND", "IDABand", MSGD_BAD_SIZES);
    return(IDADIRECT_ILL_INPUT);
  }

  if (lfree != NULL) flag = lfree((IDAMem) ida_mem);

  /* Set five main function fields in ida_mem. */
  linit  = IDABandInit;
  lsetup = IDABandSetup;
  lsolve = IDABandSolve;
  lperf  = NULL;
  lfree  = IDABandFree;

  /* Get memory for IDADlsMemRec. */
  idadls_mem = NULL;
  idadls_mem = (IDADlsMem) malloc(sizeof(IDADlsMemRec));
  if (idadls_mem == NULL) {
    IDAProcessError(IDA_mem, IDADIRECT_MEM_FAIL, "IDASBAND", "IDABand", MSGD_MEM_FAIL);
    return(IDADIRECT_MEM_FAIL);
  }

  /* Set matrix type */
  mtype = SUNDIALS_BAND;

  /* Set default Jacobian routine and Jacobian data */
  bjac = idaDlsBandDQJac;
  jacdata = IDA_mem;
  last_flag = IDADIRECT_SUCCESS;

  setupNonNull = TRUE;

  /* Store problem size */
  neq = Neq;

  idadls_mem->d_ml = mlower;
  idadls_mem->d_mu = mupper;
    
  /* Set extended upper half-bandwidth for JJ (required for pivoting). */
  smu = MIN(Neq-1, mupper + mlower);

  /* Allocate memory for JJ and pivot array. */
  JJ = NULL;
  JJ = NewBandMat(Neq, mupper, mlower, smu);
  if (JJ == NULL) {
    IDAProcessError(IDA_mem, IDADIRECT_MEM_FAIL, "IDASBAND", "IDABand", MSGD_MEM_FAIL);
    free(idadls_mem); idadls_mem = NULL;
    return(IDADIRECT_MEM_FAIL);
  }

  pivots = NULL;
  pivots = NewIntArray(Neq);
  if (pivots == NULL) {
    IDAProcessError(IDA_mem, IDADIRECT_MEM_FAIL, "IDASBAND", "IDABand", MSGD_MEM_FAIL);
    DestroyMat(JJ);
    free(idadls_mem); idadls_mem = NULL;
    return(IDADIRECT_MEM_FAIL);
  }  
  
  /* Attach linear solver memory to the integrator memory */
  lmem = idadls_mem;

  return(IDADIRECT_SUCCESS);
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
  IDADlsMem idadls_mem;

  idadls_mem = (IDADlsMem) lmem;

  /* Initialize nje and nreB */
  nje   = 0;
  nreDQ = 0;

  if (bjac == NULL) {
    bjac = idaDlsBandDQJac;
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
     IDADIRECT_SUCCESS = 0  if successful,
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
  IDADlsMem idadls_mem;
  
  idadls_mem = (IDADlsMem) lmem;

  /* Increment nje counter. */
  nje++;

  /* Zero out JJ; call Jacobian routine jac; return if it failed. */
  BandZero(JJ);
  retval = bjac(neq, mu, ml, tn,  cj, yyp, ypp, rrp,
                JJ, jacdata, tmp1, tmp2, tmp3);
  if (retval < 0) {
    IDAProcessError(IDA_mem, IDADIRECT_JACFUNC_UNRECVR, "IDASBAND", "IDABandSetup", MSGD_JACFUNC_FAILED);
    last_flag = IDADIRECT_JACFUNC_UNRECVR;
    return(-1);
  }
  if (retval > 0) {
    last_flag = IDADIRECT_JACFUNC_RECVR;
    return(+1);
  }

  /* Do LU factorization of JJ; return success or fail flag. */
  retfac = BandGBTRF(JJ, pivots);
  
  if (retfac != 0) {
    last_flag = retfac;
    return(+1);
  }
  last_flag = IDADIRECT_SUCCESS;
  return(0);
}
/*
  This routine handles the solve operation for the IDABAND linear
  solver module.  It calls the band backsolve routine, scales the
  solution vector according to cjratio, then returns IDADIRECT_SUCCESS = 0.
*/

static int IDABandSolve(IDAMem IDA_mem, N_Vector b, N_Vector weight,
                        N_Vector ycur, N_Vector ypcur, N_Vector rrcur)
{
  IDADlsMem idadls_mem;
  realtype *bd;

  idadls_mem = (IDADlsMem) lmem;
  
  bd = N_VGetArrayPointer(b);
  BandGBTRS(JJ, pivots, bd);

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
  IDADlsMem idadls_mem;

  idadls_mem = (IDADlsMem) lmem;
  
  DestroyMat(JJ);
  DestroyArray(pivots);
  free(lmem); lmem = NULL;

  return(0);

}

/* 
 * ================================================================
 *
 *                   PART II - backward problems
 *
 * ================================================================
 */


/*
 * IDABandB is a wrapper around IDABand.
 */

int IDABandB(void *idaadj_mem, int NeqB, int mupperB, int mlowerB)
{
  IDAadjMem IDAADJ_mem;
  IDADlsMemB idadlsB_mem;
  IDAMem IDAB_mem;
  int flag;

  if (idaadj_mem == NULL) {
    IDAProcessError(NULL, IDADIRECT_ADJMEM_NULL, "IDASBAND", "IDABandB", MSGD_IDAMEM_NULL);
    return(IDADIRECT_ADJMEM_NULL);
  }
  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  IDAB_mem = (IDAMem) IDAADJ_mem->IDAB_mem;
  
  /* Get memory for IDADlsMemRecB */
  idadlsB_mem = (IDADlsMemB) malloc(sizeof(IDADlsMemRecB));
  if (idadlsB_mem == NULL) {
    IDAProcessError(IDAB_mem, IDADIRECT_MEM_FAIL, "IDASBAND", "IDABandB", MSGD_MEM_FAIL);
    return(IDADIRECT_MEM_FAIL);
  }

  /* set matrix type */
  idadlsB_mem->d_typeB = SUNDIALS_BAND;

  idadlsB_mem->d_bjacB = NULL;
  idadlsB_mem->d_jac_dataB = NULL;

  /* attach lmemB and lfreeB */
  IDAADJ_mem->ia_lmemB = idadlsB_mem;
  IDAADJ_mem->ia_lfreeB = IDABandFreeB;

  flag = IDABand(IDAB_mem, NeqB, mupperB, mlowerB);

  if (flag != IDADIRECT_SUCCESS) {
    free(idadlsB_mem);
    idadlsB_mem = NULL;
  }

  return(flag);
}

/*
 * IDABandFreeB 
 */

static void IDABandFreeB(IDAadjMem IDAADJ_mem)
{
  IDADlsMemB idadlsB_mem;

  idadlsB_mem = (IDADlsMemB) IDAADJ_mem->ia_lmemB;

  free(idadlsB_mem);
}

