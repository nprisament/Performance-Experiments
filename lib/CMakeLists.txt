add_subdirectory(Transforms)
add_subdirectory(Pipeline)

# Create a combined library that includes all components
add_library(MLIRExptCombined INTERFACE)
target_link_libraries(MLIRExptCombined
  INTERFACE
  
  ExptPipeline
  ExptTransforms
)
