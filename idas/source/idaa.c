/*******************************************************************
 * File          : idaa.c                                          *
 * Programmers   : Radu Serban @ LLNL                              *
 * Version of    : 07 February 2004                                *
 *-----------------------------------------------------------------*
 * Copyright (c) 2002, The Regents of the University of California * 
 * Produced at the Lawrence Livermore National Laboratory          *
 * All rights reserved                                             *
 * For details, see sundials/idas/LICENSE                          *
 *-----------------------------------------------------------------*
 * This is the implementation file for the IDAA adjoint integrator.*
 *******************************************************************/

/*=================================================================*/
/*BEGIN             Import Header Files                            */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "idaa.h"
#include "sundialsmath.h"

/*=================================================================*/
/*END               Import Header Files                            */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             Macros                                         */
/*=================================================================*/

/* Macro: loop */

#define loop for(;;)

/*=================================================================*/
/*END               Macros                                         */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             IDAA Private Constants                       */
/*=================================================================*/

#define ZERO        RCONST(0.0)     /* real 0.0 */
#define ONE         RCONST(1.0)     /* real 1.0 */
#define TWO         RCONST(2.0)     /* real 2.0 */
#define FUZZ_FACTOR RCONST(1000000.0)  /* fuzz factor for IDAAgetY */

/* return values from IDAAgetY */
#define GETY_OK    0
#define GETY_BADT -1

/*=================================================================*/
/*END               IDAA Private Constants                       */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             Error Messages                                 */
/*=================================================================*/

#define IDAAM                "IDAAdjMalloc-- "
#define MSG_IDAAM_NO_MEM     IDAAM "ida_mem=NULL illegal.\n\n"
#define MSG_IDAAM_BAD_STEPS  IDAAM "steps non-positive illegal.\n\n"
#define MSG_IDAAM_MEM_FAIL   IDAAM "a memory request failed.\n\n"

#define IDAF                 "IDASolveF-- "
#define MSG_IDASOLVEF_MEM_FAIL IDAF "a memory request failed.\n\n"

#define IDABM                "IDAMallocB/IDAReInitB-- "
#define MSG_IDABM_NO_MEM     IDABM "idaadj_mem=NULL illegal.\n\n"
#define MSG_IDABM_BAD_TB0    IDABM "tB0 out of range.\n\n"
#define MSG_IDABM_MEM_FAIL   IDABM "a memory request failed.\n\n"

#define IDABQM               "IDAQuadMallocB-- "
#define MSG_IDABQM_NO_MEM    IDABQM "idaadj_mem=NULL illegal.\n\n"
#define MSG_BAD_ECONQB_1     IDABQM "errconQB=%d illegal.\n"
#define MSG_BAD_ECONQB_2     "The legal values are FULL=%d and PARTIAL=%d.\n\n"
#define MSG_BAD_ECONQB       MSG_BAD_ECONQB_1 MSG_BAD_ECONQB_2

#define IDAB                 "IDASOLVEBB-- "
#define MSG_IDASOLVEB_FWD    IDAB "an error occured during the forward phase.\n\n"
#define MSG_IDASOLVEB_BCK    IDAB "an error occured during the backward phase.\n\n"

/*=================================================================*/
/*END               Error Messages                                 */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             Private Functions Prototypes                   */
/*=================================================================*/

static CkpntMem IDAAckpntInit(IDAMem IDA_mem);
static CkpntMem IDAAckpntNew(IDAMem IDA_mem);
static void IDAAckpntDelete(CkpntMem *ck_memPtr);

static DtpntMem *IDAAdataMalloc(IDAMem IDA_mem, long int steps);
static void IDAAdataFree(DtpntMem *dt_mem, long int steps);
static int  IDAAdataStore(IDAadjMem IDAADJ_mem, CkpntMem ck_mem);


static int  IDAAgetY(void *idaadj_mem, realtype t, N_Vector yy, N_Vector yp);
static void IDAAhermitePrepare(IDAadjMem IDAADJ_mem, DtpntMem *dt_mem, long int i);
static void IDAAhermiteInterpolate(IDAadjMem IDAADJ_mem, DtpntMem *dt_mem,
                                   long int i, realtype t, N_Vector y, N_Vector yd);

static int IDAAres(realtype tres, 
                    N_Vector yyB, N_Vector ypB, N_Vector resvalB, 
                    void *idaadj_mem);

static void IDAArhsQ(realtype tres, N_Vector yyB, N_Vector ypB,
                     N_Vector ypQB, void *idaadj_mem);

static int IDAAdenseJac(long int NeqB, realtype t, N_Vector yyB, 
                        N_Vector ypB, realtype cjB, void *idaadj_mem, 
                        N_Vector resvecB, DenseMat JacB, 
                        N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B);

static int IDAAbandJac(long int NeqB, long int mupperB, 
                       long int mlowerB, realtype t, 
                       N_Vector yyB, N_Vector ypB, realtype cjB, 
                       void *idaadj_mem, N_Vector resvecB, BandMat JacB, 
                       N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B);

static int IDAAspgmrPrecSetup(realtype t, 
                              N_Vector yyB, N_Vector ypB, N_Vector rrB, 
                              realtype cjB, void *idaadj_mem,
                              N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B);
static int IDAAspgmrPrecSolve(realtype t, 
                              N_Vector yyB, N_Vector ypB, N_Vector rrB, 
                              N_Vector rvecB, N_Vector zvecB,
                              realtype cjb, realtype deltaB,
                              void *idaadj_mem, N_Vector tmpB);
static int IDAAspgmrJacTimesVec(N_Vector vB, N_Vector JvB, realtype t,
                                N_Vector yyB, N_Vector ypB, N_Vector rrB,
                                realtype cjB, void *idaadj_mem, 
                                N_Vector tmp1B, N_Vector tmp2B);

/*=================================================================*/
/*END               Private Functions Prototypes                   */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             Readibility Constants                          */
/*=================================================================*/

/* IDAADJ memory block */

