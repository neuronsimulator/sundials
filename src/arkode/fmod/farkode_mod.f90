! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.

! ---------------------------------------------------------------
! Programmer(s): Auto-generated by swig.
! ---------------------------------------------------------------
! SUNDIALS Copyright Start
! Copyright (c) 2002-2019, Lawrence Livermore National Security
! and Southern Methodist University.
! All rights reserved.
!
! See the top-level LICENSE and NOTICE files for details.
!
! SPDX-License-Identifier: BSD-3-Clause
! SUNDIALS Copyright End
! ---------------------------------------------------------------

module farkode_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_nvector_mod
 use fsundials_types_mod
 use fsundials_matrix_mod
 use fsundials_nvector_mod
 use fsundials_types_mod
 use fsundials_linearsolver_mod
 use fsundials_matrix_mod
 use fsundials_nvector_mod
 use fsundials_types_mod
 use fsundials_nonlinearsolver_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 integer(C_INT), parameter, public :: ARK_NORMAL = 1_C_INT
 integer(C_INT), parameter, public :: ARK_ONE_STEP = 2_C_INT
 integer(C_INT), parameter, public :: ARK_SUCCESS = 0_C_INT
 integer(C_INT), parameter, public :: ARK_TSTOP_RETURN = 1_C_INT
 integer(C_INT), parameter, public :: ARK_ROOT_RETURN = 2_C_INT
 integer(C_INT), parameter, public :: ARK_WARNING = 99_C_INT
 integer(C_INT), parameter, public :: ARK_TOO_MUCH_WORK = -1_C_INT
 integer(C_INT), parameter, public :: ARK_TOO_MUCH_ACC = -2_C_INT
 integer(C_INT), parameter, public :: ARK_ERR_FAILURE = -3_C_INT
 integer(C_INT), parameter, public :: ARK_CONV_FAILURE = -4_C_INT
 integer(C_INT), parameter, public :: ARK_LINIT_FAIL = -5_C_INT
 integer(C_INT), parameter, public :: ARK_LSETUP_FAIL = -6_C_INT
 integer(C_INT), parameter, public :: ARK_LSOLVE_FAIL = -7_C_INT
 integer(C_INT), parameter, public :: ARK_RHSFUNC_FAIL = -8_C_INT
 integer(C_INT), parameter, public :: ARK_FIRST_RHSFUNC_ERR = -9_C_INT
 integer(C_INT), parameter, public :: ARK_REPTD_RHSFUNC_ERR = -10_C_INT
 integer(C_INT), parameter, public :: ARK_UNREC_RHSFUNC_ERR = -11_C_INT
 integer(C_INT), parameter, public :: ARK_RTFUNC_FAIL = -12_C_INT
 integer(C_INT), parameter, public :: ARK_LFREE_FAIL = -13_C_INT
 integer(C_INT), parameter, public :: ARK_MASSINIT_FAIL = -14_C_INT
 integer(C_INT), parameter, public :: ARK_MASSSETUP_FAIL = -15_C_INT
 integer(C_INT), parameter, public :: ARK_MASSSOLVE_FAIL = -16_C_INT
 integer(C_INT), parameter, public :: ARK_MASSFREE_FAIL = -17_C_INT
 integer(C_INT), parameter, public :: ARK_MASSMULT_FAIL = -18_C_INT
 integer(C_INT), parameter, public :: ARK_CONSTR_FAIL = -19_C_INT
 integer(C_INT), parameter, public :: ARK_MEM_FAIL = -20_C_INT
 integer(C_INT), parameter, public :: ARK_MEM_NULL = -21_C_INT
 integer(C_INT), parameter, public :: ARK_ILL_INPUT = -22_C_INT
 integer(C_INT), parameter, public :: ARK_NO_MALLOC = -23_C_INT
 integer(C_INT), parameter, public :: ARK_BAD_K = -24_C_INT
 integer(C_INT), parameter, public :: ARK_BAD_T = -25_C_INT
 integer(C_INT), parameter, public :: ARK_BAD_DKY = -26_C_INT
 integer(C_INT), parameter, public :: ARK_TOO_CLOSE = -27_C_INT
 integer(C_INT), parameter, public :: ARK_POSTPROCESS_FAIL = -28_C_INT
 integer(C_INT), parameter, public :: ARK_VECTOROP_ERR = -29_C_INT
 integer(C_INT), parameter, public :: ARK_NLS_INIT_FAIL = -30_C_INT
 integer(C_INT), parameter, public :: ARK_NLS_SETUP_FAIL = -31_C_INT
 integer(C_INT), parameter, public :: ARK_NLS_SETUP_RECVR = -32_C_INT
 integer(C_INT), parameter, public :: ARK_NLS_OP_ERR = -33_C_INT
 integer(C_INT), parameter, public :: ARK_INNERSTEP_ATTACH_ERR = -34_C_INT
 integer(C_INT), parameter, public :: ARK_INNERSTEP_FAIL = -35_C_INT
 integer(C_INT), parameter, public :: ARK_OUTERTOINNER_FAIL = -36_C_INT
 integer(C_INT), parameter, public :: ARK_INNERTOOUTER_FAIL = -37_C_INT
 integer(C_INT), parameter, public :: ARK_UNRECOGNIZED_ERROR = -99_C_INT
 public :: FARKBandPrecInit
 public :: FARKBandPrecGetWorkSpace
 public :: FARKBandPrecGetNumRhsEvals
 public :: FARKBBDPrecInit
 public :: FARKBBDPrecReInit
 public :: FARKBBDPrecGetWorkSpace
 public :: FARKBBDPrecGetNumGfnEvals

 integer, parameter :: swig_cmem_own_bit = 0
 integer, parameter :: swig_cmem_rvalue_bit = 1
 integer, parameter :: swig_cmem_const_bit = 2
 type, bind(C) :: SwigClassWrapper
  type(C_PTR), public :: cptr = C_NULL_PTR
  integer(C_INT), public :: cmemflags = 0
 end type
 ! struct struct ARKodeButcherTableMem
 type, public :: ARKodeButcherTable
  type(SwigClassWrapper), public :: swigdata
 contains
  procedure :: set_q => swigf_ARKodeButcherTable_q_set
  procedure :: get_q => swigf_ARKodeButcherTable_q_get
  procedure :: set_p => swigf_ARKodeButcherTable_p_set
  procedure :: get_p => swigf_ARKodeButcherTable_p_get
  procedure :: set_stages => swigf_ARKodeButcherTable_stages_set
  procedure :: get_stages => swigf_ARKodeButcherTable_stages_get
  procedure :: set_A => swigf_ARKodeButcherTable_A_set
  procedure :: get_A => swigf_ARKodeButcherTable_A_get
  procedure :: set_c => swigf_ARKodeButcherTable_c_set
  procedure :: get_c => swigf_ARKodeButcherTable_c_get
  procedure :: set_b => swigf_ARKodeButcherTable_b_set
  procedure :: get_b => swigf_ARKodeButcherTable_b_get
  procedure :: set_d => swigf_ARKodeButcherTable_d_set
  procedure :: get_d => swigf_ARKodeButcherTable_d_get
  procedure :: release => swigf_release_ARKodeButcherTable
  procedure, private :: swigf_ARKodeButcherTable_op_assign__
  generic :: assignment(=) => swigf_ARKodeButcherTable_op_assign__
 end type ARKodeButcherTable
 interface ARKodeButcherTable
  module procedure swigf_create_ARKodeButcherTable
 end interface
 public :: FARKodeButcherTable_Alloc
 public :: FARKodeButcherTable_Create
 public :: FARKodeButcherTable_Copy
 public :: FARKodeButcherTable_Space
 public :: FARKodeButcherTable_Free
 public :: FARKodeButcherTable_Write
 public :: FARKodeButcherTable_CheckOrder
 public :: FARKodeButcherTable_CheckARKOrder
 integer(C_INT), parameter, public :: SDIRK_2_1_2 = 100_C_INT
 integer(C_INT), parameter, public :: BILLINGTON_3_3_2 = 101_C_INT
 integer(C_INT), parameter, public :: TRBDF2_3_3_2 = 102_C_INT
 integer(C_INT), parameter, public :: KVAERNO_4_2_3 = 103_C_INT
 integer(C_INT), parameter, public :: ARK324L2SA_DIRK_4_2_3 = 104_C_INT
 integer(C_INT), parameter, public :: CASH_5_2_4 = 105_C_INT
 integer(C_INT), parameter, public :: CASH_5_3_4 = 106_C_INT
 integer(C_INT), parameter, public :: SDIRK_5_3_4 = 107_C_INT
 integer(C_INT), parameter, public :: KVAERNO_5_3_4 = 108_C_INT
 integer(C_INT), parameter, public :: ARK436L2SA_DIRK_6_3_4 = 109_C_INT
 integer(C_INT), parameter, public :: KVAERNO_7_4_5 = 110_C_INT
 integer(C_INT), parameter, public :: ARK548L2SA_DIRK_8_4_5 = 111_C_INT
 integer(C_INT), parameter, public :: ARK437L2SA_DIRK_7_3_4 = 112_C_INT
 integer(C_INT), parameter, public :: ARK548L2SAb_DIRK_8_4_5 = 113_C_INT
 integer(C_INT), parameter, public :: MIN_DIRK_NUM = 100_C_INT
 integer(C_INT), parameter, public :: MAX_DIRK_NUM = 113_C_INT
 public :: FARKodeButcherTable_LoadDIRK
 integer(C_INT), parameter, public :: HEUN_EULER_2_1_2 = 0_C_INT
 integer(C_INT), parameter, public :: BOGACKI_SHAMPINE_4_2_3 = 1_C_INT
 integer(C_INT), parameter, public :: ARK324L2SA_ERK_4_2_3 = 2_C_INT
 integer(C_INT), parameter, public :: ZONNEVELD_5_3_4 = 3_C_INT
 integer(C_INT), parameter, public :: ARK436L2SA_ERK_6_3_4 = 4_C_INT
 integer(C_INT), parameter, public :: SAYFY_ABURUB_6_3_4 = 5_C_INT
 integer(C_INT), parameter, public :: CASH_KARP_6_4_5 = 6_C_INT
 integer(C_INT), parameter, public :: FEHLBERG_6_4_5 = 7_C_INT
 integer(C_INT), parameter, public :: DORMAND_PRINCE_7_4_5 = 8_C_INT
 integer(C_INT), parameter, public :: ARK548L2SA_ERK_8_4_5 = 9_C_INT
 integer(C_INT), parameter, public :: VERNER_8_5_6 = 10_C_INT
 integer(C_INT), parameter, public :: FEHLBERG_13_7_8 = 11_C_INT
 integer(C_INT), parameter, public :: KNOTH_WOLKE_3_3 = 12_C_INT
 integer(C_INT), parameter, public :: ARK437L2SA_ERK_7_3_4 = 13_C_INT
 integer(C_INT), parameter, public :: ARK548L2SAb_ERK_8_4_5 = 14_C_INT
 integer(C_INT), parameter, public :: MIN_ERK_NUM = 0_C_INT
 integer(C_INT), parameter, public :: MAX_ERK_NUM = 14_C_INT
 public :: FARKodeButcherTable_LoadERK
 integer(C_INT), parameter, public :: ARKLS_SUCCESS = 0_C_INT
 integer(C_INT), parameter, public :: ARKLS_MEM_NULL = -1_C_INT
 integer(C_INT), parameter, public :: ARKLS_LMEM_NULL = -2_C_INT
 integer(C_INT), parameter, public :: ARKLS_ILL_INPUT = -3_C_INT
 integer(C_INT), parameter, public :: ARKLS_MEM_FAIL = -4_C_INT
 integer(C_INT), parameter, public :: ARKLS_PMEM_NULL = -5_C_INT
 integer(C_INT), parameter, public :: ARKLS_MASSMEM_NULL = -6_C_INT
 integer(C_INT), parameter, public :: ARKLS_JACFUNC_UNRECVR = -7_C_INT
 integer(C_INT), parameter, public :: ARKLS_JACFUNC_RECVR = -8_C_INT
 integer(C_INT), parameter, public :: ARKLS_MASSFUNC_UNRECVR = -9_C_INT
 integer(C_INT), parameter, public :: ARKLS_MASSFUNC_RECVR = -10_C_INT
 integer(C_INT), parameter, public :: ARKLS_SUNMAT_FAIL = -11_C_INT
 integer(C_INT), parameter, public :: ARKLS_SUNLS_FAIL = -12_C_INT

