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
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
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


#include "arkode/arkode_erkstep.h"


#include <stdlib.h>
#ifdef _MSC_VER
# ifndef strtoull
#  define strtoull _strtoui64
# endif
# ifndef strtoll
#  define strtoll _strtoi64
# endif
#endif


typedef struct {
    void* data;
    size_t size;
} SwigArrayWrapper;


SWIGINTERN SwigArrayWrapper SwigArrayWrapper_uninitialized() {
  SwigArrayWrapper result;
  result.data = NULL;
  result.size = 0;
  return result;
}


#include <string.h>

SWIGEXPORT void * _wrap_FERKStepCreate(ARKRhsFn farg1, double const *farg2, N_Vector farg3, void *farg4) {
  void * fresult ;
  ARKRhsFn arg1 = (ARKRhsFn) 0 ;
  realtype arg2 ;
  N_Vector arg3 = (N_Vector) 0 ;
  SUNContext arg4 = (SUNContext) 0 ;
  void *result = 0 ;
  
  arg1 = (ARKRhsFn)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (SUNContext)(farg4);
  result = (void *)ERKStepCreate(arg1,arg2,arg3,arg4);
  fresult = result;
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepResize(void *farg1, N_Vector farg2, double const *farg3, double const *farg4, ARKVecResizeFn farg5, void *farg6) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  N_Vector arg2 = (N_Vector) 0 ;
  realtype arg3 ;
  realtype arg4 ;
  ARKVecResizeFn arg5 = (ARKVecResizeFn) 0 ;
  void *arg6 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (N_Vector)(farg2);
  arg3 = (realtype)(*farg3);
  arg4 = (realtype)(*farg4);
  arg5 = (ARKVecResizeFn)(farg5);
  arg6 = (void *)(farg6);
  result = (int)ERKStepResize(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepReInit(void *farg1, ARKRhsFn farg2, double const *farg3, N_Vector farg4) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKRhsFn arg2 = (ARKRhsFn) 0 ;
  realtype arg3 ;
  N_Vector arg4 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKRhsFn)(farg2);
  arg3 = (realtype)(*farg3);
  arg4 = (N_Vector)(farg4);
  result = (int)ERKStepReInit(arg1,arg2,arg3,arg4);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepReset(void *farg1, double const *farg2, N_Vector farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (N_Vector)(farg3);
  result = (int)ERKStepReset(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSStolerances(void *farg1, double const *farg2, double const *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  realtype arg3 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (realtype)(*farg3);
  result = (int)ERKStepSStolerances(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSVtolerances(void *farg1, double const *farg2, N_Vector farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (N_Vector)(farg3);
  result = (int)ERKStepSVtolerances(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepWFtolerances(void *farg1, ARKEwtFn farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKEwtFn arg2 = (ARKEwtFn) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKEwtFn)(farg2);
  result = (int)ERKStepWFtolerances(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepRootInit(void *farg1, int const *farg2, ARKRootFn farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  ARKRootFn arg3 = (ARKRootFn) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  arg3 = (ARKRootFn)(farg3);
  result = (int)ERKStepRootInit(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetDefaults(void *farg1) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  result = (int)ERKStepSetDefaults(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetOrder(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetOrder(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetInterpolantType(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetInterpolantType(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetInterpolantDegree(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetInterpolantDegree(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetDenseOrder(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetDenseOrder(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetTable(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKodeButcherTable arg2 = (ARKodeButcherTable) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKodeButcherTable)(farg2);
  result = (int)ERKStepSetTable(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetTableNum(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKODE_ERKTableID arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKODE_ERKTableID)(*farg2);
  result = (int)ERKStepSetTableNum(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetTableName(void *farg1, SwigArrayWrapper *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  char *arg2 = (char *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (char *)(farg2->data);
  result = (int)ERKStepSetTableName(arg1,(char const *)arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetCFLFraction(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetCFLFraction(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetSafetyFactor(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetSafetyFactor(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetErrorBias(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetErrorBias(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxGrowth(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetMaxGrowth(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMinReduction(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetMinReduction(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetFixedStepBounds(void *farg1, double const *farg2, double const *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  realtype arg3 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (realtype)(*farg3);
  result = (int)ERKStepSetFixedStepBounds(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetAdaptivityMethod(void *farg1, int const *farg2, int const *farg3, int const *farg4, double *farg5) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int arg3 ;
  int arg4 ;
  realtype *arg5 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  arg3 = (int)(*farg3);
  arg4 = (int)(*farg4);
  arg5 = (double *)(farg5);
  result = (int)ERKStepSetAdaptivityMethod(arg1,arg2,arg3,arg4,arg5);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetAdaptivityFn(void *farg1, ARKAdaptFn farg2, void *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKAdaptFn arg2 = (ARKAdaptFn) 0 ;
  void *arg3 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKAdaptFn)(farg2);
  arg3 = (void *)(farg3);
  result = (int)ERKStepSetAdaptivityFn(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxFirstGrowth(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetMaxFirstGrowth(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxEFailGrowth(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetMaxEFailGrowth(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetSmallNumEFails(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetSmallNumEFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetStabilityFn(void *farg1, ARKExpStabFn farg2, void *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKExpStabFn arg2 = (ARKExpStabFn) 0 ;
  void *arg3 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKExpStabFn)(farg2);
  arg3 = (void *)(farg3);
  result = (int)ERKStepSetStabilityFn(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxErrTestFails(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetMaxErrTestFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetConstraints(void *farg1, N_Vector farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  N_Vector arg2 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (N_Vector)(farg2);
  result = (int)ERKStepSetConstraints(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxNumSteps(void *farg1, long const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long)(*farg2);
  result = (int)ERKStepSetMaxNumSteps(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxHnilWarns(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetMaxHnilWarns(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetInitStep(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetInitStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMinStep(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetMinStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxStep(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetMaxStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetInterpolateStopTime(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetInterpolateStopTime(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetStopTime(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetStopTime(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepClearStopTime(void *farg1) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  result = (int)ERKStepClearStopTime(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetFixedStep(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  result = (int)ERKStepSetFixedStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetMaxNumConstrFails(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetMaxNumConstrFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRootDirection(void *farg1, int *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int *arg2 = (int *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int *)(farg2);
  result = (int)ERKStepSetRootDirection(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetNoInactiveRootWarn(void *farg1) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  result = (int)ERKStepSetNoInactiveRootWarn(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetErrHandlerFn(void *farg1, ARKErrHandlerFn farg2, void *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKErrHandlerFn arg2 = (ARKErrHandlerFn) 0 ;
  void *arg3 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKErrHandlerFn)(farg2);
  arg3 = (void *)(farg3);
  result = (int)ERKStepSetErrHandlerFn(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetErrFile(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (FILE *)(farg2);
  result = (int)ERKStepSetErrFile(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetUserData(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  void *arg2 = (void *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (void *)(farg2);
  result = (int)ERKStepSetUserData(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetDiagnostics(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (FILE *)(farg2);
  result = (int)ERKStepSetDiagnostics(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetPostprocessStepFn(void *farg1, ARKPostProcessFn farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKPostProcessFn arg2 = (ARKPostProcessFn) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKPostProcessFn)(farg2);
  result = (int)ERKStepSetPostprocessStepFn(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetPostprocessStageFn(void *farg1, ARKPostProcessFn farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKPostProcessFn arg2 = (ARKPostProcessFn) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKPostProcessFn)(farg2);
  result = (int)ERKStepSetPostprocessStageFn(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepEvolve(void *farg1, double const *farg2, N_Vector farg3, double *farg4, int const *farg5) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  N_Vector arg3 = (N_Vector) 0 ;
  realtype *arg4 = (realtype *) 0 ;
  int arg5 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (realtype *)(farg4);
  arg5 = (int)(*farg5);
  result = (int)ERKStepEvolve(arg1,arg2,arg3,arg4,arg5);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetDky(void *farg1, double const *farg2, int const *farg3, N_Vector farg4) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype arg2 ;
  int arg3 ;
  N_Vector arg4 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype)(*farg2);
  arg3 = (int)(*farg3);
  arg4 = (N_Vector)(farg4);
  result = (int)ERKStepGetDky(arg1,arg2,arg3,arg4);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumExpSteps(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumExpSteps(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumAccSteps(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumAccSteps(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumStepAttempts(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumStepAttempts(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRhsEvals(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRhsEvals(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumErrTestFails(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumErrTestFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetCurrentButcherTable(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKodeButcherTable *arg2 = (ARKodeButcherTable *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKodeButcherTable *)(farg2);
  result = (int)ERKStepGetCurrentButcherTable(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetEstLocalErrors(void *farg1, N_Vector farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  N_Vector arg2 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (N_Vector)(farg2);
  result = (int)ERKStepGetEstLocalErrors(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetWorkSpace(void *farg1, long *farg2, long *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  long *arg3 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  arg3 = (long *)(farg3);
  result = (int)ERKStepGetWorkSpace(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumSteps(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumSteps(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetActualInitStep(void *farg1, double *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype *arg2 = (realtype *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype *)(farg2);
  result = (int)ERKStepGetActualInitStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetLastStep(void *farg1, double *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype *arg2 = (realtype *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype *)(farg2);
  result = (int)ERKStepGetLastStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetCurrentStep(void *farg1, double *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype *arg2 = (realtype *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype *)(farg2);
  result = (int)ERKStepGetCurrentStep(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetCurrentTime(void *farg1, double *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype *arg2 = (realtype *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype *)(farg2);
  result = (int)ERKStepGetCurrentTime(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetTolScaleFactor(void *farg1, double *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  realtype *arg2 = (realtype *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (realtype *)(farg2);
  result = (int)ERKStepGetTolScaleFactor(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetErrWeights(void *farg1, N_Vector farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  N_Vector arg2 = (N_Vector) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (N_Vector)(farg2);
  result = (int)ERKStepGetErrWeights(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumGEvals(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumGEvals(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetRootInfo(void *farg1, int *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int *arg2 = (int *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int *)(farg2);
  result = (int)ERKStepGetRootInfo(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumConstrFails(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumConstrFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetUserData(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  void **arg2 = (void **) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (void **)(farg2);
  result = (int)ERKStepGetUserData(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepPrintAllStats(void *farg1, void *farg2, int const *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  SUNOutputFormat arg3 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (FILE *)(farg2);
  arg3 = (SUNOutputFormat)(*farg3);
  result = (int)ERKStepPrintAllStats(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT SwigArrayWrapper _wrap_FERKStepGetReturnFlagName(long const *farg1) {
  SwigArrayWrapper fresult ;
  long arg1 ;
  char *result = 0 ;
  
  arg1 = (long)(*farg1);
  result = (char *)ERKStepGetReturnFlagName(arg1);
  fresult.size = strlen((const char*)(result));
  fresult.data = (char *)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepWriteParameters(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (FILE *)(farg2);
  result = (int)ERKStepWriteParameters(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepWriteButcher(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (FILE *)(farg2);
  result = (int)ERKStepWriteButcher(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetTimestepperStats(void *farg1, long *farg2, long *farg3, long *farg4, long *farg5, long *farg6) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  long *arg3 = (long *) 0 ;
  long *arg4 = (long *) 0 ;
  long *arg5 = (long *) 0 ;
  long *arg6 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  arg3 = (long *)(farg3);
  arg4 = (long *)(farg4);
  arg5 = (long *)(farg5);
  arg6 = (long *)(farg6);
  result = (int)ERKStepGetTimestepperStats(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetStepStats(void *farg1, long *farg2, double *farg3, double *farg4, double *farg5, double *farg6) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  realtype *arg3 = (realtype *) 0 ;
  realtype *arg4 = (realtype *) 0 ;
  realtype *arg5 = (realtype *) 0 ;
  realtype *arg6 = (realtype *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  arg3 = (realtype *)(farg3);
  arg4 = (realtype *)(farg4);
  arg5 = (realtype *)(farg5);
  arg6 = (realtype *)(farg6);
  result = (int)ERKStepGetStepStats(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT void _wrap_FERKStepFree(void *farg1) {
  void **arg1 = (void **) 0 ;
  
  arg1 = (void **)(farg1);
  ERKStepFree(arg1);
}


SWIGEXPORT void _wrap_FERKStepPrintMem(void *farg1, void *farg2) {
  void *arg1 = (void *) 0 ;
  FILE *arg2 = (FILE *) 0 ;
  
  arg1 = (void *)(farg1);
  arg2 = (FILE *)(farg2);
  ERKStepPrintMem(arg1,arg2);
}


SWIGEXPORT int _wrap_FERKStepSetRelaxFn(void *farg1, ARKRelaxFn farg2, ARKRelaxJacFn farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKRelaxFn arg2 = (ARKRelaxFn) 0 ;
  ARKRelaxJacFn arg3 = (ARKRelaxJacFn) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKRelaxFn)(farg2);
  arg3 = (ARKRelaxJacFn)(farg3);
  result = (int)ERKStepSetRelaxFn(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxEtaFail(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  sunrealtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (sunrealtype)(*farg2);
  result = (int)ERKStepSetRelaxEtaFail(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxLowerBound(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  sunrealtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (sunrealtype)(*farg2);
  result = (int)ERKStepSetRelaxLowerBound(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxMaxFails(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetRelaxMaxFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxMaxIters(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (int)(*farg2);
  result = (int)ERKStepSetRelaxMaxIters(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxSolver(void *farg1, int const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  ARKRelaxSolver arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (ARKRelaxSolver)(*farg2);
  result = (int)ERKStepSetRelaxSolver(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxResTol(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  sunrealtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (sunrealtype)(*farg2);
  result = (int)ERKStepSetRelaxResTol(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxTol(void *farg1, double const *farg2, double const *farg3) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  sunrealtype arg2 ;
  sunrealtype arg3 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (sunrealtype)(*farg2);
  arg3 = (sunrealtype)(*farg3);
  result = (int)ERKStepSetRelaxTol(arg1,arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepSetRelaxUpperBound(void *farg1, double const *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  sunrealtype arg2 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (sunrealtype)(*farg2);
  result = (int)ERKStepSetRelaxUpperBound(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRelaxFnEvals(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRelaxFnEvals(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRelaxJacEvals(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRelaxJacEvals(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRelaxFails(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRelaxFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRelaxBoundFails(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRelaxBoundFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRelaxSolveFails(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRelaxSolveFails(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FERKStepGetNumRelaxSolveIters(void *farg1, long *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  long *arg2 = (long *) 0 ;
  int result;
  
  arg1 = (void *)(farg1);
  arg2 = (long *)(farg2);
  result = (int)ERKStepGetNumRelaxSolveIters(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}