#define uround     (IDAADJ_mem->ia_uround)
#define tinitial   (IDAADJ_mem->ia_tinitial)
#define tfinal     (IDAADJ_mem->ia_tfinal)
#define nckpnts    (IDAADJ_mem->ia_nckpnts)
#define nsteps     (IDAADJ_mem->ia_nsteps)
#define ckpntData  (IDAADJ_mem->ia_ckpntData)
#define newData    (IDAADJ_mem->ia_newData)
#define np         (IDAADJ_mem->ia_np)
#define dt         (IDAADJ_mem->ia_dt)
#define Y0         (IDAADJ_mem->ia_Y0)
#define Y1         (IDAADJ_mem->ia_Y1)
#define ytmp       (IDAADJ_mem->ia_ytmp)
#define yptmp      (IDAADJ_mem->ia_yptmp)
#define res_B      (IDAADJ_mem->ia_resB)
#define rdata_B    (IDAADJ_mem->ia_rdataB)
#define djac_B     (IDAADJ_mem->ia_djacB)
#define bjac_B     (IDAADJ_mem->ia_bjacB)
#define pset_B     (IDAADJ_mem->ia_psetB)
#define psolve_B   (IDAADJ_mem->ia_psolveB)
#define jtimes_B   (IDAADJ_mem->ia_jtimesB)
#define jdata_B    (IDAADJ_mem->ia_jdataB)
#define pdata_B    (IDAADJ_mem->ia_pdataB)
#define rhsQ_B     (IDAADJ_mem->ia_rhsQB)
#define rdataQ_B   (IDAADJ_mem->ia_rdataQB)
#define t_for_quad (IDAADJ_mem->ia_t_for_quad)

/* Forward IDAS memory block */

/*#define         (IDA_mem->ida_)*/
#define nvspec     (IDA_mem->ida_nvspec)
#define res        (IDA_mem->ida_res)
#define itol       (IDA_mem->ida_itol)
#define reltol     (IDA_mem->ida_reltol)
#define abstol     (IDA_mem->ida_abstol)

#define forceSetup (IDA_mem->ida_forceSetup)
#define h0u        (IDA_mem->ida_h0u)

#define phi        (IDA_mem->ida_phi)
#define psi        (IDA_mem->ida_psi)
#define alpha      (IDA_mem->ida_alpha)
#define beta       (IDA_mem->ida_beta)
#define sigma      (IDA_mem->ida_sigma)
#define gamma      (IDA_mem->ida_gamma)
#define tn         (IDA_mem->ida_tn)
#define kk         (IDA_mem->ida_kk)
#define nst        (IDA_mem->ida_nst)
#define kk         (IDA_mem->ida_kk)
#define kused      (IDA_mem->ida_kused)
#define knew       (IDA_mem->ida_knew)
#define phase      (IDA_mem->ida_phase)
#define ns         (IDA_mem->ida_ns)
#define hh         (IDA_mem->ida_hh)
#define hused      (IDA_mem->ida_hused)
#define rr         (IDA_mem->ida_rr)
#define cj         (IDA_mem->ida_cj)
#define cjlast     (IDA_mem->ida_cjlast)
#define cjold      (IDA_mem->ida_cjold)
#define cjratio    (IDA_mem->ida_cjratio)

/* Checkpoint memory block */

#define t0_        (ck_mem->ck_t0)
#define t1_        (ck_mem->ck_t1)
#define phi_       (ck_mem->ck_phi)
#define psi_       (ck_mem->ck_psi)
#define alpha_     (ck_mem->ck_alpha)
#define beta_      (ck_mem->ck_beta)
#define sigma_     (ck_mem->ck_sigma)
#define gamma_     (ck_mem->ck_gamma)
#define nst_       (ck_mem->ck_nst)
#define kk_        (ck_mem->ck_kk)
#define kused_     (ck_mem->ck_kused)
#define knew_      (ck_mem->ck_knew)
#define phase_     (ck_mem->ck_phase)
#define ns_        (ck_mem->ck_ns)
#define hh_        (ck_mem->ck_hh)
#define hused_     (ck_mem->ck_hused)
#define rr_        (ck_mem->ck_rr)
#define cj_        (ck_mem->ck_cj)
#define cjlast_    (ck_mem->ck_cjlast)
#define cjold_     (ck_mem->ck_cjold)
#define cjratio_   (ck_mem->ck_cjratio)
#define next_      (ck_mem->ck_next)

/*=================================================================*/
/*END               Readibility Constants                          */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             Exported Functions                             */
/*=================================================================*/

/*------------------    IDAAdjMalloc      --------------------------*/
/*
  This routine allocates space for the global IDAA memory
  structure.
*/
/*-----------------------------------------------------------------*/

