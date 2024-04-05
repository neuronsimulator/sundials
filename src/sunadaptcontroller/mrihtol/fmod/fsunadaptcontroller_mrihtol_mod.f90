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

module fsunadaptcontroller_mrihtol_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_core_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 public :: FSUNAdaptController_MRIHTol
 public :: FSUNAdaptController_GetSlowController_MRIHTol
 public :: FSUNAdaptController_GetFastController_MRIHTol
 public :: FSUNAdaptController_GetType_MRIHTol
 public :: FSUNAdaptController_EstimateStepTol_MRIHTol
 public :: FSUNAdaptController_Reset_MRIHTol
 public :: FSUNAdaptController_SetDefaults_MRIHTol
 public :: FSUNAdaptController_Write_MRIHTol
 public :: FSUNAdaptController_SetErrorBias_MRIHTol
 public :: FSUNAdaptController_UpdateMRITol_MRIHTol
 public :: FSUNAdaptController_Space_MRIHTol

! WRAPPER DECLARATIONS
interface
function swigc_FSUNAdaptController_MRIHTol(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_GetSlowController_MRIHTol(farg1) &
bind(C, name="_wrap_FSUNAdaptController_GetSlowController_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_GetFastController_MRIHTol(farg1) &
bind(C, name="_wrap_FSUNAdaptController_GetFastController_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_GetType_MRIHTol(farg1) &
bind(C, name="_wrap_FSUNAdaptController_GetType_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_EstimateStepTol_MRIHTol(farg1, farg2, farg3, farg4, farg5, farg6, farg7, farg8) &
bind(C, name="_wrap_FSUNAdaptController_EstimateStepTol_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT), intent(in) :: farg4
real(C_DOUBLE), intent(in) :: farg5
real(C_DOUBLE), intent(in) :: farg6
type(C_PTR), value :: farg7
type(C_PTR), value :: farg8
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Reset_MRIHTol(farg1) &
bind(C, name="_wrap_FSUNAdaptController_Reset_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_SetDefaults_MRIHTol(farg1) &
bind(C, name="_wrap_FSUNAdaptController_SetDefaults_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Write_MRIHTol(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_Write_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_SetErrorBias_MRIHTol(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_SetErrorBias_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_UpdateMRITol_MRIHTol(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNAdaptController_UpdateMRITol_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Space_MRIHTol(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_Space_MRIHTol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNAdaptController_MRIHTol(sunctx, hcontrol, tolcontrol) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(SUNAdaptController), target, intent(inout) :: hcontrol
type(SUNAdaptController), target, intent(inout) :: tolcontrol
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = sunctx
farg2 = c_loc(hcontrol)
farg3 = c_loc(tolcontrol)
fresult = swigc_FSUNAdaptController_MRIHTol(farg1, farg2, farg3)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_GetSlowController_MRIHTol(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_GetSlowController_MRIHTol(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_GetFastController_MRIHTol(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_GetFastController_MRIHTol(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_GetType_MRIHTol(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNAdaptController_Type) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_GetType_MRIHTol(farg1)
swig_result = fresult
end function

function FSUNAdaptController_EstimateStepTol_MRIHTol(c, h, tolfac, p, dsm, dsm5, hnew, tolfacnew) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
real(C_DOUBLE), intent(in) :: tolfac
integer(C_INT), intent(in) :: p
real(C_DOUBLE), intent(in) :: dsm
real(C_DOUBLE), intent(in) :: dsm5
real(C_DOUBLE), dimension(*), target, intent(inout) :: hnew
real(C_DOUBLE), dimension(*), target, intent(inout) :: tolfacnew
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
integer(C_INT) :: farg4 
real(C_DOUBLE) :: farg5 
real(C_DOUBLE) :: farg6 
type(C_PTR) :: farg7 
type(C_PTR) :: farg8 

farg1 = c_loc(c)
farg2 = h
farg3 = tolfac
farg4 = p
farg5 = dsm
farg6 = dsm5
farg7 = c_loc(hnew(1))
farg8 = c_loc(tolfacnew(1))
fresult = swigc_FSUNAdaptController_EstimateStepTol_MRIHTol(farg1, farg2, farg3, farg4, farg5, farg6, farg7, farg8)
swig_result = fresult
end function

function FSUNAdaptController_Reset_MRIHTol(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_Reset_MRIHTol(farg1)
swig_result = fresult
end function

function FSUNAdaptController_SetDefaults_MRIHTol(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_SetDefaults_MRIHTol(farg1)
swig_result = fresult
end function

function FSUNAdaptController_Write_MRIHTol(c, fptr) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
type(C_PTR) :: fptr
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(c)
farg2 = fptr
fresult = swigc_FSUNAdaptController_Write_MRIHTol(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_SetErrorBias_MRIHTol(c, bias) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: bias
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 

farg1 = c_loc(c)
farg2 = bias
fresult = swigc_FSUNAdaptController_SetErrorBias_MRIHTol(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_UpdateMRITol_MRIHTol(c, h, tolfac, dsm, dsm4) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
real(C_DOUBLE), intent(in) :: tolfac
real(C_DOUBLE), intent(in) :: dsm
real(C_DOUBLE), intent(in) :: dsm4
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
real(C_DOUBLE) :: farg4 
real(C_DOUBLE) :: farg5 

farg1 = c_loc(c)
farg2 = h
farg3 = tolfac
farg4 = dsm
farg5 = dsm4
fresult = swigc_FSUNAdaptController_UpdateMRITol_MRIHTol(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNAdaptController_Space_MRIHTol(c, lenrw, leniw) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_LONG), dimension(*), target, intent(inout) :: lenrw
integer(C_LONG), dimension(*), target, intent(inout) :: leniw
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(c)
farg2 = c_loc(lenrw(1))
farg3 = c_loc(leniw(1))
fresult = swigc_FSUNAdaptController_Space_MRIHTol(farg1, farg2, farg3)
swig_result = fresult
end function


end module