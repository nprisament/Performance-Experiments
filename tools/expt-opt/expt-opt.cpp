//===- expt-opt.cpp ---------------------------------------*- C++ -*-===//

#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"

int main(int argc, char **argv) {
  mlir::registerAllPasses();
  // TODO: Register Expt passes here.

  mlir::DialectRegistry registry;
  registerAllDialects(registry);
  // registry.insert<mlir::Expt::ExptDialect>();

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Expt optimizer driver\n", registry));
}