! WRAPPER DECLARATIONS
interface
function swigc_FARKBandPrecInit(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FARKBandPrecInit") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T), intent(in) :: farg2
integer(C_INT64_T), intent(in) :: farg3
integer(C_INT64_T), intent(in) :: farg4
integer(C_INT) :: fresult
end function

function swigc_FARKBandPrecGetWorkSpace(farg1, farg2, farg3) &
bind(C, name="_wrap_FARKBandPrecGetWorkSpace") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FARKBandPrecGetNumRhsEvals(farg1, farg2) &
bind(C, name="_wrap_FARKBandPrecGetNumRhsEvals") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FARKBBDPrecInit(farg1, farg2, farg3, farg4, farg5, farg6, farg7, farg8, farg9) &
bind(C, name="_wrap_FARKBBDPrecInit") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T), intent(in) :: farg2
integer(C_INT64_T), intent(in) :: farg3
integer(C_INT64_T), intent(in) :: farg4
integer(C_INT64_T), intent(in) :: farg5
integer(C_INT64_T), intent(in) :: farg6
real(C_DOUBLE), intent(in) :: farg7
type(C_FUNPTR), value :: farg8
type(C_FUNPTR), value :: farg9
integer(C_INT) :: fresult
end function

function swigc_FARKBBDPrecReInit(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FARKBBDPrecReInit") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T), intent(in) :: farg2
integer(C_INT64_T), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
integer(C_INT) :: fresult
end function

function swigc_FARKBBDPrecGetWorkSpace(farg1, farg2, farg3) &
bind(C, name="_wrap_FARKBBDPrecGetWorkSpace") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FARKBBDPrecGetNumGfnEvals(farg1, farg2) &
bind(C, name="_wrap_FARKBBDPrecGetNumGfnEvals") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

subroutine swigc_ARKodeButcherTable_q_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_q_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT), intent(in) :: farg2
end subroutine

