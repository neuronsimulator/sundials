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

%module fsunnonlinsol_newton_mod

// include code common to all implementations
%include "fsunnonlinsol.i"

%sunnonlinsol_impl(Newton)

// Process and wrap functions in the following files
%include "sunnonlinsol/sunnonlinsol_newton.h"

