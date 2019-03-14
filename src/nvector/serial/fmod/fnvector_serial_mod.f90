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

module fnvector_serial_mod
 use, intrinsic :: ISO_C_BINDING
 use fnvector_mod
 use fsundials_types
 implicit none
 private

 ! PUBLIC METHODS AND TYPES

  public :: FN_VGetData_Serial
  
 public :: FN_VNew_Serial
 public :: FN_VNewEmpty_Serial
 public :: FN_VMake_Serial
 public :: FN_VCloneVectorArray_Serial
 public :: FN_VCloneVectorArrayEmpty_Serial
 public :: FN_VDestroyVectorArray_Serial
 public :: FN_VGetLength_Serial
 public :: FN_VPrint_Serial
 public :: FN_VPrintFile_Serial
 public :: FN_VGetVectorID_Serial
 public :: FN_VCloneEmpty_Serial
 public :: FN_VClone_Serial
 public :: FN_VDestroy_Serial
 public :: FN_VSpace_Serial
 public :: FN_VGetArrayPointer_Serial
 public :: FN_VSetArrayPointer_Serial
 public :: FN_VLinearSum_Serial
 public :: FN_VConst_Serial
 public :: FN_VProd_Serial
 public :: FN_VDiv_Serial
 public :: FN_VScale_Serial
 public :: FN_VAbs_Serial
 public :: FN_VInv_Serial
 public :: FN_VAddConst_Serial
 public :: FN_VDotProd_Serial
 public :: FN_VMaxNorm_Serial
 public :: FN_VWrmsNorm_Serial
 public :: FN_VWrmsNormMask_Serial
 public :: FN_VMin_Serial
 public :: FN_VWL2Norm_Serial
 public :: FN_VL1Norm_Serial
 public :: FN_VCompare_Serial
 public :: FN_VInvTest_Serial
 public :: FN_VConstrMask_Serial
 public :: FN_VMinQuotient_Serial
 public :: FN_VLinearCombination_Serial
 public :: FN_VScaleAddMulti_Serial
 public :: FN_VDotProdMulti_Serial
 public :: FN_VLinearSumVectorArray_Serial
 public :: FN_VScaleVectorArray_Serial
 public :: FN_VConstVectorArray_Serial
 public :: FN_VWrmsNormVectorArray_Serial
 public :: FN_VWrmsNormMaskVectorArray_Serial
 public :: FN_VScaleAddMultiVectorArray_Serial
 public :: FN_VLinearCombinationVectorArray_Serial
 public :: FN_VEnableFusedOps_Serial
 public :: FN_VEnableLinearCombination_Serial
 public :: FN_VEnableScaleAddMulti_Serial
 public :: FN_VEnableDotProdMulti_Serial
 public :: FN_VEnableLinearSumVectorArray_Serial
 public :: FN_VEnableScaleVectorArray_Serial
 public :: FN_VEnableConstVectorArray_Serial
 public :: FN_VEnableWrmsNormVectorArray_Serial
 public :: FN_VEnableWrmsNormMaskVectorArray_Serial
 public :: FN_VEnableScaleAddMultiVectorArray_Serial
 public :: FN_VEnableLinearCombinationVectorArray_Serial

 ! WRAPPER DECLARATIONS
 interface