function swigc_ARKodeButcherTable_q_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_q_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_ARKodeButcherTable_p_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_p_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT), intent(in) :: farg2
end subroutine

function swigc_ARKodeButcherTable_p_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_p_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_ARKodeButcherTable_stages_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_stages_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT), intent(in) :: farg2
end subroutine

function swigc_ARKodeButcherTable_stages_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_stages_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_ARKodeButcherTable_A_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_A_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_ARKodeButcherTable_A_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_A_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_ARKodeButcherTable_c_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_c_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_ARKodeButcherTable_c_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_c_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_ARKodeButcherTable_b_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_b_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_ARKodeButcherTable_b_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_b_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_ARKodeButcherTable_d_set(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_d_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_ARKodeButcherTable_d_get(farg1) &
bind(C, name="_wrap_ARKodeButcherTable_d_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

function swigc_new_ARKodeButcherTable() &
bind(C, name="_wrap_new_ARKodeButcherTable") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: fresult
end function

subroutine swigc_delete_ARKodeButcherTable(farg1) &
bind(C, name="_wrap_delete_ARKodeButcherTable")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper), intent(inout) :: farg1
end subroutine

subroutine swigc_ARKodeButcherTable_op_assign__(farg1, farg2) &
bind(C, name="_wrap_ARKodeButcherTable_op_assign__")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper), intent(inout) :: farg1
type(SwigClassWrapper) :: farg2
end subroutine