void *IDAAdjMalloc(void *ida_mem, long int steps)
{
  IDAadjMem IDAADJ_mem;
  IDAMem IDA_mem;

  /* Check arguments */
  if (ida_mem == NULL) {
    fprintf(stdout, MSG_IDAAM_NO_MEM);
    return (NULL);
  }
  if (steps <= 0) {
    fprintf(stdout, MSG_IDAAM_BAD_STEPS);
    return (NULL);
  }

  /* Allocate memory block */
  IDAADJ_mem = (IDAadjMem) malloc(sizeof(struct IDAadjMemRec));
  if (IDAADJ_mem == NULL) {
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  /* Attach IDAS memory for forward runs */
  IDA_mem = (IDAMem)ida_mem;
  IDAADJ_mem->IDA_mem = IDA_mem;

  /* Initialize Check Points linked list */
  IDAADJ_mem->ck_mem = IDAAckpntInit(IDA_mem);
  if (IDAADJ_mem->ck_mem == NULL) {
    free(IDAADJ_mem);
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  /* Allocate Data Points memory */
  IDAADJ_mem->dt_mem = IDAAdataMalloc(IDA_mem, steps);
  if (IDAADJ_mem->dt_mem == NULL) {
    IDAAckpntDelete(&(IDAADJ_mem->ck_mem));
    free(IDAADJ_mem);
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  /* Workspace memory */
  Y0 = N_VNew(nvspec);
  if (Y0 == NULL) {
    IDAAdataFree(IDAADJ_mem->dt_mem, steps);
    IDAAckpntDelete(&(IDAADJ_mem->ck_mem));
    free(IDAADJ_mem);
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  Y1 = N_VNew(nvspec);
  if (Y1 == NULL) {
    N_VFree(Y0);
    IDAAdataFree(IDAADJ_mem->dt_mem, steps);
    IDAAckpntDelete(&(IDAADJ_mem->ck_mem));
    free(IDAADJ_mem);
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  ytmp = N_VNew(nvspec);
  if (ytmp == NULL) {
    N_VFree(Y1);
    N_VFree(Y0);
    IDAAdataFree(IDAADJ_mem->dt_mem, steps);
    IDAAckpntDelete(&(IDAADJ_mem->ck_mem));
    free(IDAADJ_mem);
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  yptmp = N_VNew(nvspec);
  if (yptmp == NULL) {
    N_VFree(ytmp);
    N_VFree(Y1);
    N_VFree(Y0);
    IDAAdataFree(IDAADJ_mem->dt_mem, steps);
    IDAAckpntDelete(&(IDAADJ_mem->ck_mem));
    free(IDAADJ_mem);
    fprintf(stdout, MSG_IDAAM_MEM_FAIL);
    return(NULL);
  }

  /* Other entries in IDAADJ_mem */
  uround   = IDA_mem->ida_uround;
  nsteps   = steps;
  tinitial = tn; 

  /* Initialize nckpnts to ZERO */
  nckpnts = 0;

  return((void *)IDAADJ_mem);
} 

/*------------------     IDAAdjFree       --------------------------*/
/*
  This routine frees the memory allocated by IDAAdjMalloc.
*/
/*-----------------------------------------------------------------*/

void IDAAdjFree(void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Delete check points one by one */
  while (IDAADJ_mem->ck_mem != NULL) {
    IDAAckpntDelete(&(IDAADJ_mem->ck_mem));
  }

  /* Free vectors at each data point */
  IDAAdataFree(IDAADJ_mem->dt_mem, nsteps);
  free(IDAADJ_mem->dt_mem);

  /* Free vectors in IDAADJ_mem */
  N_VFree(Y0);
  N_VFree(Y1);
  N_VFree(ytmp);
  N_VFree(yptmp);

  /* Free IDAS memory for backward run */
  IDAFree(IDAADJ_mem->IDAB_mem);

  /* Free IDAA memory */
  free(IDAADJ_mem);

}

/*------------------  IDAAdjGetIDABmem  --------------------------*/
/*
  IDAAdjGetIDABmem returns a (void *) pointer to the IDAS     
  memory allocated for the backward problem. This pointer can    
  then be used to call any of the IDAGet* IDAS routines to  
  extract optional output for the backward integration phase.
*/
/*-----------------------------------------------------------------*/

void *IDAAdjGetIDABmem(void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  
  IDAADJ_mem  = (IDAadjMem) idaadj_mem;
  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  return(ida_mem);
}

/*------------------  IDAAdjCheckPointsList ---------------------*/
/*
  This routine lists the linked list of check point structures.
  For debugging....
*/
/*-----------------------------------------------------------------*/

void IDAAdjCheckPointsList(void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;
  CkpntMem ck_mem;
  int i;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ck_mem = IDAADJ_mem->ck_mem;
  i = 0;

  while (ck_mem != NULL) {
    printf("Check point %2d  addr: %p  time = [ %5e %5e ]  next: %p\n", 
           nckpnts-i, (void *)ck_mem, t0_, t1_, (void *)next_ );
    ck_mem = next_;
    i++;
  }

}

/*=================================================================*/
/*BEGIN             Wrappers for IDAA                            */
/*=================================================================*/

/*------------------     IDASolveF          --------------------------*/
/*
  This routine integrates to tout and returns solution into yout.
  In the same time, it stores check point data every 'steps' steps. 
  
  IDASolveF can be called repeatedly by the user. The last tout
  will be used as the starting time for the backward integration.
  
  ncheckPtr points to the number of check points stored so far.
*/
/*-----------------------------------------------------------------*/

int IDASolveF(void *idaadj_mem, realtype tout, realtype *tret,
              N_Vector yret, N_Vector ypret, int itask, int *ncheckPtr)
{
  IDAadjMem IDAADJ_mem;
  IDAMem IDA_mem;
  CkpntMem tmp;
  DtpntMem *dt_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  IDA_mem = IDAADJ_mem->IDA_mem;
  dt_mem = IDAADJ_mem->dt_mem;

  /* On the first step, load dt_mem[0] */
  if ( nst == 0) {
    dt_mem[0]->t = IDAADJ_mem->ck_mem->ck_t0;
    N_VScale(ONE, IDAADJ_mem->ck_mem->ck_phi[0], dt_mem[0]->y);
    N_VScale(ONE, IDAADJ_mem->ck_mem->ck_phi[1], dt_mem[0]->yd);
  }

  /* Integrate to tout while loading check points */

  loop {

    /* Perform one step of the integration */

    flag = IDASolve(IDA_mem, tout, tret, yret, ypret, ONE_STEP);
    if (flag < 0) break;

    /* Test if a new check point is needed */

    if ( nst % nsteps == 0 ) {

      IDAADJ_mem->ck_mem->ck_t1 = *tret;

      /* Create a new check point, load it, and append it to the list */
      tmp = IDAAckpntNew(IDA_mem);
      if (tmp == NULL) {
        flag = IDASOLVEF_MEM_FAIL;
        break;
      }
      tmp->ck_next = IDAADJ_mem->ck_mem;
      IDAADJ_mem->ck_mem = tmp;
      nckpnts++;
      forceSetup = TRUE;
      
      /* Reset i=0 and load dt_mem[0] */
      dt_mem[0]->t = IDAADJ_mem->ck_mem->ck_t0;
      N_VScale(ONE, yret,  dt_mem[0]->y);
      N_VScale(ONE, ypret, dt_mem[0]->yd);

    } else {
      
      /* Load next point in dt_mem */
      dt_mem[nst%nsteps]->t = *tret;
      N_VScale(ONE, yret,  dt_mem[nst%nsteps]->y);
      N_VScale(ONE, ypret, dt_mem[nst%nsteps]->yd);

    }

    /* Set t1 field of the current ckeck point structure
       for the case in which there will be no future
       check points */
    IDAADJ_mem->ck_mem->ck_t1 = *tret;

    /* tfinal is now set to *t */
    tfinal = *tret;

    /* In ONE_STEP mode break from loop */
    if (itask == ONE_STEP) break;

    /* In NORMAL mode and if we passed tout,
       evaluate yout at tout, set t=tout,
       then break from the loop */
    if ( (itask == NORMAL) && (*tret >= tout) ) {
      *tret = tout;
      IDAGetSolution(IDA_mem, tout, yret, ypret);
      break;
    }

  }

  if (flag == IDASOLVEF_MEM_FAIL) 
    fprintf(stdout, MSG_IDASOLVEF_MEM_FAIL);

  /* Get ncheck from IDAADJ_mem */ 
  *ncheckPtr = nckpnts;

  /* Data is available for the last interval */
  newData = TRUE;
  ckpntData = IDAADJ_mem->ck_mem;
  np = nst % nsteps + 1;

  return(flag);

}

/*-- IDACreateB, IDASet*B, IDAMallocB, and IDAReInitB -----*/
/*-----------------------------------------------------------------*/

int IDACreateB(void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;

  if (idaadj_mem == NULL) {
    fprintf(stdout, MSG_IDABM_NO_MEM);
    return(IDABM_NO_MEM);
  }

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = IDACreate();

  if (ida_mem == NULL) {
    fprintf(stdout, MSG_IDABM_MEM_FAIL);
    return(IDABM_MEM_FAIL);
  }

  IDAADJ_mem->IDAB_mem = (IDAMem) ida_mem;

  return(SUCCESS);

}

/*-----------------------------------------------------------------*/

int IDASetRdataB(void *idaadj_mem, void *rdataB)
{
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  rdata_B = rdataB;

  return(SUCCESS);
}

int IDASetErrFileB(void *idaadj_mem, FILE *errfpB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetErrFile(ida_mem, errfpB);

  return(flag);
}

int IDASetMaxOrdB(void *idaadj_mem, int maxordB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetMaxOrd(ida_mem, maxordB);

  return(flag);
}


int IDASetMaxNumStepsB(void *idaadj_mem, long int mxstepsB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetMaxNumSteps(ida_mem, mxstepsB);

  return(flag);
}

int IDASetInitStepB(void *idaadj_mem, realtype hinB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetInitStep(ida_mem, hinB);

  return(flag);
}

int IDASetMaxStepB(void *idaadj_mem, realtype hmaxB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetMaxStep(ida_mem, hmaxB);

  return(flag);
}

int IDASetSuppressAlgB(void *idaadj_mem, booleantype suppressalgB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetSuppressAlg(ida_mem, suppressalgB);

  return(flag);
}

int IDASetIdB(void *idaadj_mem, N_Vector idB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetId(ida_mem, idB);

  return(flag);
}

int IDASetConstraintsB(void *idaadj_mem, N_Vector constraintsB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetConstraints(ida_mem, constraintsB);

  return(flag);
}

/*-----------------------------------------------------------------*/

int IDAMallocB(void *idaadj_mem, ResFnB resB,
               realtype tB0, N_Vector yyB0, N_Vector ypB0, 
               int itolB, realtype *reltolB, void *abstolB,
               NV_Spec nvspecB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  if (idaadj_mem == NULL) {
    fprintf(stdout, MSG_IDABM_NO_MEM);
    return(IDABM_NO_MEM);
  }

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  if ( (tB0 < tinitial) || (tB0 > tfinal) ) {
    fprintf(stdout, MSG_IDABM_BAD_TB0);
    return(IDABM_BAD_TB0);
  }

  res_B = resB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  IDASetRdata(ida_mem, idaadj_mem);

  flag = IDAMalloc(ida_mem, IDAAres, tB0, yyB0, ypB0,
                   itolB, reltolB, abstolB, nvspecB);

  return(flag);

}

/*-----------------------------------------------------------------*/

int IDAReInitB(void *idaadj_mem, ResFnB resB,
               realtype tB0, N_Vector yyB0, N_Vector ypB0,
               int itolB, realtype *reltolB, void *abstolB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  if (idaadj_mem == NULL) {
    fprintf(stdout, MSG_IDABM_NO_MEM);
    return(IDABM_NO_MEM);
  }

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  if ( (tB0 < tinitial) || (tB0 > tfinal) ) {
    fprintf(stdout, MSG_IDABM_BAD_TB0);
    return(IDABM_BAD_TB0);
  }

  res_B  = resB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  IDASetRdata(ida_mem, idaadj_mem);

  flag = IDAReInit(ida_mem, IDAAres, tB0, yyB0, ypB0,
                   itolB, reltolB, abstolB);
  
  return(flag);

}

/*-- IDASetQuad*B, IDAQuadMallocB, and IDAQuadReInitB -------*/
/*-----------------------------------------------------------------*/

int IDASetQuadErrConB(void *idaadj_mem, int errconQB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetQuadErrCon(ida_mem, errconQB);

  return(flag);
}

int IDASetQuadRdataB(void *idaadj_mem, void *rdataQB)
{
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  rdataQ_B = rdataQB;

  return(SUCCESS);
}

int IDASetQuadTolerancesB(void *idaadj_mem, int itolQB, 
                          realtype *reltolQB, void *abstolQB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  ida_mem = (void *)IDAADJ_mem->IDAB_mem;

  flag = IDASetQuadTolerances(ida_mem, itolQB, reltolQB, abstolQB);

  return(flag);
}

/*-----------------------------------------------------------------*/

int IDAQuadMallocB(void *idaadj_mem, QuadRhsFnB rhsQB, NV_Spec nvspecQB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  if (idaadj_mem == NULL) {
    fprintf(stdout, MSG_IDABQM_NO_MEM);
    return(IDABM_NO_MEM);
  }

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  rhsQ_B = rhsQB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  IDASetQuadRdata(ida_mem, idaadj_mem);

  flag = IDAQuadMalloc(ida_mem, IDAArhsQ, nvspecQB); 

  return(flag);

}

/*-----------------------------------------------------------------*/

int IDAQuadReInitB(void *idaadj_mem, QuadRhsFnB rhsQB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  if (idaadj_mem == NULL) {
    fprintf(stdout, MSG_IDABQM_NO_MEM);
    return(IDABM_NO_MEM);
  }

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  rhsQ_B = rhsQB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDAQuadReInit(ida_mem, IDAArhsQ);

  return(flag);

}

/*---------  IDADenseB and IDAdenseSet*B    -------------------------*/
/*-----------------------------------------------------------------*/

int IDADenseB(void *idaadj_mem, long int NeqB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;
  
  flag = IDADense(ida_mem, NeqB);

  return(flag);
}

int IDADenseSetJacFnB(void *idaadj_mem, IDADenseJacFnB djacB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  djac_B     = djacB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDADenseSetJacData(ida_mem, idaadj_mem);
  flag = IDADenseSetJacFn(ida_mem, IDAAdenseJac);

  return(flag);
}

int IDADenseSetJacDataB(void *idaadj_mem, void *jdataB)
{
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  jdata_B = jdataB;

  return(SUCCESS);
}

/*-----------  IDABandB and IDABandSet*B      -----------------------*/
/*-----------------------------------------------------------------*/

int IDABandB(void *idaadj_mem, long int NeqB, 
            long int mupperB, long int mlowerB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;
  
  flag = IDABand(ida_mem, NeqB, mupperB, mlowerB);

  return(flag);
}

int IDABandSetJacFnB(void *idaadj_mem, IDABandJacFnB bjacB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  bjac_B     = bjacB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDABandSetJacData(ida_mem, idaadj_mem);
  flag = IDABandSetJacFn(ida_mem, IDAAbandJac);

  return(flag);
}

int IDABandSetJacDataB(void *idaadj_mem, void *jdataB)
{ 
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  jdata_B = jdataB;

  return(SUCCESS);
}

/*------------   IDASpgmrB and IDASpgmrSet*B    ---------------------*/
/*-----------------------------------------------------------------*/

int IDASpgmrB(void *idaadj_mem, int maxlB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;
  
  flag = IDASpgmr(ida_mem, maxlB);

  return(flag);
}

int IDASpgmrSetGSTypeB(void *idaadj_mem, int gstypeB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetGSType(ida_mem, gstypeB);

  return(flag);
}

int IDASpgmrSetMaxRestartsB(void *idaadj_mem, int maxrsB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetMaxRestarts(ida_mem, maxrsB);

  return(flag);
}

int IDASpgmrSetEpsLinB(void *idaadj_mem, realtype eplifacB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetEpsLin(ida_mem, eplifacB);

  return(flag);
}

int IDASpgmrSetIncrementFactorB(void *idaadj_mem, realtype dqincfacB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetIncrementFactor(ida_mem, dqincfacB);

  return(flag);
}

int IDASpgmrSetPrecSetupFnB(void *idaadj_mem, IDASpgmrPrecSetupFnB psetB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  pset_B = psetB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetPrecData(ida_mem, idaadj_mem);
  flag = IDASpgmrSetPrecSetupFn(ida_mem,IDAAspgmrPrecSetup);

  return(flag);
}

int IDASpgmrSetPrecSolveFnB(void *idaadj_mem, IDASpgmrPrecSolveFnB psolveB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  psolve_B = psolveB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetPrecData(ida_mem, idaadj_mem);
  flag = IDASpgmrSetPrecSolveFn(ida_mem,IDAAspgmrPrecSolve);

  return(flag);
}

int IDASpgmrSetJacTimesVecFnB(void *idaadj_mem, IDASpgmrJacTimesVecFnB jtimesB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  jtimes_B = jtimesB;

  ida_mem = (void *) IDAADJ_mem->IDAB_mem;

  flag = IDASpgmrSetJacData(ida_mem, idaadj_mem);
  flag = IDASpgmrSetJacTimesVecFn(ida_mem,IDAAspgmrJacTimesVec);

  return(flag);
}

int IDASpgmrSetPrecDataB(void *idaadj_mem, void *PdataB)
{
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  pdata_B = PdataB;

  return(SUCCESS);
}

int IDASpgmrSetJacDataB(void *idaadj_mem, void *jdataB)
{
  IDAadjMem IDAADJ_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  jdata_B = jdataB;

  return(SUCCESS);
}

/*------------------     IDASolveB          --------------------------*/
/*
  This routine performs the backward integration from tB0 
  to tinitial through a sequence of forward-backward runs in
  between consecutive check points. It returns the values of
  the adjoint variables and any existing quadrature variables
  at tinitial.
*/
/*-----------------------------------------------------------------*/

int IDASolveB(void *idaadj_mem, N_Vector yyB, N_Vector ypB)
{
  IDAadjMem IDAADJ_mem;
  CkpntMem ck_mem;
  IDAMem IDAB_mem;
  int flag;
  realtype tB0, t;
  
  IDAADJ_mem  = (IDAadjMem) idaadj_mem;
  ck_mem = IDAADJ_mem->ck_mem;

  IDAB_mem = IDAADJ_mem->IDAB_mem;

  /* First decide which check points tB0 falls in between */
  tB0 = IDAB_mem->ida_tn;
  while ( tB0 <= t0_ ) ck_mem = next_;
  
  do {

    /* If data in dt_mem is not available for the 
       current check point, compute it */
    if (ck_mem != ckpntData) {
      flag = IDAAdataStore(IDAADJ_mem, ck_mem);
      if (flag < 0) {
        fprintf(stdout, MSG_IDASOLVEB_FWD);
        return(flag);
      }
    }

    /* Propagate backward integration to next check point */
    IDASetStopTime((void *)IDAB_mem, t0_);
    flag = IDASolve(IDAB_mem, t0_, &t, yyB, ypB, NORMAL_TSTOP);
    if (flag < 0) {
      fprintf(stdout, MSG_IDASOLVEB_BCK);
      return(flag);
    }

    /* Move check point in linked list to next one */
    ck_mem = next_;

  } while (ck_mem != NULL);

  t_for_quad = t;

  return(flag);

}

/*------------------  IDAGetQuadB  ------------------------------*/
/*-----------------------------------------------------------------*/

int IDAGetQuadB(void *idaadj_mem, N_Vector qB)
{
  IDAadjMem IDAADJ_mem;
  void *ida_mem;
  int flag;
  
  IDAADJ_mem  = (IDAadjMem) idaadj_mem;
  ida_mem = (void *) IDAADJ_mem->IDAB_mem;
  
  flag = IDAGetQuad(ida_mem, t_for_quad, qB);

  return(flag);
}

/*=================================================================*/
/*END               Wrappers for IDAA                            */
/*=================================================================*/

/*------------------  IDAGetMemB  --------------------------*/
/*
  IDAGetMemB returns a (void *) pointer to the IDAS
  memory allocated for the backward problem. This pointer can    
  then be used to call any of the IDAGet* IDAS routines to  
  extract optional output for the backward integration phase.
*/
/*-----------------------------------------------------------------*/

void *IDAGetMemB(void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;
  void *idab_mem;
  
  IDAADJ_mem  = (IDAadjMem) idaadj_mem;
  idab_mem = (void *) IDAADJ_mem->IDAB_mem;

  return(idab_mem);
}


/*=================================================================*/
/*BEGIN           Debugging routines                               */
/*=================================================================*/

int IDAAloadData(void *idaadj_mem, int which_ckpnt, long int *points)
{
  IDAadjMem IDAADJ_mem;
  CkpntMem ck_mem;
  int i, flag = SUCCESS;
  
  IDAADJ_mem  = (IDAadjMem) idaadj_mem;
  ck_mem = IDAADJ_mem->ck_mem;

  for (i=0; i<which_ckpnt; i++) ck_mem = next_;

  printf("Starting at check point %p   ",(void *)ck_mem);

  /* If data in dt_mem is not available for the 
     current check point, compute it */
  if (ck_mem != ckpntData) {
    printf("...regenerate data\n");
    flag = IDAAdataStore(IDAADJ_mem, ck_mem);
    if (flag < 0) {
      fprintf(stdout, MSG_IDASOLVEB_FWD);
      return(flag);
    }
  } else {
    printf("...data already available\n");
  }

  *points = np;

  return(flag);

}

/*--------------------   IDAAgetData  ------------------------*/
/*
  This routine returns the solution stored in the data structure
  at the 'which' data point.
  For debugging....
*/
/*-----------------------------------------------------------------*/

void IDAAgetData(void *idaadj_mem, long int which_pnt, 
                 realtype *t, N_Vector yout, N_Vector ydout)
{
  IDAadjMem IDAADJ_mem;
  DtpntMem *dt_mem;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  dt_mem = IDAADJ_mem->dt_mem;

  *t = dt_mem[which_pnt]->t;

  if (yout != NULL)
    N_VScale(ONE, dt_mem[which_pnt]->y, yout);

  if (ydout != NULL)
    N_VScale(ONE, dt_mem[which_pnt]->yd, ydout);

}

/*=================================================================*/
/*BEGIN           Debugging routines                               */
/*=================================================================*/

/*=================================================================*/
/*END               Exported Functions                             */
/*=================================================================*/

/*=================================================================*/
/*BEGIN             Private Functions Implementation               */
/*=================================================================*/

/*------------------     IDAAckpntInit    --------------------------*/
/*
  This routine initializes the check point linked list with 
  information from the initial time.
*/
/*-----------------------------------------------------------------*/

static CkpntMem IDAAckpntInit(IDAMem IDA_mem)
{
  CkpntMem ck_mem;

  /* Allocate space for ckdata */
  ck_mem = (CkpntMem) malloc(sizeof(struct CkpntMemRec));
  phi_[0] = N_VNew(nvspec);
  phi_[1] = N_VNew(nvspec);

  /* Load ckdata from IDA_mem 
     Note: phi[1] has not been scaled by the step size yet!!! */
  N_VScale(ONE, phi[0], phi_[0]);
  N_VScale(ONE, phi[1], phi_[1]);
  t0_    = tn;
  
  /* Next in list */
  next_  = NULL;

  return(ck_mem);
}

/*------------------    IDAAckpntNew      --------------------------*/
/*
  This routine allocates space for a new check point and sets 
  its data from current values in IDA_mem.
*/
/*-----------------------------------------------------------------*/

static CkpntMem IDAAckpntNew(IDAMem IDA_mem)
{
  CkpntMem ck_mem;
  int j, jj;

  /* Allocate space for ckdata */
  ck_mem = (CkpntMem) malloc(sizeof(struct CkpntMemRec));
  if (ck_mem == NULL) return(NULL);

  for (j=0; j<=kk; j++) {
    phi_[j] = N_VNew(nvspec);
    if(phi_[j] == NULL) {
      for(jj=0; jj<j; jj++) N_VFree(phi_[jj]);
      return(NULL);
    }
  }

  /* Load check point data from IDA_mem */
  for (j=0; j<=kk; j++)
    N_VScale(ONE, phi[j], phi_[j]);
  for (j=0; j<MXORDP1; j++) {
    psi_[j]   = psi[j];
    alpha_[j] = alpha[j];
    beta_[j]  = beta[j];
    sigma_[j] = sigma[j];
    gamma_[j] = gamma[j];
  }
  nst_       = nst;
  kk_        = kk;
  kused_     = kused;
  knew_      = knew;
  phase_     = phase;
  ns_        = ns;
  hh_        = hh;
  hused_     = hused;
  rr_        = rr;
  cj_        = cj;
  cjlast_    = cjlast;
  cjold_     = cjold;
  cjratio_   = cjratio;
  t0_        = tn;

  return(ck_mem);
}

/*------------------    IDAAckpntDelete   --------------------------*/
/*
  This routine deletes the first check point in list.
*/
/*-----------------------------------------------------------------*/

static void IDAAckpntDelete(CkpntMem *ck_memPtr)
{
  CkpntMem tmp;
  int j;

  if (*ck_memPtr != NULL) {
    /* store head of list */
    tmp = *ck_memPtr;
    /* move head of list */
    *ck_memPtr = (*ck_memPtr)->ck_next;
    /* free tmp */
    for (j=0;j<=tmp->ck_kk;j++) N_VFree(tmp->ck_phi[j]);
    free(tmp);
  }
}

/*------------------    IDAAdataMalloc    --------------------------*/
/*
  This routine allocates memory for storing information at all
  intermediate points between two consecutive check points. 
  This data is then used to interpolate the forward solution 
  at any other time.
*/
/*-----------------------------------------------------------------*/

static DtpntMem *IDAAdataMalloc(IDAMem IDA_mem, long int steps)
{
  DtpntMem *dt_mem;
  long int i;

  dt_mem = (DtpntMem *)malloc((steps+1)*sizeof(struct DtpntMemRec *));

  for (i=0; i<=steps; i++) {
    dt_mem[i] = (DtpntMem)malloc(sizeof(struct DtpntMemRec));
    dt_mem[i]->y  = N_VNew(nvspec);
    dt_mem[i]->yd = N_VNew(nvspec);
  } 

  return(dt_mem);

}

/*------------------    IDAAdataFree      --------------------------*/
/*
  This routine frees the memeory allocated for data storage.
*/
/*-----------------------------------------------------------------*/

static void IDAAdataFree(DtpntMem *dt_mem, long int steps)
{
  long int i;

  for (i=0; i<=steps; i++) {
    N_VFree(dt_mem[i]->y);
    N_VFree(dt_mem[i]->yd);
    free(dt_mem[i]);
  }

}

/*------------------    IDAAdataStore     --------------------------*/
/*
  This routine integrates the forward model starting at the check
  point ck_mem and stores y and yprime at all intermediate 
  steps. It returns the error flag from IDA.
*/
/*-----------------------------------------------------------------*/

int IDAAdataStore(IDAadjMem IDAADJ_mem, CkpntMem ck_mem)
{
  IDAMem IDA_mem;
  DtpntMem *dt_mem;
  realtype t;
  long int i;
  int j, flag;

  IDA_mem = IDAADJ_mem->IDA_mem;
  dt_mem = IDAADJ_mem->dt_mem;

  /*
   * Initialize IDA_mem with data from ck_mem and
   * Set first structure in dt_mem
   */

  if (next_ == NULL) {

    /* In this case, we just call the reinitialization routine, but
       make sure we use the same initial stepsize as on the first run. */

    IDASetInitStep(IDA_mem, h0u);

    flag = IDAReInit(IDA_mem, res, t0_, phi_[0], phi_[1], itol, reltol, abstol);
    if (flag != SUCCESS) return(flag);

    dt_mem[0]->t = t0_;
    N_VScale(ONE, phi_[0], dt_mem[0]->y);
    N_VScale(ONE, phi_[1], dt_mem[0]->yd);

  } else {

    /* Copy parameters from check point data structure */
    nst       = nst_;
    kk        = kk_;
    kused     = kused_;
    knew      = knew_;
    phase     = phase_;
    ns        = ns_;
    hh        = hh_;
    hused     = hused_;
    rr        = rr_;
    cj        = cj_;
    cjlast    = cjlast_;
    cjold     = cjold_;
    cjratio   = cjratio_;
    tn        = t0_;

    /* Copy the arrays from check point data structure */
    for (j=0; j<=kk; j++)
      N_VScale(ONE, phi_[j], phi[j]);
    for (j=0; j<MXORDP1; j++) {
      psi[j]   = psi_[j];
      alpha[j] = alpha_[j];
      beta[j]  = beta_[j];
      sigma[j] = sigma_[j];
      gamma[j] = gamma_[j];
    }
    
    /* Force a call to setup at the beginning */
    forceSetup = TRUE;

    /* Set structure dt_mem[0] */
    dt_mem[0]->t = t0_;
    IDAGetSolution(IDA_mem, dt_mem[0]->t, dt_mem[0]->y, dt_mem[0]->yd);

  }

  /* 
   * Run IDA in ONE_STEP mode to set following structures in dt_mem[i] 
   */

  i = 1;
  do {
    flag = IDASolve(IDA_mem, t1_, &t, dt_mem[i]->y, dt_mem[i]->yd, ONE_STEP);
    if (flag < 0) return(flag);
    dt_mem[i]->t = t;
    i++;
  } while (t<t1_);

  /* 
   * New data is now available 
   */

  ckpntData = ck_mem;
  newData = TRUE;
  np  = i;

  return(flag);

}

/*------------------     IDAAgetY       --------------------------*/
/*
  This routine uses cubic piece-wise Hermite interpolation for 
  the forward solution vector. 
  It is called by the wrapper routines before calling user provided 
  routines (resB, rhsQB, djacB, bjacB, jtimesB, psolB)
*/
/*-----------------------------------------------------------------*/

static int IDAAgetY(void *idaadj_mem, realtype t, N_Vector yy, N_Vector yp)
{
  IDAadjMem IDAADJ_mem;
  DtpntMem *dt_mem;
  static long int i;
  long int inew;
  booleantype to_left, to_right;
  realtype troundoff;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;
  dt_mem = IDAADJ_mem->dt_mem;

  if ( newData ) {
    i = np-1;
    IDAAhermitePrepare(IDAADJ_mem, dt_mem, i); 
    newData = FALSE;
  }

  /* Search for inew starting from last i */ 
  to_left  = ( t < dt_mem[i-1]->t );
  to_right = ( t > dt_mem[i]->t );
  
  /* Test if t is beyond left limit */
  if ( (to_left) && (i==1) ) {
    /*troundoff = FUZZ_FACTOR*uround*(ABS(dt_mem[0]->t)+ABS(dt_mem[1]->t));*/
    troundoff = FUZZ_FACTOR*uround;
    if ( ABS( t - dt_mem[0]->t ) <= troundoff ) {
      N_VScale(ONE, dt_mem[0]->y, yy);
      N_VScale(ONE, dt_mem[0]->yd, yp);
      return(GETY_OK);
    }
    else {
      printf("\n TROUBLE IN GETY\n ");
      printf("%g = ABS(t-dt_mem[0]->t) > troundoff = %g  uround = %g\n",
             ABS(t-dt_mem[0]->t), troundoff, uround);
      return(GETY_BADT);
    }
  }

  inew = i;
  if ( to_left ) {
    /* Search to the left */
    inew--;
    loop {
      if ( inew == 1 ) break;
      if ( t <= dt_mem[inew-1]->t ) inew--;
      else                          break;
    }
  } else if ( to_right ) {
    /* Search to the right */
    inew++;
    loop {
      if ( t > dt_mem[inew]->t ) inew++;
      else                       break;
    }
  }
  
  if ( inew != i )
    IDAAhermitePrepare(IDAADJ_mem, dt_mem, inew);

  IDAAhermiteInterpolate(IDAADJ_mem, dt_mem, inew, t, yy, yp);

  i = inew;

  return(GETY_OK);

}

/*------------------   IDAAhermitePrepare --------------------------*/
/*
  This routine computes quantities required by the Hermite
  interpolation that are independent of the interpolation point.
*/
/*-----------------------------------------------------------------*/

static void IDAAhermitePrepare(IDAadjMem IDAADJ_mem, DtpntMem *dt_mem, long int i)
{
  realtype t0, t1; 
  N_Vector y0, y1, yd0, yd1;

  t0  = dt_mem[i-1]->t;
  y0  = dt_mem[i-1]->y;
  yd0 = dt_mem[i-1]->yd;

  t1  = dt_mem[i]->t;
  y1  = dt_mem[i]->y;
  yd1 = dt_mem[i]->yd;

  dt = t1 - t0;

  N_VLinearSum(ONE, y1, -ONE, y0, Y0);
  N_VLinearSum(ONE, yd1,  ONE, yd0, Y1);
  N_VLinearSum(dt, Y1, -TWO, Y0, Y1);
  N_VLinearSum(ONE, Y0, -dt, yd0, Y0);
}

/*------------------   IDAAhermiteInterpolate ----------------------*/
/*
  This routine performs the Hermite interpolation.
  y  = y0 + a * yd0 + b * Y0  + c * Y1
  yd =          yd0 + bd * Y0 + cd * Y1
*/
/*-----------------------------------------------------------------*/

static void IDAAhermiteInterpolate(IDAadjMem IDAADJ_mem, DtpntMem *dt_mem,
                                   long int i, realtype t, N_Vector y, N_Vector yd)
{
  realtype t0, t1;
  N_Vector y0, yd0;
  realtype dt2, a, b, c, bd, cd;

  t0  = dt_mem[i-1]->t;
  t1  = dt_mem[i]->t;
  y0  = dt_mem[i-1]->y;
  yd0 = dt_mem[i-1]->yd;

  dt2 = dt*dt;

  a  = t - t0;
  b  = a * a / dt2;
  c  = b * (t-t1) / dt;

  bd = 2 * a / dt2;
  cd = ( (t-t1) * bd + b ) / dt;

  N_VLinearSum(ONE,  y0,  a, yd0,  y);
  N_VLinearSum(ONE,   y,  b,  Y0,  y);
  N_VLinearSum(ONE,   y,  c,  Y1,  y);

  N_VLinearSum(ONE, yd0, bd,  Y0, yd);
  N_VLinearSum(ONE,  yd, cd,  Y1, yd);
}

/*=================================================================*/
/*BEGIN        Wrappers for adjoint system                         */
/*=================================================================*/

/*------------------       IDAAres        --------------------------*/
/*
  This routine interfaces to the RhsFnB routine provided by
  the user.
*/
/*-----------------------------------------------------------------*/

static int IDAAres(realtype tres, 
                    N_Vector yyB, N_Vector ypB, N_Vector resvalB, 
                    void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, tres, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  }

  /* Call user's adjoint RES routine */
  flag = res_B(tres, ytmp, yptmp, yyB, ypB, resvalB, rdata_B);

  return(flag);

}

/*------------------       IDAArhsQ       --------------------------*/
/*
  This routine interfaces to the QuadRhsFnB routine provided by
  the user.
*/
/*-----------------------------------------------------------------*/

static void IDAArhsQ(realtype tres, N_Vector yyB, N_Vector ypB,
                     N_Vector ypQB, void *idaadj_mem)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, tres, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  }

  /* Call user's adjoint quadrature RHS routine */
  rhsQ_B(tres, ytmp, yptmp, yyB, ypB, ypQB, rdataQ_B);

}

/*------------------    IDAAdenseJac      --------------------------*/
/*
  This routine interfaces to the IDADenseJacFnB routine provided 
  by the user.
*/
/*-----------------------------------------------------------------*/

static int IDAAdenseJac(long int NeqB, realtype t, N_Vector yyB, 
                        N_Vector ypB, realtype cjB, void *idaadj_mem, 
                        N_Vector resvecB, DenseMat JacB, 
                        N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, t, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  }

  /* Call user's adjoint dense djacB routine */
  flag = djac_B(NeqB, t, ytmp, yptmp, yyB, ypB, cjB, 
                jdata_B, resvecB, JacB, 
                tmp1B, tmp2B, tmp3B);

  return(flag);
}

/*------------------    IDAAbandJac       --------------------------*/
/*
  This routine interfaces to the IDABandJacFnB routine provided 
  by the user.
*/
/*-----------------------------------------------------------------*/

static int IDAAbandJac(long int NeqB, long int mupperB, 
                       long int mlowerB, realtype t, 
                       N_Vector yyB, N_Vector ypB, realtype cjB, 
                       void *idaadj_mem, N_Vector resvecB, BandMat JacB, 
                       N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, t, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  }

  /* Call user's adjoint band bjacB routine */
  flag = bjac_B(NeqB, mupperB, mlowerB, t, ytmp, yptmp, yyB, ypB, cjB, 
                jdata_B, resvecB, JacB, tmp1B, tmp2B, tmp3B);

  return(flag);
}

/*------------------   IDAAspgmrPrecSetup   ------------------------*/
/*
  This routine interfaces to the IDASpgmrPrecSetupFnB routine 
  provided by the user.
*/
/*-----------------------------------------------------------------*/

static int IDAAspgmrPrecSetup(realtype t, 
                              N_Vector yyB, N_Vector ypB, N_Vector rrB, 
                              realtype cjB, void *idaadj_mem,
                              N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, t, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  } 

  /* Call user's adjoint precondB routine */
  flag = pset_B(t, ytmp, yptmp, yyB, ypB, rrB, cjB, pdata_B,
                tmp1B, tmp2B, tmp3B);

  return(flag);
}