function FN_VNew_Serial(vec_length) &
bind(C, name="N_VNew_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T), value :: vec_length
type(C_PTR) :: fresult
end function

function FN_VNewEmpty_Serial(vec_length) &
bind(C, name="N_VNewEmpty_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T), value :: vec_length
type(C_PTR) :: fresult
end function

function FN_VMake_Serial(vec_length, v_data) &
bind(C, name="N_VMake_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T), value :: vec_length
real(C_DOUBLE), dimension(*) :: v_data
type(C_PTR) :: fresult
end function

function FN_VCloneVectorArray_Serial(count, w) &
bind(C, name="N_VCloneVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: count
type(C_PTR), value :: w
type(C_PTR) :: fresult
end function

function FN_VCloneVectorArrayEmpty_Serial(count, w) &
bind(C, name="N_VCloneVectorArrayEmpty_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: count
type(C_PTR), value :: w
type(C_PTR) :: fresult
end function

subroutine FN_VDestroyVectorArray_Serial(vs, count) &
bind(C, name="N_VDestroyVectorArray_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: vs
integer(C_INT), value :: count
end subroutine

function FN_VGetLength_Serial(v) &
bind(C, name="N_VGetLength_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
integer(C_INT64_T) :: fresult
end function

subroutine FN_VPrint_Serial(v) &
bind(C, name="N_VPrint_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
end subroutine

subroutine FN_VPrintFile_Serial(v, outfile) &
bind(C, name="N_VPrintFile_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
type(C_PTR), value :: outfile
end subroutine

function FN_VGetVectorID_Serial(v) &
bind(C, name="N_VGetVectorID_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
integer(C_INT) :: fresult
end function

function FN_VCloneEmpty_Serial(w) &
bind(C, name="N_VCloneEmpty_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: w
type(C_PTR) :: fresult
end function

function FN_VClone_Serial(w) &
bind(C, name="N_VClone_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: w
type(C_PTR) :: fresult
end function

subroutine FN_VDestroy_Serial(v) &
bind(C, name="N_VDestroy_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
end subroutine

subroutine FN_VSpace_Serial(v, lrw, liw) &
bind(C, name="N_VSpace_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
integer(C_INT64_T) :: lrw
integer(C_INT64_T) :: liw
end subroutine

function FN_VGetArrayPointer_Serial(v) &
bind(C, name="N_VGetArrayPointer_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
type(C_PTR) :: fresult
end function

subroutine FN_VSetArrayPointer_Serial(v_data, v) &
bind(C, name="N_VSetArrayPointer_Serial")
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), dimension(*) :: v_data
type(C_PTR), value :: v
end subroutine

subroutine FN_VLinearSum_Serial(a, x, b, y, z) &
bind(C, name="N_VLinearSum_Serial")
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), value :: a
type(C_PTR), value :: x
real(C_DOUBLE), value :: b
type(C_PTR), value :: y
type(C_PTR), value :: z
end subroutine

subroutine FN_VConst_Serial(c, z) &
bind(C, name="N_VConst_Serial")
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), value :: c
type(C_PTR), value :: z
end subroutine

subroutine FN_VProd_Serial(x, y, z) &
bind(C, name="N_VProd_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: y
type(C_PTR), value :: z
end subroutine

subroutine FN_VDiv_Serial(x, y, z) &
bind(C, name="N_VDiv_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: y
type(C_PTR), value :: z
end subroutine

subroutine FN_VScale_Serial(c, x, z) &
bind(C, name="N_VScale_Serial")
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), value :: c
type(C_PTR), value :: x
type(C_PTR), value :: z
end subroutine

subroutine FN_VAbs_Serial(x, z) &
bind(C, name="N_VAbs_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: z
end subroutine

subroutine FN_VInv_Serial(x, z) &
bind(C, name="N_VInv_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: z
end subroutine

subroutine FN_VAddConst_Serial(x, b, z) &
bind(C, name="N_VAddConst_Serial")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
real(C_DOUBLE), value :: b
type(C_PTR), value :: z
end subroutine

function FN_VDotProd_Serial(x, y) &
bind(C, name="N_VDotProd_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: y
real(C_DOUBLE) :: fresult
end function

function FN_VMaxNorm_Serial(x) &
bind(C, name="N_VMaxNorm_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
real(C_DOUBLE) :: fresult
end function

function FN_VWrmsNorm_Serial(x, w) &
bind(C, name="N_VWrmsNorm_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: w
real(C_DOUBLE) :: fresult
end function

function FN_VWrmsNormMask_Serial(x, w, id) &
bind(C, name="N_VWrmsNormMask_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: w
type(C_PTR), value :: id
real(C_DOUBLE) :: fresult
end function

function FN_VMin_Serial(x) &
bind(C, name="N_VMin_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
real(C_DOUBLE) :: fresult
end function

function FN_VWL2Norm_Serial(x, w) &
bind(C, name="N_VWL2Norm_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: w
real(C_DOUBLE) :: fresult
end function

function FN_VL1Norm_Serial(x) &
bind(C, name="N_VL1Norm_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
real(C_DOUBLE) :: fresult
end function

subroutine FN_VCompare_Serial(c, x, z) &
bind(C, name="N_VCompare_Serial")
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), value :: c
type(C_PTR), value :: x
type(C_PTR), value :: z
end subroutine

function FN_VInvTest_Serial(x, z) &
bind(C, name="N_VInvTest_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: x
type(C_PTR), value :: z
logical(C_BOOL) :: fresult
end function

function FN_VConstrMask_Serial(c, x, m) &
bind(C, name="N_VConstrMask_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: c
type(C_PTR), value :: x
type(C_PTR), value :: m
logical(C_BOOL) :: fresult
end function

function FN_VMinQuotient_Serial(num, denom) &
bind(C, name="N_VMinQuotient_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: num
type(C_PTR), value :: denom
real(C_DOUBLE) :: fresult
end function

function FN_VLinearCombination_Serial(nvec, c, v, z) &
bind(C, name="N_VLinearCombination_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
real(C_DOUBLE) :: c
type(C_PTR), value :: v
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VScaleAddMulti_Serial(nvec, a, x, y, z) &
bind(C, name="N_VScaleAddMulti_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
real(C_DOUBLE) :: a
type(C_PTR), value :: x
type(C_PTR), value :: y
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VDotProdMulti_Serial(nvec, x, y, dotprods) &
bind(C, name="N_VDotProdMulti_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
type(C_PTR), value :: x
type(C_PTR), value :: y
real(C_DOUBLE) :: dotprods
integer(C_INT) :: fresult
end function

function FN_VLinearSumVectorArray_Serial(nvec, a, x, b, y, z) &
bind(C, name="N_VLinearSumVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
real(C_DOUBLE), value :: a
type(C_PTR), value :: x
real(C_DOUBLE), value :: b
type(C_PTR), value :: y
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VScaleVectorArray_Serial(nvec, c, x, z) &
bind(C, name="N_VScaleVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
real(C_DOUBLE) :: c
type(C_PTR), value :: x
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VConstVectorArray_Serial(nvecs, c, z) &
bind(C, name="N_VConstVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvecs
real(C_DOUBLE), value :: c
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VWrmsNormVectorArray_Serial(nvecs, x, w, nrm) &
bind(C, name="N_VWrmsNormVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvecs
type(C_PTR), value :: x
type(C_PTR), value :: w
real(C_DOUBLE) :: nrm
integer(C_INT) :: fresult
end function

function FN_VWrmsNormMaskVectorArray_Serial(nvecs, x, w, id, nrm) &
bind(C, name="N_VWrmsNormMaskVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvecs
type(C_PTR), value :: x
type(C_PTR), value :: w
type(C_PTR), value :: id
real(C_DOUBLE) :: nrm
integer(C_INT) :: fresult
end function

function FN_VScaleAddMultiVectorArray_Serial(nvec, nsum, a, x, y, z) &
bind(C, name="N_VScaleAddMultiVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
integer(C_INT), value :: nsum
real(C_DOUBLE) :: a
type(C_PTR), value :: x
type(C_PTR), value :: y
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VLinearCombinationVectorArray_Serial(nvec, nsum, c, x, z) &
bind(C, name="N_VLinearCombinationVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), value :: nvec
integer(C_INT), value :: nsum
real(C_DOUBLE) :: c
type(C_PTR), value :: x
type(C_PTR), value :: z
integer(C_INT) :: fresult
end function

function FN_VEnableFusedOps_Serial(v, tf) &
bind(C, name="N_VEnableFusedOps_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableLinearCombination_Serial(v, tf) &
bind(C, name="N_VEnableLinearCombination_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableScaleAddMulti_Serial(v, tf) &
bind(C, name="N_VEnableScaleAddMulti_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableDotProdMulti_Serial(v, tf) &
bind(C, name="N_VEnableDotProdMulti_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableLinearSumVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableLinearSumVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableScaleVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableScaleVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableConstVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableConstVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableWrmsNormVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableWrmsNormVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableWrmsNormMaskVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableWrmsNormMaskVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableScaleAddMultiVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableScaleAddMultiVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

function FN_VEnableLinearCombinationVectorArray_Serial(v, tf) &
bind(C, name="N_VEnableLinearCombinationVectorArray_Serial") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: v
logical(C_BOOL), value :: tf
integer(C_INT) :: fresult
end function

 end interface


contains
 ! FORTRAN PROXY CODE

  subroutine FN_VGetData_Serial(vec, vdata)

      use, intrinsic :: iso_c_binding
      implicit none

      type(C_PTR)        :: vec
      integer(C_INT64_T) :: len
      type(C_PTR)        :: cptr
      real(C_DOUBLE), dimension(:), pointer :: vdata

      len = FN_VGetLength_Serial(vec)
      cptr = FN_VGetArrayPointer_Serial(vec)

      call c_f_pointer(cptr, vdata, (/len/))

  end subroutine FN_VGetData_Serial
  

end module