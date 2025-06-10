//===- ExptDialect.cpp - Expt dialect ---------------*- C++ -*-===//

#include "Dialect/ExptDialect.h"
#include "Dialect/ExptOps.h"

using namespace mlir;
using namespace mlir::Expt;

//===----------------------------------------------------------------------===//
// Expt dialect.
//===----------------------------------------------------------------------===//

void ExptDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "Dialect/ExptOps.cpp.inc"
      >();
}
