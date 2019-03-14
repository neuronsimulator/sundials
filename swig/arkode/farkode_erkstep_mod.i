// ---------------------------------------------------------------
// Programmer: Cody J. Balos @ LLNL
// ---------------------------------------------------------------
// SUNDIALS Copyright Start
// Copyright (c) 2002-2019, Lawrence Livermore National Security
// and Southern Methodist University.
// All rights reserved.
//
// See the top-level LICENSE and NOTICE files for details.
//
// SPDX-License-Identifier: BSD-3-Clause
// SUNDIALS Copyright End
// ---------------------------------------------------------------
// Swig interface file
// ---------------------------------------------------------------

%module farkode_erkstep_mod

%include "../sundials/fsundials.i"

// Load the typedefs and generate a "use" statements in the module
%import "farkode_mod.i"

// adapt_params is a nullable array
%typemap(bindc, in="type(C_PTR)") realtype* adapt_params "type(C_PTR)"

// Process definitions from these files
%include "arkode/arkode_erkstep.h"
