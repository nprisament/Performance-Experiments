add_mlir_dialect_library(MLIRExpt
        ExptDialect.cpp
        ExptOps.cpp

        ADDITIONAL_HEADER_DIRS
        ${PROJECT_SOURCE_DIR}/include/Dialect

        DEPENDS
        MLIRExptOpsIncGen

	LINK_LIBS PUBLIC
	MLIRIR
        MLIRInferTypeOpInterface
	)
