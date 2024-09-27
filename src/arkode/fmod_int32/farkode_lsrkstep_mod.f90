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

module farkode_lsrkstep_mod
 use, intrinsic :: ISO_C_BINDING
 use farkode_mod
 use fsundials_core_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 ! typedef enum ARKODE_LSRKMethodType
 enum, bind(c)
  enumerator :: ARKODE_LSRK_RKC_2 = 0
  enumerator :: ARKODE_LSRK_RKL_2 = 1
  enumerator :: ARKODE_LSRK_SSP_S_2 = 3
  enumerator :: ARKODE_LSRK_SSP_S_3 = 4
  enumerator :: ARKODE_LSRK_SSP_10_4 = 5
 end enum
 integer, parameter, public :: ARKODE_LSRKMethodType = kind(ARKODE_LSRK_RKC_2)
 public :: ARKODE_LSRK_RKC_2, ARKODE_LSRK_RKL_2, ARKODE_LSRK_SSP_S_2, ARKODE_LSRK_SSP_S_3, ARKODE_LSRK_SSP_10_4
 public :: FLSRKStepCreateSTS
 public :: FLSRKStepCreateSSP
 public :: FLSRKStepReInitSTS
 public :: FLSRKStepReInitSSP
 public :: FLSRKStepSetMethod
 type, bind(C) :: SwigArrayWrapper
  type(C_PTR), public :: data = C_NULL_PTR
  integer(C_SIZE_T), public :: size = 0
 end type
 public :: FLSRKStepSetMethodByName
 public :: FLSRKStepSetDomEigFn
 public :: FLSRKStepSetDomEigFrequency
 public :: FLSRKStepSetMaxNumStages
 public :: FLSRKStepSetDomEigSafetyFactor
 public :: FLSRKStepSetSSPStageNum
 public :: FLSRKStepGetNumRhsEvals
 public :: FLSRKStepGetNumDomEigUpdates
 public :: FLSRKStepGetMaxNumStages
 public :: FLSRKStepGetAverageStageNum

