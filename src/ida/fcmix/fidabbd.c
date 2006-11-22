/*
 * -----------------------------------------------------------------
 * $Revision: 1.2 $
 * $Date: 2006-11-22 00:12:50 $
 * ----------------------------------------------------------------- 
 * Programmer(s): Aaron Collier @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2005, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see the LICENSE file.
 * -----------------------------------------------------------------
 * This module contains the routines necessary to interface with the
 * IDABBDPRE module and user-supplied Fortran routines.
 * The routines here call the generically named routines and provide
 * a standard interface to the C code of the IDABBDPRE package.
 * -----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#include "fida.h"            /* function names, prototypes, global variables */
#include "fidabbd.h"         /* prototypes of interfaces to IDABBD           */

#include <ida/ida_bbdpre.h>  /* prototypes of IDABBDPRE functions and macros */
#include <ida/ida_spgmr.h>   /* prototypes of IDASPGMR interface routines    */
#include <ida/ida_spbcgs.h>  /* prototypes of IDASPBCG interface routines    */
#include <ida/ida_sptfqmr.h> /* prototypes of IDASPTFQMR interface routines  */

/*************************************************/

/* private constant(s) */

#define ZERO RCONST(0.0)

/*************************************************/

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

  extern void FIDA_GLOCFN(int*, 
                          realtype*, realtype*, realtype*, realtype*, 
                          long int*, realtype*,
                          int*);
  extern void FIDA_COMMFN(int*, 
                          realtype*, realtype*, realtype*, 
                          long int*, realtype*,
                          int*);

#ifdef __cplusplus
}
#endif

/*************************************************/

void FIDA_BBDINIT(int *Nloc, int *mudq, int *mldq,
		  int *mu, int *ml, realtype *dqrely, int *ier)
{
  IDABBD_Data = IDABBDPrecAlloc(IDA_idamem, *Nloc, *mudq, *mldq, *mu, *ml,
				*dqrely, (IDABBDLocalFn) FIDAgloc, (IDABBDCommFn) FIDAcfn);
  if (IDABBD_Data == NULL) *ier = -1;
  else *ier = 0;

  return;
}

/*************************************************/

void FIDA_BBDSPTFQMR(int *maxl, realtype *eplifac, realtype *dqincfac, int *ier)
{
  *ier = 0;

  *ier = IDABBDSptfqmr(IDA_idamem, *maxl, IDABBD_Data);
  if (*ier != IDASPILS_SUCCESS) return;

  *ier = IDASpilsSetEpsLin(IDA_idamem, *eplifac);
  if (*ier != IDASPILS_SUCCESS) return;

  if (*dqincfac != ZERO) {
    *ier = IDASpilsSetIncrementFactor(IDA_idamem, *dqincfac);
    if (*ier != IDASPILS_SUCCESS) return;
  }

  IDA_ls = IDA_LS_SPTFQMR;

  return;
}

/*************************************************/

void FIDA_BBDSPBCG(int *maxl, realtype *eplifac, realtype *dqincfac, int *ier)
{
  *ier = 0;

  *ier = IDABBDSpbcg(IDA_idamem, *maxl, IDABBD_Data);
  if (*ier != IDASPILS_SUCCESS) return;

  *ier = IDASpilsSetEpsLin(IDA_idamem, *eplifac);
  if (*ier != IDASPILS_SUCCESS) return;

  if (*dqincfac != ZERO) {
    *ier = IDASpilsSetIncrementFactor(IDA_idamem, *dqincfac);
    if (*ier != IDASPILS_SUCCESS) return;
  }

  IDA_ls = IDA_LS_SPBCG;

  return;
}

/*************************************************/

void FIDA_BBDSPGMR(int *maxl, int *gstype, int *maxrs,
		   realtype *eplifac, realtype *dqincfac, int *ier)
{
  *ier = 0;

  *ier = IDABBDSpgmr(IDA_idamem, *maxl, IDABBD_Data);
  if (*ier != IDASPILS_SUCCESS) return;

  if (*gstype != 0) {
    *ier = IDASpilsSetGSType(IDA_idamem, *gstype);
    if (*ier != IDASPILS_SUCCESS) return;
  }

  if (*maxrs != 0) {
    *ier = IDASpilsSetMaxRestarts(IDA_idamem, *maxrs);
    if (*ier != IDASPILS_SUCCESS) return;
  }

  *ier = IDASpilsSetEpsLin(IDA_idamem, *eplifac);
  if (*ier != IDASPILS_SUCCESS) return;

  if (*dqincfac != ZERO) {
    *ier = IDASpilsSetIncrementFactor(IDA_idamem, *dqincfac);
    if (*ier != IDASPILS_SUCCESS) return;
  }

  IDA_ls = IDA_LS_SPGMR;

  return;
}

/*************************************************/

void FIDA_BBDREINIT(int *Nloc, int *mudq, int *mldq,
		    realtype *dqrely, int *ier)
{
  *ier = 0;

  *ier = IDABBDPrecReInit(IDABBD_Data, *mudq, *mldq,
			  *dqrely, (IDABBDLocalFn) FIDAgloc, (IDABBDCommFn) FIDAcfn);

  return;
}

/*************************************************/

int FIDAgloc(int Nloc, realtype t, N_Vector yy, N_Vector yp,
	     N_Vector gval, void *res_data)
{
  realtype *yy_data, *yp_data, *gval_data;
  int ier;
  FIDAUserData IDA_userdata;

  /* Initialize all pointers to NULL */
  yy_data = yp_data = gval_data = NULL;

  /* NOTE: The user-supplied routine should set ier to an
     appropriate value, but we preset the value to zero
     (meaning SUCCESS) so the user need only reset the
     value if an error occurred */
  ier = 0;

  /* Get pointers to vector data */
  yy_data   = N_VGetArrayPointer(yy);
  yp_data   = N_VGetArrayPointer(yp);
  gval_data = N_VGetArrayPointer(gval);

  IDA_userdata = (FIDAUserData) res_data;

  /* Call user-supplied routine */
  FIDA_GLOCFN(&Nloc, &t, yy_data, yp_data, gval_data, 
              IDA_userdata->ipar, IDA_userdata->rpar, &ier);

  return(ier);
}

/*************************************************/

int FIDAcfn(int Nloc, realtype t, N_Vector yy, N_Vector yp,
	    void *res_data)
{
  realtype *yy_data, *yp_data;
  int ier;
  FIDAUserData IDA_userdata;

  /* Initialize all pointers to NULL */
  yy_data = yp_data = NULL;

  /* NOTE: The user-supplied routine should set ier to an
     appropriate value, but we preset the value to zero
     (meaning SUCCESS) so the user need only reset the
     value if an error occurred */
  ier = 0;

  /* Get pointers to vector data */
  yy_data = N_VGetArrayPointer(yy);
  yp_data = N_VGetArrayPointer(yp);

  IDA_userdata = (FIDAUserData) res_data;

  /* Call user-supplied routine */
  FIDA_COMMFN(&Nloc, &t, yy_data, yp_data, 
              IDA_userdata->ipar, IDA_userdata->rpar, &ier);

  return(ier);
}

/*************************************************/

void FIDA_BBDOPT(long int *lenrwbbd, long int *leniwbbd, long int *ngebbd)
{
  IDABBDPrecGetWorkSpace(IDABBD_Data, lenrwbbd, leniwbbd);
  IDABBDPrecGetNumGfnEvals(IDABBD_Data, ngebbd);

  return;
}

/*************************************************/

void FIDA_BBDFREE(void)
{
  IDABBDPrecFree(&IDABBD_Data);

  return;
}
