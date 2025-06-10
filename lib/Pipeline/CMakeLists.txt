add_mlir_conversion_library(ExptPipeline
  Pipelines.cpp

  LINK_COMPONENTS
  Core

  LINK_LIBS PUBLIC
  MLIRIR
)
