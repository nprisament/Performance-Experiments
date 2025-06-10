//===- ExptDialect.td - Expt dialect -----------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef Expt_DIALECT
#define Expt_DIALECT

include "mlir/IR/OpBase.td"

//===----------------------------------------------------------------------===//
// Expt dialect definition.
//===----------------------------------------------------------------------===//

def Expt_Dialect : Dialect {
    let name = "Expt";
    let summary = "A Expt out-of-tree MLIR dialect.";
    let description = [{
        This dialect is an example of an out-of-tree MLIR dialect designed to
        illustrate the basic setup required to develop MLIR-based tools without
        working inside of the LLVM source tree.
    }];
    let cppNamespace = "::mlir::Expt";
}

//===----------------------------------------------------------------------===//
// Base Expt operation definition.
//===----------------------------------------------------------------------===//

class Expt_Op<string mnemonic, list<Trait> traits = []> :
        Op<Expt_Dialect, mnemonic, traits>;

#endif // Expt_DIALECT
