//===-- Passes.td - GPU pass definition file ---------------*- tablegen -*-===//
// Copyright 2023 Enflame Revolutionary Academy
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef Expt_PASSES
#define Expt_PASSES

include "mlir/Pass/PassBase.td"

// --------------------------------------------------------------------------
// Dummy Passes
// --------------------------------------------------------------------------


def ExptDummyPass : Pass<"Expt-dummy-pass", "mlir::func::FuncOp"> {
  let summary = "Dummy pass boilerplate";
  let constructor = "mlir::Expt::createExptDummyPass()";
  let options = [
    Option<"optionName", "option-name", "uint64_t", /*default=*/"512",
           "Set the option for in KiB (default: 512)">,
  ];
}


#endif // Expt_PASSES
