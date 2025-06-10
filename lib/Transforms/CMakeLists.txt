add_mlir_dialect_library(ExptTransforms
  ExptDummyPass.cpp

  LINK_COMPONENTS
  Core
  Support

  DEPENDS
  ExptTransformsPassesIncGen

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRPass
  MLIRTransforms
  MLIRExpt
  )

