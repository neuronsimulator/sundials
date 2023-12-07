! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.

! ---------------------------------------------------------------
! Programmer(s): Auto-generated by swig.
! ---------------------------------------------------------------
! SUNDIALS Copyright Start
! Copyright (c) 2002-2023, Lawrence Livermore National Security
! and Southern Methodist University.
! All rights reserved.
!
! See the top-level LICENSE and NOTICE files for details.
!
! SPDX-License-Identifier: BSD-3-Clause
! SUNDIALS Copyright End
! ---------------------------------------------------------------

module fsundials_nonlinearsolver_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_context_mod
 use fsundials_types_mod
 use fsundials_types_mod
 use fsundials_types_mod
 use fsundials_nvector_mod
 use fsundials_context_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 ! typedef enum SUNNonlinearSolver_Type
 enum, bind(c)
  enumerator :: SUNNONLINEARSOLVER_ROOTFIND
  enumerator :: SUNNONLINEARSOLVER_FIXEDPOINT
 end enum
 integer, parameter, public :: SUNNonlinearSolver_Type = kind(SUNNONLINEARSOLVER_ROOTFIND)
 public :: SUNNONLINEARSOLVER_ROOTFIND, SUNNONLINEARSOLVER_FIXEDPOINT
 ! struct struct _generic_SUNNonlinearSolver_Ops
 type, bind(C), public :: SUNNonlinearSolver_Ops
  type(C_FUNPTR), public :: gettype
  type(C_FUNPTR), public :: initialize
  type(C_FUNPTR), public :: setup
  type(C_FUNPTR), public :: solve
  type(C_FUNPTR), public :: free
  type(C_FUNPTR), public :: setsysfn
  type(C_FUNPTR), public :: setlsetupfn
  type(C_FUNPTR), public :: setlsolvefn
  type(C_FUNPTR), public :: setctestfn
  type(C_FUNPTR), public :: setmaxiters
  type(C_FUNPTR), public :: getnumiters
  type(C_FUNPTR), public :: getcuriter
  type(C_FUNPTR), public :: getnumconvfails
 end type SUNNonlinearSolver_Ops
 ! struct struct _generic_SUNNonlinearSolver
 type, bind(C), public :: SUNNonlinearSolver
  type(C_PTR), public :: content
  type(C_PTR), public :: ops
  type(C_PTR), public :: sunctx
 end type SUNNonlinearSolver
 public :: FSUNNonlinSolNewEmpty
 public :: FSUNNonlinSolFreeEmpty
 public :: FSUNNonlinSolGetType
 public :: FSUNNonlinSolInitialize
 public :: FSUNNonlinSolSetup
 public :: FSUNNonlinSolSolve
 public :: FSUNNonlinSolFree
 public :: FSUNNonlinSolSetSysFn
 public :: FSUNNonlinSolSetLSetupFn
 public :: FSUNNonlinSolSetLSolveFn
 public :: FSUNNonlinSolSetConvTestFn
 public :: FSUNNonlinSolSetMaxIters
 public :: FSUNNonlinSolGetNumIters
 public :: FSUNNonlinSolGetCurIter
 public :: FSUNNonlinSolGetNumConvFails
 integer(C_INT), parameter, public :: SUN_NLS_SUCCESS = 0_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_CONTINUE = +901_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_CONV_RECVR = +902_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_MEM_NULL = -901_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_MEM_FAIL = -902_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_ILL_INPUT = -903_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_VECTOROP_ERR = -904_C_INT
 integer(C_INT), parameter, public :: SUN_NLS_EXT_FAIL = -905_C_INT

! WRAPPER DECLARATIONS
interface
function swigc_FSUNNonlinSolNewEmpty(farg1) &
bind(C, name="_wrap_FSUNNonlinSolNewEmpty") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_FSUNNonlinSolFreeEmpty(farg1) &
bind(C, name="_wrap_FSUNNonlinSolFreeEmpty")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
end subroutine

function swigc_FSUNNonlinSolGetType(farg1) &
bind(C, name="_wrap_FSUNNonlinSolGetType") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolInitialize(farg1) &
bind(C, name="_wrap_FSUNNonlinSolInitialize") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSetup(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNNonlinSolSetup") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSolve(farg1, farg2, farg3, farg4, farg5, farg6, farg7) &
bind(C, name="_wrap_FSUNNonlinSolSolve") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT), intent(in) :: farg6
type(C_PTR), value :: farg7
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolFree(farg1) &
bind(C, name="_wrap_FSUNNonlinSolFree") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSetSysFn(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolSetSysFn") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSetLSetupFn(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolSetLSetupFn") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSetLSolveFn(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolSetLSolveFn") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSetConvTestFn(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNNonlinSolSetConvTestFn") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolSetMaxIters(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolSetMaxIters") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolGetNumIters(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolGetNumIters") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolGetCurIter(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolGetCurIter") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNNonlinSolGetNumConvFails(farg1, farg2) &
bind(C, name="_wrap_FSUNNonlinSolGetNumConvFails") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNNonlinSolNewEmpty(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNNonlinearSolver), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNNonlinSolNewEmpty(farg1)
call c_f_pointer(fresult, swig_result)
end function

subroutine FSUNNonlinSolFreeEmpty(nls)
use, intrinsic :: ISO_C_BINDING
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(C_PTR) :: farg1 

farg1 = c_loc(nls)
call swigc_FSUNNonlinSolFreeEmpty(farg1)
end subroutine

function FSUNNonlinSolGetType(nls) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNNonlinearSolver_Type) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(nls)
fresult = swigc_FSUNNonlinSolGetType(farg1)
swig_result = fresult
end function

