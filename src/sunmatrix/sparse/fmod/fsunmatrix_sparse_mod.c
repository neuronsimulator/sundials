/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

/* ---------------------------------------------------------------
 * Programmer(s): Auto-generated by swig.
 * ---------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2022, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -------------------------------------------------------------*/

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* qualifier for exported *const* global data variables*/
#ifndef SWIGEXTERN
# ifdef __cplusplus
#   define SWIGEXTERN extern
# else
#   define SWIGEXTERN
# endif
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif

/*  Errors in SWIG */
#define  SWIG_UnknownError    	   -1
#define  SWIG_IOError        	   -2
#define  SWIG_RuntimeError   	   -3
#define  SWIG_IndexError     	   -4
#define  SWIG_TypeError      	   -5
#define  SWIG_DivisionByZero 	   -6
#define  SWIG_OverflowError  	   -7
#define  SWIG_SyntaxError    	   -8
#define  SWIG_ValueError     	   -9
#define  SWIG_SystemError    	   -10
#define  SWIG_AttributeError 	   -11
#define  SWIG_MemoryError    	   -12
#define  SWIG_NullReferenceError   -13




#include <assert.h>
#define SWIG_exception_impl(DECL, CODE, MSG, RETURNNULL) \
 { printf("In " DECL ": " MSG); assert(0); RETURNNULL; }


#include <stdio.h>
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(_WATCOM)
# ifndef snprintf
#  define snprintf _snprintf
# endif
#endif


/* Support for the `contract` feature.
 *
 * Note that RETURNNULL is first because it's inserted via a 'Replaceall' in
 * the fortran.cxx file.
 */
#define SWIG_contract_assert(RETURNNULL, EXPR, MSG) \
 if (!(EXPR)) { SWIG_exception_impl("$decl", SWIG_ValueError, MSG, RETURNNULL); } 


#define SWIGVERSION 0x040000 
#define SWIG_VERSION SWIGVERSION


#define SWIG_as_voidptr(a) (void *)((const void *)(a)) 
#define SWIG_as_voidptrptr(a) ((void)SWIG_as_voidptr(*a),(void**)(a)) 


#include "sundials/sundials_matrix.h"


#include "sunmatrix/sunmatrix_sparse.h"

SWIGEXPORT SUNMatrix _wrap_FSUNSparseMatrix(int64_t const *farg1, int64_t const *farg2, int64_t const *farg3, int const *farg4, void *farg5) {
  SUNMatrix fresult ;
  sunindextype arg1 ;
  sunindextype arg2 ;
  sunindextype arg3 ;
  int arg4 ;
  SUNContext arg5 = (SUNContext) 0 ;
  SUNMatrix result;
  
  arg1 = (sunindextype)(*farg1);
  arg2 = (sunindextype)(*farg2);
  arg3 = (sunindextype)(*farg3);
  arg4 = (int)(*farg4);
  arg5 = (SUNContext)(farg5);
  result = (SUNMatrix)SUNSparseMatrix(arg1,arg2,arg3,arg4,arg5);
  fresult = result;
  return fresult;
}


SWIGEXPORT SUNMatrix _wrap_FSUNSparseFromDenseMatrix(SUNMatrix farg1, double const *farg2, int const *farg3) {
  SUNMatrix fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  realtype arg2 ;
  int arg3 ;
  SUNMatrix result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (int)(*farg3);
  result = (SUNMatrix)SUNSparseFromDenseMatrix(arg1,arg2,arg3);
  fresult = result;
  return fresult;
}


SWIGEXPORT SUNMatrix _wrap_FSUNSparseFromBandMatrix(SUNMatrix farg1, double const *farg2, int const *farg3) {
  SUNMatrix fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  realtype arg2 ;
  int arg3 ;
  SUNMatrix result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (int)(*farg3);
  result = (SUNMatrix)SUNSparseFromBandMatrix(arg1,arg2,arg3);
  fresult = result;
  return fresult;
}


