#pragma once

#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"

namespace mlir {
namespace Expt {

// Bootstrap utility for entire system
void bootstrapExptCompiler(mlir::DialectRegistry &registry);

} // namespace Expt
} // namespace mlir
