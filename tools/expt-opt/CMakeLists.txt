get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
set(LIBS
        ${dialect_libs}
        ${conversion_libs}
        MLIROptLib
        MLIRExptCombined
        )
add_llvm_executable(expt-opt expt-opt.cpp)

llvm_update_compile_flags(expt-opt)
target_link_libraries(expt-opt PRIVATE ${LIBS})