function FSUNNonlinSolInitialize(nls) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(nls)
fresult = swigc_FSUNNonlinSolInitialize(farg1)
swig_result = fresult
end function

function FSUNNonlinSolSetup(nls, y, mem) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(N_Vector), target, intent(inout) :: y
type(C_PTR) :: mem
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(nls)
farg2 = c_loc(y)
farg3 = mem
fresult = swigc_FSUNNonlinSolSetup(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNNonlinSolSolve(nls, y0, y, w, tol, calllsetup, mem) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(N_Vector), target, intent(inout) :: y0
type(N_Vector), target, intent(inout) :: y
type(N_Vector), target, intent(inout) :: w
real(C_DOUBLE), intent(in) :: tol
integer(C_INT), intent(in) :: calllsetup
type(C_PTR) :: mem
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 
real(C_DOUBLE) :: farg5 
integer(C_INT) :: farg6 
type(C_PTR) :: farg7 

farg1 = c_loc(nls)
farg2 = c_loc(y0)
farg3 = c_loc(y)
farg4 = c_loc(w)
farg5 = tol
farg6 = calllsetup
farg7 = mem
fresult = swigc_FSUNNonlinSolSolve(farg1, farg2, farg3, farg4, farg5, farg6, farg7)
swig_result = fresult
end function

function FSUNNonlinSolFree(nls) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(nls)
fresult = swigc_FSUNNonlinSolFree(farg1)
swig_result = fresult
end function

function FSUNNonlinSolSetSysFn(nls, sysfn) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(C_FUNPTR), intent(in), value :: sysfn
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 

farg1 = c_loc(nls)
farg2 = sysfn
fresult = swigc_FSUNNonlinSolSetSysFn(farg1, farg2)
swig_result = fresult
end function

function FSUNNonlinSolSetLSetupFn(nls, setupfn) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(C_FUNPTR), intent(in), value :: setupfn
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 

farg1 = c_loc(nls)
farg2 = setupfn
fresult = swigc_FSUNNonlinSolSetLSetupFn(farg1, farg2)
swig_result = fresult
end function

function FSUNNonlinSolSetLSolveFn(nls, solvefn) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(C_FUNPTR), intent(in), value :: solvefn
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 

farg1 = c_loc(nls)
farg2 = solvefn
fresult = swigc_FSUNNonlinSolSetLSolveFn(farg1, farg2)
swig_result = fresult
end function

function FSUNNonlinSolSetConvTestFn(nls, ctestfn, ctest_data) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
type(C_FUNPTR), intent(in), value :: ctestfn
type(C_PTR) :: ctest_data
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(nls)
farg2 = ctestfn
farg3 = ctest_data
fresult = swigc_FSUNNonlinSolSetConvTestFn(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNNonlinSolSetMaxIters(nls, maxiters) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_INT), intent(in) :: maxiters
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(nls)
farg2 = maxiters
fresult = swigc_FSUNNonlinSolSetMaxIters(farg1, farg2)
swig_result = fresult
end function

function FSUNNonlinSolGetNumIters(nls, niters) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_LONG), dimension(*), target, intent(inout) :: niters
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(nls)
farg2 = c_loc(niters(1))
fresult = swigc_FSUNNonlinSolGetNumIters(farg1, farg2)
swig_result = fresult
end function

function FSUNNonlinSolGetCurIter(nls, iter) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_INT), dimension(*), target, intent(inout) :: iter
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(nls)
farg2 = c_loc(iter(1))
fresult = swigc_FSUNNonlinSolGetCurIter(farg1, farg2)
swig_result = fresult
end function

function FSUNNonlinSolGetNumConvFails(nls, nconvfails) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNNonlinearSolver), target, intent(inout) :: nls
integer(C_LONG), dimension(*), target, intent(inout) :: nconvfails
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(nls)
farg2 = c_loc(nconvfails(1))
fresult = swigc_FSUNNonlinSolGetNumConvFails(farg1, farg2)
swig_result = fresult
end function


end module