function swigc_FARKodeButcherTable_Alloc(farg1, farg2) &
bind(C, name="_wrap_FARKodeButcherTable_Alloc") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
integer(C_INT), intent(in) :: farg1
integer(C_INT), intent(in) :: farg2
type(SwigClassWrapper) :: fresult
end function

function swigc_FARKodeButcherTable_Create(farg1, farg2, farg3, farg4, farg5, farg6, farg7) &
bind(C, name="_wrap_FARKodeButcherTable_Create") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
integer(C_INT), intent(in) :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT), intent(in) :: farg3
type(C_PTR), value :: farg4
type(C_PTR), value :: farg5
type(C_PTR), value :: farg6
type(C_PTR), value :: farg7
type(SwigClassWrapper) :: fresult
end function

function swigc_FARKodeButcherTable_Copy(farg1) &
bind(C, name="_wrap_FARKodeButcherTable_Copy") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(SwigClassWrapper) :: fresult
end function

subroutine swigc_FARKodeButcherTable_Space(farg1, farg2, farg3) &
bind(C, name="_wrap_FARKodeButcherTable_Space")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
end subroutine

subroutine swigc_FARKodeButcherTable_Free(farg1) &
bind(C, name="_wrap_FARKodeButcherTable_Free")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
end subroutine

