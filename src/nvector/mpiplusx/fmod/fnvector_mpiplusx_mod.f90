! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.

! ---------------------------------------------------------------
! Programmer(s): Auto-generated by swig.
! ---------------------------------------------------------------
! SUNDIALS Copyright Start
! Copyright (c) 2002-2024, Lawrence Livermore National Security
! and Southern Methodist University.
! All rights reserved.
!
! See the top-level LICENSE and NOTICE files for details.
!
! SPDX-License-Identifier: BSD-3-Clause
! SUNDIALS Copyright End
! ---------------------------------------------------------------

module fnvector_mpiplusx_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_core_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 public :: FN_VMake_MPIPlusX
 public :: FN_VGetVectorID_MPIPlusX
 public :: FN_VSetArrayPointer_MPIPlusX
 public :: FN_VGetLocalVector_MPIPlusX
 public :: FN_VGetLocalLength_MPIPlusX
 public :: FN_VEnableFusedOps_MPIPlusX
 public :: FN_VPrint_MPIPlusX
 public :: FN_VPrintFile_MPIPlusX

 public :: FN_VGetArrayPointer_MPIPlusX


! WRAPPER DECLARATIONS
interface
function swigc_FN_VMake_MPIPlusX(farg1, farg2, farg3) &
bind(C, name="_wrap_FN_VMake_MPIPlusX") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR) :: fresult
end function

function swigc_FN_VGetVectorID_MPIPlusX(farg1) &
bind(C, name="_wrap_FN_VGetVectorID_MPIPlusX") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_FN_VSetArrayPointer_MPIPlusX(farg1, farg2) &
bind(C, name="_wrap_FN_VSetArrayPointer_MPIPlusX")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_FN_VGetLocalVector_MPIPlusX(farg1) &
bind(C, name="_wrap_FN_VGetLocalVector_MPIPlusX") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FN_VGetLocalLength_MPIPlusX(farg1) &
bind(C, name="_wrap_FN_VGetLocalLength_MPIPlusX") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T) :: fresult
end function

function swigc_FN_VEnableFusedOps_MPIPlusX(farg1, farg2) &
bind(C, name="_wrap_FN_VEnableFusedOps_MPIPlusX") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

subroutine swigc_FN_VPrint_MPIPlusX(farg1) &
bind(C, name="_wrap_FN_VPrint_MPIPlusX")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
end subroutine

subroutine swigc_FN_VPrintFile_MPIPlusX(farg1, farg2) &
bind(C, name="_wrap_FN_VPrintFile_MPIPlusX")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
end subroutine


function swigc_FN_VGetArrayPointer_MPIPlusX(farg1) &
bind(C, name="_wrap_FN_VGetArrayPointer_MPIPlusX") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FN_VMake_MPIPlusX(comm, x, sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(N_Vector), pointer :: swig_result
integer :: comm
type(N_Vector), target, intent(inout) :: x
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
integer(C_INT) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = int(comm, C_INT)
farg2 = c_loc(x)
farg3 = sunctx
fresult = swigc_FN_VMake_MPIPlusX(farg1, farg2, farg3)
call c_f_pointer(fresult, swig_result)
end function

function FN_VGetVectorID_MPIPlusX(v) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(N_Vector_ID) :: swig_result
type(N_Vector), target, intent(inout) :: v
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(v)
fresult = swigc_FN_VGetVectorID_MPIPlusX(farg1)
swig_result = fresult
end function

subroutine FN_VSetArrayPointer_MPIPlusX(vdata, v)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), dimension(*), target, intent(inout) :: vdata
type(N_Vector), target, intent(inout) :: v
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(vdata(1))
farg2 = c_loc(v)
call swigc_FN_VSetArrayPointer_MPIPlusX(farg1, farg2)
end subroutine

function FN_VGetLocalVector_MPIPlusX(v) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(N_Vector), pointer :: swig_result
type(N_Vector), target, intent(inout) :: v
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(v)
fresult = swigc_FN_VGetLocalVector_MPIPlusX(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FN_VGetLocalLength_MPIPlusX(v) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T) :: swig_result
type(N_Vector), target, intent(inout) :: v
integer(C_INT64_T) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(v)
fresult = swigc_FN_VGetLocalLength_MPIPlusX(farg1)
swig_result = fresult
end function

function FN_VEnableFusedOps_MPIPlusX(v, tf) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(N_Vector), target, intent(inout) :: v
integer(C_INT), intent(in) :: tf
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(v)
farg2 = tf
fresult = swigc_FN_VEnableFusedOps_MPIPlusX(farg1, farg2)
swig_result = fresult
end function

subroutine FN_VPrint_MPIPlusX(x)
use, intrinsic :: ISO_C_BINDING
type(N_Vector), target, intent(inout) :: x
type(C_PTR) :: farg1 

farg1 = c_loc(x)
call swigc_FN_VPrint_MPIPlusX(farg1)
end subroutine

subroutine FN_VPrintFile_MPIPlusX(x, outfile)
use, intrinsic :: ISO_C_BINDING
type(N_Vector), target, intent(inout) :: x
type(C_PTR) :: outfile
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(x)
farg2 = outfile
call swigc_FN_VPrintFile_MPIPlusX(farg1, farg2)
end subroutine


function FN_VGetArrayPointer_MPIPlusX(v) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), dimension(:), pointer :: swig_result
type(N_Vector), target, intent(inout) :: v
type(C_PTR) :: fresult
type(C_PTR) :: farg1

farg1 = c_loc(v)
fresult = swigc_FN_VGetArrayPointer_MPIPlusX(farg1)
call c_f_pointer(fresult, swig_result, [FN_VGetLocalLength_MPIPlusX(v)])
end function


end module
