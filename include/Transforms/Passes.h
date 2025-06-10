//===- Passes.h - Pass Entrypoints ------------------------------*- C++ -*-===//

#pragma once

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#include "Dialect/ExptDialect.h"

namespace mlir {
namespace Expt {

// Declare your pass entry
std::unique_ptr<OperationPass<mlir::func::FuncOp>> createExptDummyPass();

//===----------------------------------------------------------------------===//
// Handle table-gen pass decls and registrations
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Declaration
//===----------------------------------------------------------------------===//

#define GEN_PASS_DECL
#include "Transforms/Passes.h.inc"

//===----------------------------------------------------------------------===//
// Registration
//===----------------------------------------------------------------------===//
//
#define GEN_PASS_REGISTRATION
#include "Transforms/Passes.h.inc"

//===----------------------------------------------------------------------===//
// Classes
//===----------------------------------------------------------------------===//
//
#define GEN_PASS_CLASSES
#include "Transforms/Passes.h.inc"

} // namespace Expt

} // namespace mlir