subroutine swigc_FARKodeButcherTable_Write(farg1, farg2) &
bind(C, name="_wrap_FARKodeButcherTable_Write")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_FARKodeButcherTable_CheckOrder(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FARKodeButcherTable_CheckOrder") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FARKodeButcherTable_CheckARKOrder(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FARKodeButcherTable_CheckARKOrder") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(SwigClassWrapper) :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
type(C_PTR), value :: farg5
integer(C_INT) :: fresult
end function

function swigc_FARKodeButcherTable_LoadDIRK(farg1) &
bind(C, name="_wrap_FARKodeButcherTable_LoadDIRK") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
integer(C_INT), intent(in) :: farg1
type(SwigClassWrapper) :: fresult
end function

function swigc_FARKodeButcherTable_LoadERK(farg1) &
bind(C, name="_wrap_FARKodeButcherTable_LoadERK") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
integer(C_INT), intent(in) :: farg1
type(SwigClassWrapper) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FARKBandPrecInit(arkode_mem, n, mu, ml) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT64_T), intent(in) :: n
integer(C_INT64_T), intent(in) :: mu
integer(C_INT64_T), intent(in) :: ml
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT64_T) :: farg2 
integer(C_INT64_T) :: farg3 
integer(C_INT64_T) :: farg4 

farg1 = arkode_mem
farg2 = n
farg3 = mu
farg4 = ml
fresult = swigc_FARKBandPrecInit(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FARKBandPrecGetWorkSpace(arkode_mem, lenrwls, leniwls) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_LONG), dimension(*), target, intent(inout) :: lenrwls
integer(C_LONG), dimension(*), target, intent(inout) :: leniwls
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = arkode_mem
farg2 = c_loc(lenrwls(1))
farg3 = c_loc(leniwls(1))
fresult = swigc_FARKBandPrecGetWorkSpace(farg1, farg2, farg3)
swig_result = fresult
end function

function FARKBandPrecGetNumRhsEvals(arkode_mem, nfevalsbp) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_LONG), dimension(*), target, intent(inout) :: nfevalsbp
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = arkode_mem
farg2 = c_loc(nfevalsbp(1))
fresult = swigc_FARKBandPrecGetNumRhsEvals(farg1, farg2)
swig_result = fresult
end function