SWIGEXPORT int _wrap_FSUNSparseMatrix_ToCSR(SUNMatrix farg1, void *farg2) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) (SUNMatrix)0 ;
  SUNMatrix *arg2 = (SUNMatrix *) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (SUNMatrix *)(farg2);
  result = (int)SUNSparseMatrix_ToCSR(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNSparseMatrix_ToCSC(SUNMatrix farg1, void *farg2) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) (SUNMatrix)0 ;
  SUNMatrix *arg2 = (SUNMatrix *) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (SUNMatrix *)(farg2);
  result = (int)SUNSparseMatrix_ToCSC(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNSparseMatrix_Realloc(SUNMatrix farg1) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  result = (int)SUNSparseMatrix_Realloc(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNSparseMatrix_Reallocate(SUNMatrix farg1, int64_t const *farg2) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype arg2 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (sunindextype)(*farg2);
  result = (int)SUNSparseMatrix_Reallocate(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT void _wrap_FSUNSparseMatrix_Print(SUNMatrix farg1, void *farg2) {
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (FILE *)(farg2);
  SUNSparseMatrix_Print(arg1,arg2);
}


SWIGEXPORT int64_t _wrap_FSUNSparseMatrix_Rows(SUNMatrix farg1) {
  int64_t fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype result;
  
  arg1 = (SUNMatrix)(farg1);
  result = SUNSparseMatrix_Rows(arg1);
  fresult = (sunindextype)(result);
  return fresult;
}


SWIGEXPORT int64_t _wrap_FSUNSparseMatrix_Columns(SUNMatrix farg1) {
  int64_t fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype result;
  
  arg1 = (SUNMatrix)(farg1);
  result = SUNSparseMatrix_Columns(arg1);
  fresult = (sunindextype)(result);
  return fresult;
}


SWIGEXPORT int64_t _wrap_FSUNSparseMatrix_NNZ(SUNMatrix farg1) {
  int64_t fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype result;
  
  arg1 = (SUNMatrix)(farg1);
  result = SUNSparseMatrix_NNZ(arg1);
  fresult = (sunindextype)(result);
  return fresult;
}


SWIGEXPORT int64_t _wrap_FSUNSparseMatrix_NP(SUNMatrix farg1) {
  int64_t fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype result;
  
  arg1 = (SUNMatrix)(farg1);
  result = SUNSparseMatrix_NP(arg1);
  fresult = (sunindextype)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNSparseMatrix_SparseType(SUNMatrix farg1) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  result = (int)SUNSparseMatrix_SparseType(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT double * _wrap_FSUNSparseMatrix_Data(SUNMatrix farg1) {
  double * fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  realtype *result = 0 ;
  
  arg1 = (SUNMatrix)(farg1);
  result = (realtype *)SUNSparseMatrix_Data(arg1);
  fresult = result;
  return fresult;
}


SWIGEXPORT int64_t * _wrap_FSUNSparseMatrix_IndexValues(SUNMatrix farg1) {
  int64_t * fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype *result = 0 ;
  
  arg1 = (SUNMatrix)(farg1);
  result = (sunindextype *)SUNSparseMatrix_IndexValues(arg1);
  fresult = result;
  return fresult;
}


SWIGEXPORT int64_t * _wrap_FSUNSparseMatrix_IndexPointers(SUNMatrix farg1) {
  int64_t * fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  sunindextype *result = 0 ;
  
  arg1 = (SUNMatrix)(farg1);
  result = (sunindextype *)SUNSparseMatrix_IndexPointers(arg1);
  fresult = result;
  return fresult;
}


SWIGEXPORT int _wrap_FSUNMatGetID_Sparse(SUNMatrix farg1) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  SUNMatrix_ID result;
  
  arg1 = (SUNMatrix)(farg1);
  result = (SUNMatrix_ID)SUNMatGetID_Sparse(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT SUNMatrix _wrap_FSUNMatClone_Sparse(SUNMatrix farg1) {
  SUNMatrix fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  SUNMatrix result;
  
  arg1 = (SUNMatrix)(farg1);
  result = (SUNMatrix)SUNMatClone_Sparse(arg1);
  fresult = result;
  return fresult;
}


SWIGEXPORT void _wrap_FSUNMatDestroy_Sparse(SUNMatrix farg1) {
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  
  arg1 = (SUNMatrix)(farg1);
  SUNMatDestroy_Sparse(arg1);
}


SWIGEXPORT int _wrap_FSUNMatZero_Sparse(SUNMatrix farg1) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  result = (int)SUNMatZero_Sparse(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNMatCopy_Sparse(SUNMatrix farg1, SUNMatrix farg2) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  SUNMatrix arg2 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (SUNMatrix)(farg2);
  result = (int)SUNMatCopy_Sparse(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNMatScaleAdd_Sparse(double const *farg1, SUNMatrix farg2, SUNMatrix farg3) {
  int fresult ;
  realtype arg1 ;
  SUNMatrix arg2 = (SUNMatrix) 0 ;
  SUNMatrix arg3 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (realtype)(*farg1);
  arg2 = (SUNMatrix)(farg2);
  arg3 = (SUNMatrix)(farg3);
  result = (int)SUNMatScaleAdd_Sparse(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNMatScaleAddI_Sparse(double const *farg1, SUNMatrix farg2) {
  int fresult ;
  realtype arg1 ;
  SUNMatrix arg2 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (realtype)(*farg1);
  arg2 = (SUNMatrix)(farg2);
  result = (int)SUNMatScaleAddI_Sparse(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNMatMatvec_Sparse(SUNMatrix farg1, N_Vector farg2, N_Vector farg3) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  N_Vector arg2 = (N_Vector) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (N_Vector)(farg2);
  arg3 = (N_Vector)(farg3);
  result = (int)SUNMatMatvec_Sparse(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNMatSpace_Sparse(SUNMatrix farg1, long *farg2, long *farg3) {
  int fresult ;
  SUNMatrix arg1 = (SUNMatrix) 0 ;
  long *arg2 = (long *) 0 ;
  long *arg3 = (long *) 0 ;
  int result;
  
  arg1 = (SUNMatrix)(farg1);
  arg2 = (long *)(farg2);
  arg3 = (long *)(farg3);
  result = (int)SUNMatSpace_Sparse(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}



