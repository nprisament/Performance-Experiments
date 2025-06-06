#include "mlir/InitAllDialects.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "../src/hi.hpp"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);
  hi::hi();
  
  return mlir::asMainReturnCode(mlir::MlirOptMain(argc, argv, "Experimental Pass Driver", registry));
}