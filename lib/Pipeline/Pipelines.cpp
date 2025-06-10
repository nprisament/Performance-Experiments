#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"

#include <mlir/Conversion/Passes.h>
#include <mlir/Dialect/Affine/Passes.h>
#include <mlir/Dialect/Linalg/Passes.h>

#include "Pipeline/Pipelines.h"
#include "Transforms/Passes.h"

namespace mlir {
class DialectRegistry;
} // namespace mlir

namespace {

//===----------------------------------------------------------------------===//
// CodeGen-related Pass Pipeline Helpers
//===----------------------------------------------------------------------===//
//
// helper pass-pipeline to convert linalg -> linalg.generic_op
void buildExptDummyPipeline(mlir::OpPassManager &pm) {
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void registerExptPipelines() {
  mlir::PassPipelineRegistration<>("Expt-dummy-pipeline",
                                   "fractal dummy pass pipeline",
                                   buildExptDummyPipeline);
}

/// Add all the MLIR dialects to the provided registry.
/// TODO: AirDialect has issue, cannot find getTypeID impl, fix when needed
inline void registerExptDialects(mlir::DialectRegistry &registry) {
  // clang-format off
  // registry.insert<mlir::Expt::ExptDialect>();
  // clang-format on
}

/// Append all the MLIR dialects to the registry contained in the given context.
// inline void registerExptDialects(mlir::MLIRContext &context) {
//   mlir::DialectRegistry registry;
//   registerExptDialects(registry);
//   context.appendDialectRegistry(registry);
// }
} // namespace

namespace mlir {
namespace Expt {

void bootstrapExptCompiler(mlir::DialectRegistry &registry) {

  // register dialect for ChopperRT target
  registerExptDialects(registry);

  // prepare codegen
  // mlir::RTI::registerFractalRTIPasses();
  // mlir::registerFractalCodegenPasses();
  // mlir::registerFractalOptimisationPasses();
  // mlir::registerFractalConversionPasses();

  // prepare pipelines
  registerExptPipelines();
}

} // namespace Expt
} // namespace mlir
