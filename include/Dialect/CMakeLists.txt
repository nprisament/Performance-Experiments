add_mlir_dialect(ExptOps Expt)
add_mlir_doc(ExptDialect ExptDialect Dialect/ -gen-dialect-doc)
add_mlir_doc(ExptOps ExptOps Dialect/ -gen-op-doc)
add_dependencies(mlir-headers MLIRExptOpsIncGen)