! WRAPPER DECLARATIONS
interface
function swigc_FLSRKStepCreateSTS(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FLSRKStepCreateSTS") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_FUNPTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
type(C_PTR) :: fresult
end function

function swigc_FLSRKStepCreateSSP(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FLSRKStepCreateSSP") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_FUNPTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
type(C_PTR) :: fresult
end function

function swigc_FLSRKStepReInitSTS(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FLSRKStepReInitSTS") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
real(C_DOUBLE), intent(in) :: farg3
type(C_PTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepReInitSSP(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FLSRKStepReInitSSP") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
real(C_DOUBLE), intent(in) :: farg3
type(C_PTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetMethod(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetMethod") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetMethodByName(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetMethodByName") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
type(C_PTR), value :: farg1
type(SwigArrayWrapper) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetDomEigFn(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetDomEigFn") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetDomEigFrequency(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetDomEigFrequency") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetMaxNumStages(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetMaxNumStages") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetDomEigSafetyFactor(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetDomEigSafetyFactor") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepSetSSPStageNum(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepSetSSPStageNum") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepGetNumRhsEvals(farg1, farg2, farg3) &
bind(C, name="_wrap_FLSRKStepGetNumRhsEvals") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepGetNumDomEigUpdates(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepGetNumDomEigUpdates") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepGetMaxNumStages(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepGetMaxNumStages") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FLSRKStepGetAverageStageNum(farg1, farg2) &
bind(C, name="_wrap_FLSRKStepGetAverageStageNum") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FLSRKStepCreateSTS(rhs, t0, y0, sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(C_PTR) :: swig_result
type(C_FUNPTR), intent(in), value :: rhs
real(C_DOUBLE), intent(in) :: t0
type(N_Vector), target, intent(inout) :: y0
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_FUNPTR) :: farg1 
real(C_DOUBLE) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 

farg1 = rhs
farg2 = t0
farg3 = c_loc(y0)
farg4 = sunctx
fresult = swigc_FLSRKStepCreateSTS(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FLSRKStepCreateSSP(rhs, t0, y0, sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(C_PTR) :: swig_result
type(C_FUNPTR), intent(in), value :: rhs
real(C_DOUBLE), intent(in) :: t0
type(N_Vector), target, intent(inout) :: y0
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_FUNPTR) :: farg1 
real(C_DOUBLE) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 

farg1 = rhs
farg2 = t0
farg3 = c_loc(y0)
farg4 = sunctx
fresult = swigc_FLSRKStepCreateSSP(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FLSRKStepReInitSTS(arkode_mem, rhs, t0, y0) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
type(C_FUNPTR), intent(in), value :: rhs
real(C_DOUBLE), intent(in) :: t0
type(N_Vector), target, intent(inout) :: y0
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 
real(C_DOUBLE) :: farg3 
type(C_PTR) :: farg4 

farg1 = arkode_mem
farg2 = rhs
farg3 = t0
farg4 = c_loc(y0)
fresult = swigc_FLSRKStepReInitSTS(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FLSRKStepReInitSSP(arkode_mem, rhs, t0, y0) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
type(C_FUNPTR), intent(in), value :: rhs
real(C_DOUBLE), intent(in) :: t0
type(N_Vector), target, intent(inout) :: y0
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 
real(C_DOUBLE) :: farg3 
type(C_PTR) :: farg4 

farg1 = arkode_mem
farg2 = rhs
farg3 = t0
farg4 = c_loc(y0)
fresult = swigc_FLSRKStepReInitSSP(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FLSRKStepSetMethod(arkode_mem, method) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(ARKODE_LSRKMethodType), intent(in) :: method
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = arkode_mem
farg2 = method
fresult = swigc_FLSRKStepSetMethod(farg1, farg2)
swig_result = fresult
end function


subroutine SWIG_string_to_chararray(string, chars, wrap)
  use, intrinsic :: ISO_C_BINDING
  character(kind=C_CHAR, len=*), intent(IN) :: string
  character(kind=C_CHAR), dimension(:), target, allocatable, intent(OUT) :: chars
  type(SwigArrayWrapper), intent(OUT) :: wrap
  integer :: i

  allocate(character(kind=C_CHAR) :: chars(len(string) + 1))
  do i=1,len(string)
    chars(i) = string(i:i)
  end do
  i = len(string) + 1
  chars(i) = C_NULL_CHAR ! C string compatibility
  wrap%data = c_loc(chars)
  wrap%size = len(string)
end subroutine

function FLSRKStepSetMethodByName(arkode_mem, emethod) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
character(kind=C_CHAR, len=*), target :: emethod
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(SwigArrayWrapper) :: farg2 

farg1 = arkode_mem
call SWIG_string_to_chararray(emethod, farg2_chars, farg2)
fresult = swigc_FLSRKStepSetMethodByName(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepSetDomEigFn(arkode_mem, dom_eig) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
type(C_FUNPTR), intent(in), value :: dom_eig
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 

farg1 = arkode_mem
farg2 = dom_eig
fresult = swigc_FLSRKStepSetDomEigFn(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepSetDomEigFrequency(arkode_mem, nsteps) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT), intent(in) :: nsteps
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = arkode_mem
farg2 = nsteps
fresult = swigc_FLSRKStepSetDomEigFrequency(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepSetMaxNumStages(arkode_mem, stage_max_limit) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT), intent(in) :: stage_max_limit
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = arkode_mem
farg2 = stage_max_limit
fresult = swigc_FLSRKStepSetMaxNumStages(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepSetDomEigSafetyFactor(arkode_mem, dom_eig_sfty) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
real(C_DOUBLE), intent(in) :: dom_eig_sfty
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 

farg1 = arkode_mem
farg2 = dom_eig_sfty
fresult = swigc_FLSRKStepSetDomEigSafetyFactor(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepSetSSPStageNum(arkode_mem, num_of_stages) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT), intent(in) :: num_of_stages
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = arkode_mem
farg2 = num_of_stages
fresult = swigc_FLSRKStepSetSSPStageNum(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepGetNumRhsEvals(arkode_mem, fe_evals, fi_evals) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_LONG), dimension(*), target, intent(inout) :: fe_evals
integer(C_LONG), dimension(*), target, intent(inout) :: fi_evals
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = arkode_mem
farg2 = c_loc(fe_evals(1))
farg3 = c_loc(fi_evals(1))
fresult = swigc_FLSRKStepGetNumRhsEvals(farg1, farg2, farg3)
swig_result = fresult
end function

function FLSRKStepGetNumDomEigUpdates(arkode_mem, num_dom_eig_updates) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_LONG), dimension(*), target, intent(inout) :: num_dom_eig_updates
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = arkode_mem
farg2 = c_loc(num_dom_eig_updates(1))
fresult = swigc_FLSRKStepGetNumDomEigUpdates(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepGetMaxNumStages(arkode_mem, stage_max) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
integer(C_INT), dimension(*), target, intent(inout) :: stage_max
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = arkode_mem
farg2 = c_loc(stage_max(1))
fresult = swigc_FLSRKStepGetMaxNumStages(farg1, farg2)
swig_result = fresult
end function

function FLSRKStepGetAverageStageNum(arkode_mem, avg_stage) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: arkode_mem
real(C_DOUBLE), dimension(*), target, intent(inout) :: avg_stage
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = arkode_mem
farg2 = c_loc(avg_stage(1))
fresult = swigc_FLSRKStepGetAverageStageNum(farg1, farg2)
swig_result = fresult
end function


end module