function FARKBBDPrecInit(arkode_mem, nlocal, mudq, mldq, mukeep, mlkeep, dqrely, gloc, cfn) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT64_T), intent(in) :: nlocal
integer(C_INT64_T), intent(in) :: mudq
integer(C_INT64_T), intent(in) :: mldq
integer(C_INT64_T), intent(in) :: mukeep
integer(C_INT64_T), intent(in) :: mlkeep
real(C_DOUBLE), intent(in) :: dqrely
type(C_FUNPTR), intent(in), value :: gloc
type(C_FUNPTR), intent(in), value :: cfn
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT64_T) :: farg2 
integer(C_INT64_T) :: farg3 
integer(C_INT64_T) :: farg4 
integer(C_INT64_T) :: farg5 
integer(C_INT64_T) :: farg6 
real(C_DOUBLE) :: farg7 
type(C_FUNPTR) :: farg8 
type(C_FUNPTR) :: farg9 

farg1 = arkode_mem
farg2 = nlocal
farg3 = mudq
farg4 = mldq
farg5 = mukeep
farg6 = mlkeep
farg7 = dqrely
farg8 = gloc
farg9 = cfn
fresult = swigc_FARKBBDPrecInit(farg1, farg2, farg3, farg4, farg5, farg6, farg7, farg8, farg9)
swig_result = fresult
end function

function FARKBBDPrecReInit(arkode_mem, mudq, mldq, dqrely) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT64_T), intent(in) :: mudq
integer(C_INT64_T), intent(in) :: mldq
real(C_DOUBLE), intent(in) :: dqrely
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT64_T) :: farg2 
integer(C_INT64_T) :: farg3 
real(C_DOUBLE) :: farg4 

farg1 = arkode_mem
farg2 = mudq
farg3 = mldq
farg4 = dqrely
fresult = swigc_FARKBBDPrecReInit(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FARKBBDPrecGetWorkSpace(arkode_mem, lenrwbbdp, leniwbbdp) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_LONG), dimension(*), target, intent(inout) :: lenrwbbdp
integer(C_LONG), dimension(*), target, intent(inout) :: leniwbbdp
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = arkode_mem
farg2 = c_loc(lenrwbbdp(1))
farg3 = c_loc(leniwbbdp(1))
fresult = swigc_FARKBBDPrecGetWorkSpace(farg1, farg2, farg3)
swig_result = fresult
end function

function FARKBBDPrecGetNumGfnEvals(arkode_mem, ngevalsbbdp) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_LONG), dimension(*), target, intent(inout) :: ngevalsbbdp
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = arkode_mem
farg2 = c_loc(ngevalsbbdp(1))
fresult = swigc_FARKBBDPrecGetNumGfnEvals(farg1, farg2)
swig_result = fresult
end function

subroutine swigf_ARKodeButcherTable_q_set(self, q)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
integer(C_INT), intent(in) :: q
type(SwigClassWrapper) :: farg1 
integer(C_INT) :: farg2 

farg1 = self%swigdata
farg2 = q
call swigc_ARKodeButcherTable_q_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_q_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(ARKodeButcherTable), intent(in) :: self
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_q_get(farg1)
swig_result = fresult
end function

subroutine swigf_ARKodeButcherTable_p_set(self, p)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
integer(C_INT), intent(in) :: p
type(SwigClassWrapper) :: farg1 
integer(C_INT) :: farg2 

farg1 = self%swigdata
farg2 = p
call swigc_ARKodeButcherTable_p_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_p_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(ARKodeButcherTable), intent(in) :: self
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_p_get(farg1)
swig_result = fresult
end function

subroutine swigf_ARKodeButcherTable_stages_set(self, stages)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
integer(C_INT), intent(in) :: stages
type(SwigClassWrapper) :: farg1 
integer(C_INT) :: farg2 