/*----------------   IDAAspgmrPrecSolve    -------------------------*/
/*
  This routine interfaces to the IDASpgmrPrecSolveFnB routine 
  provided by the user.
*/
/*-----------------------------------------------------------------*/

static int IDAAspgmrPrecSolve(realtype t, 
                              N_Vector yyB, N_Vector ypB, N_Vector rrB, 
                              N_Vector rvecB, N_Vector zvecB,
                              realtype cjB, realtype deltaB,
                              void *idaadj_mem, N_Vector tmpB)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, t, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  } 

  /* Call user's adjoint psolveB routine */
  flag = psolve_B(t, ytmp, yptmp, yyB, ypB, rrB, rvecB, zvecB, cjB, 
                  deltaB, pdata_B, tmpB);

  return(flag);
}

/*------------------   IDAAspgmrJacTimesVec    ---------------------*/
/*
  This routine interfaces to the IDASpgmrJacTimesVecFnB routine 
  provided by the user.
*/
/*-----------------------------------------------------------------*/

static int IDAAspgmrJacTimesVec(N_Vector vB, N_Vector JvB, realtype t,
                                N_Vector yyB, N_Vector ypB, N_Vector rrB,
                                realtype cjB, void *idaadj_mem, 
                                N_Vector tmp1B, N_Vector tmp2B)
{
  IDAadjMem IDAADJ_mem;
  int flag;

  IDAADJ_mem = (IDAadjMem) idaadj_mem;

  /* Forward solution from Hermite interpolation */
  flag = IDAAgetY(IDAADJ_mem, t, ytmp, yptmp);
  if (flag != GETY_OK) {
    printf("\n\nBad t in interpolation\n\n");
    exit(1);
  } 

  /* Call user's adjoint jtimesB routine */
  flag = jtimes_B(vB, JvB, t, ytmp, yptmp, yyB, ypB, rrB, cjB, jdata_B, 
                  tmp1B, tmp2B);

  return(flag);
}

/*=================================================================*/
/*END               Wrappers for adjoint system                    */
/*=================================================================*/

/*=================================================================*/
/*END               Private Functions Implementation               */
/*=================================================================*/
