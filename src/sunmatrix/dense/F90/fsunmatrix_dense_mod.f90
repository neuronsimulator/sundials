! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.
module fsunmatrix_dense_mod
 use, intrinsic :: ISO_C_BINDING
 use fsunmatrix_mod
 use fsundials_types
 implicit none
 private

 ! PUBLIC METHODS AND TYPES

  public :: FSUNMatGetData_Dense
  
 public :: FSUNDenseMatrix
 public :: FSUNDenseMatrix_Print
 public :: FSUNDenseMatrix_Rows
 public :: FSUNDenseMatrix_Columns
 public :: FSUNDenseMatrix_LData
 public :: FSUNDenseMatrix_Data
 public :: FSUNDenseMatrix_Cols
 public :: FSUNDenseMatrix_Column
 public :: FSUNMatGetID_Dense
 public :: FSUNMatClone_Dense
 public :: FSUNMatDestroy_Dense
 public :: FSUNMatZero_Dense
 public :: FSUNMatCopy_Dense
 public :: FSUNMatScaleAdd_Dense
 public :: FSUNMatScaleAddI_Dense
 public :: FSUNMatMatvec_Dense
 public :: FSUNMatSpace_Dense

 ! WRAPPER DECLARATIONS
 interface
function FSUNDenseMatrix(m, n) &
bind(C, name="SUNDenseMatrix") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T), value :: m
integer(C_INT64_T), value :: n
type(C_PTR) :: fresult
end function

subroutine FSUNDenseMatrix_Print(a, outfile) &
bind(C, name="SUNDenseMatrix_Print")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
type(C_PTR), value :: outfile
end subroutine

function FSUNDenseMatrix_Rows(a) &
bind(C, name="SUNDenseMatrix_Rows") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_INT64_T) :: fresult
end function

function FSUNDenseMatrix_Columns(a) &
bind(C, name="SUNDenseMatrix_Columns") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_INT64_T) :: fresult
end function

function FSUNDenseMatrix_LData(a) &
bind(C, name="SUNDenseMatrix_LData") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_INT64_T) :: fresult
end function

function FSUNDenseMatrix_Data(a) &
bind(C, name="SUNDenseMatrix_Data") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
type(C_PTR) :: fresult
end function

function FSUNDenseMatrix_Cols(a) &
bind(C, name="SUNDenseMatrix_Cols") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
type(C_PTR) :: fresult
end function

function FSUNDenseMatrix_Column(a, j) &
bind(C, name="SUNDenseMatrix_Column") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_INT64_T), value :: j
type(C_PTR) :: fresult
end function

function FSUNMatGetID_Dense(a) &
bind(C, name="SUNMatGetID_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_INT) :: fresult
end function

function FSUNMatClone_Dense(a) &
bind(C, name="SUNMatClone_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
type(C_PTR) :: fresult
end function

subroutine FSUNMatDestroy_Dense(a) &
bind(C, name="SUNMatDestroy_Dense")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
end subroutine

function FSUNMatZero_Dense(a) &
bind(C, name="SUNMatZero_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_INT) :: fresult
end function

function FSUNMatCopy_Dense(a, b) &
bind(C, name="SUNMatCopy_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
type(C_PTR), value :: b
integer(C_INT) :: fresult
end function

function FSUNMatScaleAdd_Dense(c, a, b) &
bind(C, name="SUNMatScaleAdd_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), value :: c
type(C_PTR), value :: a
type(C_PTR), value :: b
integer(C_INT) :: fresult
end function

function FSUNMatScaleAddI_Dense(c, a) &
bind(C, name="SUNMatScaleAddI_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE), value :: c
type(C_PTR), value :: a
integer(C_INT) :: fresult
end function

function FSUNMatMatvec_Dense(a, x, y) &
bind(C, name="SUNMatMatvec_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
type(C_PTR), value :: x
type(C_PTR), value :: y
integer(C_INT) :: fresult
end function

function FSUNMatSpace_Dense(a, lenrw, leniw) &
bind(C, name="SUNMatSpace_Dense") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: a
integer(C_LONG) :: lenrw
integer(C_LONG) :: leniw
integer(C_INT) :: fresult
end function

 end interface


contains
 ! FORTRAN PROXY CODE

  subroutine FSUNMatGetData_Dense(mat, mdata)

      use, intrinsic :: iso_c_binding
      implicit none

      type(C_PTR)        :: mat
      integer(C_INT64_T) :: M, N
      type(C_PTR)        :: cptr
      real(C_DOUBLE), dimension(:,:), pointer :: mdata

      M = FSUNDenseMatrix_Rows(mat)
      N = FSUNDenseMatrix_Columns(mat)
      cptr = FSUNDenseMatrix_Data(mat)

      call c_f_pointer(cptr, mdata, (/M,N/))

  end subroutine FSUNMatGetData_Dense
  

end module