farg1 = self%swigdata
farg2 = stages
call swigc_ARKodeButcherTable_stages_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_stages_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(ARKodeButcherTable), intent(in) :: self
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_stages_get(farg1)
swig_result = fresult
end function

subroutine swigf_ARKodeButcherTable_A_set(self, a)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
type(C_PTR), target, intent(inout) :: a
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = c_loc(a)
call swigc_ARKodeButcherTable_A_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_A_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), pointer :: swig_result
class(ARKodeButcherTable), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_A_get(farg1)
call c_f_pointer(fresult, swig_result)
end function

subroutine swigf_ARKodeButcherTable_c_set(self, c)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
real(C_DOUBLE), dimension(*), target, intent(inout) :: c
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = c_loc(c(1))
call swigc_ARKodeButcherTable_c_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_c_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), dimension(:), pointer :: swig_result
class(ARKodeButcherTable), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_c_get(farg1)
call c_f_pointer(fresult, swig_result, [1])
end function

subroutine swigf_ARKodeButcherTable_b_set(self, b)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
real(C_DOUBLE), dimension(*), target, intent(inout) :: b
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = c_loc(b(1))
call swigc_ARKodeButcherTable_b_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_b_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), dimension(:), pointer :: swig_result
class(ARKodeButcherTable), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_b_get(farg1)
call c_f_pointer(fresult, swig_result, [1])
end function

subroutine swigf_ARKodeButcherTable_d_set(self, d)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: self
real(C_DOUBLE), dimension(*), target, intent(inout) :: d
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = c_loc(d(1))
call swigc_ARKodeButcherTable_d_set(farg1, farg2)
end subroutine

function swigf_ARKodeButcherTable_d_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), dimension(:), pointer :: swig_result
class(ARKodeButcherTable), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_ARKodeButcherTable_d_get(farg1)
call c_f_pointer(fresult, swig_result, [1])
end function

function swigf_create_ARKodeButcherTable() &
result(self)
use, intrinsic :: ISO_C_BINDING
type(ARKodeButcherTable) :: self
type(SwigClassWrapper) :: fresult 

fresult = swigc_new_ARKodeButcherTable()
self%swigdata = fresult
end function

subroutine swigf_release_ARKodeButcherTable(self)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(inout) :: self
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
if (btest(farg1%cmemflags, swig_cmem_own_bit)) then
call swigc_delete_ARKodeButcherTable(farg1)
endif
farg1%cptr = C_NULL_PTR
farg1%cmemflags = 0
self%swigdata = farg1
end subroutine

subroutine swigf_ARKodeButcherTable_op_assign__(self, other)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(inout) :: self
type(ARKodeButcherTable), intent(in) :: other
type(SwigClassWrapper) :: farg1 
type(SwigClassWrapper) :: farg2 

farg1 = self%swigdata
farg2 = other%swigdata
call swigc_ARKodeButcherTable_op_assign__(farg1, farg2)
self%swigdata = farg1
end subroutine

function FARKodeButcherTable_Alloc(stages, embedded) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(ARKodeButcherTable) :: swig_result
integer(C_INT), intent(in) :: stages
integer(C_INT), intent(in) :: embedded
type(SwigClassWrapper) :: fresult 
integer(C_INT) :: farg1 
integer(C_INT) :: farg2 

farg1 = stages
farg2 = embedded
fresult = swigc_FARKodeButcherTable_Alloc(farg1, farg2)
swig_result%swigdata = fresult
end function

function FARKodeButcherTable_Create(s, q, p, c, a, b, d) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(ARKodeButcherTable) :: swig_result
integer(C_INT), intent(in) :: s
integer(C_INT), intent(in) :: q
integer(C_INT), intent(in) :: p
real(C_DOUBLE), dimension(*), target, intent(inout) :: c
real(C_DOUBLE), dimension(*), target, intent(inout) :: a
real(C_DOUBLE), dimension(*), target, intent(inout) :: b
real(C_DOUBLE), dimension(*), target, intent(inout) :: d
type(SwigClassWrapper) :: fresult 
integer(C_INT) :: farg1 
integer(C_INT) :: farg2 
integer(C_INT) :: farg3 
type(C_PTR) :: farg4 
type(C_PTR) :: farg5 
type(C_PTR) :: farg6 
type(C_PTR) :: farg7 

