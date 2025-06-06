cmake_minimum_required(VERSION 3.14)
project(performance-experiments LANGUAGES CXX C)

# Globally set the build type to Release
# This will apply to your main project and all FetchContent dependencies.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting CMAKE_BUILD_TYPE to Release (no explicit build type given)")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set common optimization flags for Release
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "Flags used by the C++ compiler during Release builds." FORCE)
  set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "Flags used by the C compiler during Release builds." FORCE)
endif()

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(LLD_PATH NAMES lld)

if (LLD_PATH)
  message(STATUS "Found LLD linker: ${LLD_PATH}. Adding -fuse-ld=lld to link options.")
  add_link_options("-fuse-ld=lld")
else()
  message(STATUS "LLD linker not found. Not adding -fuse-ld=lld to link options.")
endif()

# To test NOT MLIR_FOUND paths, comment out the below line.
find_package(MLIR QUIET CONFIG)

if(MLIR_FOUND)
  message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
  message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

  set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
  set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
  set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR})
  list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
  list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
  include(TableGen)
  include(AddLLVM)
  include(AddMLIR)
  include(HandleLLVMOptions)

  include_directories(${LLVM_INCLUDE_DIRS})
  include_directories(${MLIR_INCLUDE_DIRS})
  link_directories(${LLVM_BUILD_LIBRARY_DIR})
  add_definitions(${LLVM_DEFINITIONS})

  # # TableGen

  # set(LLVM_TARGET_DEFINITIONS "/src/Passes/Passes.td")
  # mlir_tablegen(Passes.h.inc -gen-pass-decls -name=CustomPasses)
  # add_public_tablegen_target(CustomPassIncGen)
  # include_directories(${CMAKE_CURRENT_BINARY_DIR})

  # Tool Configuration

  get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
  get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
  
  file(GLOB_RECURSE MLIR_SOURCES "src/*.cpp")
  add_library(MLIR_SRC_LIB STATIC ${MLIR_SOURCES})
  # add_dependencies(MLIR_SRC_LIB CustomPassIncGen)

  set(MLIR_LIBS ${dialect_libs} ${conversion_libs} MLIROptLib MLIR_SRC_LIB)
else()
  message(STATUS "MLIR not found. Will build without MLIR support.")
  set(MLIR_LIBS)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
set(gtest_force_shared_crt ON CACHE BOOL "For Windows: Prevent overriding the parent project's compiler/linker settings" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "Disable building gmock" FORCE)
set(BUILD_GTEST_TESTS OFF CACHE BOOL "Disable building gtest tests" FORCE)
# set(BUILD_GMOCK_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST_EXAMPLES OFF CACHE BOOL "Disable building gtest examples" FORCE)
# set(BUILD_GMOCK_EXAMPLES OFF CACHE BOOL "" FORCE)
set(_original_cxx_flags "${CMAKE_CXX_FLAGS}")
set(_original_c_flags "${CMAKE_C_FLAGS}")
# Add warning supression to gtest due to clang non-compliance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-covered-switch-default")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-covered-switch-default")
FetchContent_MakeAvailable(googletest)
# Restore original flags to avoid affecting other targets
set(CMAKE_CXX_FLAGS "${_original_cxx_flags}")
set(CMAKE_C_FLAGS "${_original_c_flags}")

# Enable testing
enable_testing()

if(MLIR_FOUND)
  # Find all cpp files in the test directory
  file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
else()
  # If MLIR is not found, we can still run tests that do not depend on MLIR
  file(GLOB_RECURSE TEST_SOURCES "test/lib/*.cpp")
endif()

# Create a test executable
add_executable(perf-expr-tests ${TEST_SOURCES})
target_link_libraries(perf-expr-tests gtest_main ${MLIR_LIBS})

# Discover tests and add them to CTest
include(GoogleTest)
gtest_discover_tests(perf-expr-tests)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        main
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable building tests for google benchmark" FORCE)
set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "Use the previously fecthed gtest for google benchmark" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

if(MLIR_FOUND)
  # Find all cpp files in the test directory
  file(GLOB_RECURSE BENCH_SOURCES "bench/b*.cpp")
  file(GLOB_RECURSE ASYMPTOTIC_BENCH_SOURCES "bench/ab*.cpp")
else()
  # If MLIR is not found, we can still run benchmarks that do not depend on MLIR
  file(GLOB_RECURSE BENCH_SOURCES "bench/lib/b*.cpp")
  file(GLOB_RECURSE ASYMPTOTIC_BENCH_SOURCES "bench/lib/ab*.cpp")
endif()

# Create a test executable
add_executable(perf-expr-bench ${BENCH_SOURCES})
target_link_libraries(perf-expr-bench benchmark::benchmark_main ${MLIR_LIBS})
add_executable(perf-expr-asymp-bench ${ASYMPTOTIC_BENCH_SOURCES})
target_link_libraries(perf-expr-asymp-bench benchmark::benchmark_main ${MLIR_LIBS})

add_custom_target(run_tests
  COMMAND $<TARGET_FILE:perf-expr-tests>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running Google Tests..."
  DEPENDS perf-expr-tests
)

add_custom_target(run_benchmarks
  COMMAND $<TARGET_FILE:perf-expr-bench>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running Google Benchmarks..."
  DEPENDS perf-expr-bench
)

add_custom_target(run_asymp_bench
  COMMAND $<TARGET_FILE:perf-expr-asymp-bench>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running Asymptotic Google Benchmarks..."
  DEPENDS perf-expr-asymp-bench
)

if(MLIR_FOUND)
  add_llvm_executable(expr-opt "exec/expr-opt.cpp")

  llvm_update_compile_flags(expr-opt)
  target_link_libraries(expr-opt PRIVATE ${MLIR_LIBS})

  set_property(TARGET expr-opt PROPERTY EXCLUDE_FROM_ALL ON)
endif()
