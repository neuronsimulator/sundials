// ---------------------------------------------------------------
// SUNDIALS Copyright Start
// Copyright (c) 2002-2024, Lawrence Livermore National Security
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

%module fsunadjointstepper_mod

// Include shared configuration
%include "../sundials/fsundials.i"

%include <stdint.i>

%{
#include "sunadjoint/sunadjoint_stepper.h"
%}

%import "../sundials/fsundials_core_mod.i"
%import "../sunadjoint/fsunadjointcheckpointscheme_mod.i"

%fortran_struct(SUNAdjointStepper_);
%typemap(ctype) SUNAdjointStepper_* "SUNAdjointStepper";
%rename(SUNAdjointStepper) SUNAdjointStepper_;

// Process and wrap functions in the following files
%include  "sunadjoint/sunadjoint_stepper.h"