farg1 = s
farg2 = q
farg3 = p
farg4 = c_loc(c(1))
farg5 = c_loc(a(1))
farg6 = c_loc(b(1))
farg7 = c_loc(d(1))
fresult = swigc_FARKodeButcherTable_Create(farg1, farg2, farg3, farg4, farg5, farg6, farg7)
swig_result%swigdata = fresult
end function

function FARKodeButcherTable_Copy(b) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(ARKodeButcherTable) :: swig_result
class(ARKodeButcherTable), intent(in) :: b
type(SwigClassWrapper) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = b%swigdata
fresult = swigc_FARKodeButcherTable_Copy(farg1)
swig_result%swigdata = fresult
end function

subroutine FARKodeButcherTable_Space(b, liw, lrw)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: b
integer(C_INT64_T), dimension(*), target, intent(inout) :: liw
integer(C_INT64_T), dimension(*), target, intent(inout) :: lrw
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = b%swigdata
farg2 = c_loc(liw(1))
farg3 = c_loc(lrw(1))
call swigc_FARKodeButcherTable_Space(farg1, farg2, farg3)
end subroutine

subroutine FARKodeButcherTable_Free(b)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: b
type(SwigClassWrapper) :: farg1 

farg1 = b%swigdata
call swigc_FARKodeButcherTable_Free(farg1)
end subroutine

subroutine FARKodeButcherTable_Write(b, outfile)
use, intrinsic :: ISO_C_BINDING
class(ARKodeButcherTable), intent(in) :: b
type(C_PTR) :: outfile
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = b%swigdata
farg2 = outfile
call swigc_FARKodeButcherTable_Write(farg1, farg2)
end subroutine

function FARKodeButcherTable_CheckOrder(b, q, p, outfile) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(ARKodeButcherTable), intent(in) :: b
integer(C_INT), dimension(*), target, intent(inout) :: q
integer(C_INT), dimension(*), target, intent(inout) :: p
type(C_PTR) :: outfile
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 

farg1 = b%swigdata
farg2 = c_loc(q(1))
farg3 = c_loc(p(1))
farg4 = outfile
fresult = swigc_FARKodeButcherTable_CheckOrder(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FARKodeButcherTable_CheckARKOrder(b1, b2, q, p, outfile) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(ARKodeButcherTable), intent(in) :: b1
class(ARKodeButcherTable), intent(in) :: b2
integer(C_INT), dimension(*), target, intent(inout) :: q
integer(C_INT), dimension(*), target, intent(inout) :: p
type(C_PTR) :: outfile
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 
type(SwigClassWrapper) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 
type(C_PTR) :: farg5 

farg1 = b1%swigdata
farg2 = b2%swigdata
farg3 = c_loc(q(1))
farg4 = c_loc(p(1))
farg5 = outfile
fresult = swigc_FARKodeButcherTable_CheckARKOrder(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FARKodeButcherTable_LoadDIRK(imethod) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(ARKodeButcherTable) :: swig_result
integer(C_INT), intent(in) :: imethod
type(SwigClassWrapper) :: fresult 
integer(C_INT) :: farg1 

farg1 = imethod
fresult = swigc_FARKodeButcherTable_LoadDIRK(farg1)
swig_result%swigdata = fresult
end function

function FARKodeButcherTable_LoadERK(imethod) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(ARKodeButcherTable) :: swig_result
integer(C_INT), intent(in) :: imethod
type(SwigClassWrapper) :: fresult 
integer(C_INT) :: farg1 

farg1 = imethod
fresult = swigc_FARKodeButcherTable_LoadERK(farg1)
swig_result%swigdata = fresult
end function


end module
