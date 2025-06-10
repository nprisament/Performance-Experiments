<<<<<<< HEAD
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
=======
cmake_minimum_required(VERSION 3.13.4)

project(Expt-dialect LANGUAGES CXX C)
>>>>>>> e720842 (initial commit using my mlir-template)

find_program(LLD_PATH NAMES lld)

if (LLD_PATH)
  message(STATUS "Found LLD linker: ${LLD_PATH}. Adding -fuse-ld=lld to link options.")
  add_link_options("-fuse-ld=lld")
else()
  message(STATUS "LLD linker not found. Not adding -fuse-ld=lld to link options.")
endif()

<<<<<<< HEAD
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
=======
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")

include(TableGen)
include(AddMLIR)
include(AddLLVM)
include(HandleLLVMOptions)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
link_directories(${LLVM_BUILD_LIBRARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

set(LLVM_LIT_ARGS "-sv" CACHE STRING "lit default options")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
include(sanitizers)

# -----------------------------------------------------------------------------
# Hybrid Googletest Inclusion
# -----------------------------------------------------------------------------

enable_testing()

find_package(GTest CONFIG QUIET)

if(NOT GTest_FOUND)
  message(STATUS "GTest library not found, attempting to download with FetchContent...")

  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
  )
  set(gtest_force_shared_crt ON CACHE BOOL "For Windows: Prevent overriding the parent project's compiler/linker settings" FORCE)
  set(BUILD_GMOCK OFF CACHE BOOL "Disable building gmock" FORCE)
  set(BUILD_GTEST_TESTS OFF CACHE BOOL "Disable building gtest tests" FORCE)
  set(BUILD_GMOCK_TESTS OFF CACHE BOOL "Disable building gmock tests" FORCE)
  set(BUILD_GTEST_EXAMPLES OFF CACHE BOOL "Disable building gtest examples" FORCE)
  set(BUILD_GMOCK_EXAMPLES OFF CACHE BOOL "Disable building gmock examples" FORCE)
  set(_original_cxx_flags "${CMAKE_CXX_FLAGS}")
  set(_original_c_flags "${CMAKE_C_FLAGS}")
  # Add warning supression to gtest due to clang non-compliance
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-covered-switch-default")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-covered-switch-default")
  FetchContent_MakeAvailable(googletest)
  # Restore original flags to avoid affecting other targets
  set(CMAKE_CXX_FLAGS "${_original_cxx_flags}")
  set(CMAKE_C_FLAGS "${_original_c_flags}")

  message(STATUS "GTest downloaded and configured via FetchContent.")
else()
  message(STATUS "GTest library found at ${GTest_DIR}")
endif()

# Check if we have GTest targets available (either from find_package or FetchContent)
if(TARGET GTest::gtest_main)
  message(STATUS "GTest targets are available")
else()
  message(FATAL_ERROR "Failed to find or download Googletest. Cannot proceed.")
endif()

# -----------------------------------------------------------------------------
# Hybrid Google Benchmark Inclusion
# -----------------------------------------------------------------------------

find_package(benchmark CONFIG QUIET)

if(NOT benchmark_FOUND)
  message(STATUS "Google Benchmark library not found, attempting to download with FetchContent...")

  include(FetchContent)

  FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        main
  )
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark testing" FORCE)
  set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "Disable benchmark exceptions" FORCE)
  set(BENCHMARK_ENABLE_LTO ON CACHE BOOL "Enable benchmark LTO" FORCE)
  set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "Use the previously fecthed gtest for google benchmark" FORCE)
  FetchContent_MakeAvailable(benchmark)

  message(STATUS "Google Benchmark downloaded and configured via FetchContent.")
else()
  message(STATUS "Google Benchmark library found at ${benchmark_DIR}")
endif()

# Check if we have benchmark targets available (either from find_package or FetchContent)
if(TARGET benchmark::benchmark_main)
  message(STATUS "Google Benchmark targets are available")
else()
  message(FATAL_ERROR "Failed to find or download Google Benchmark. Cannot proceed.")
endif()

# -----------------------------------------------------------------------------
# Subdirectories
# -----------------------------------------------------------------------------

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(tools)
add_subdirectory(unittest)
add_subdirectory(benchmark)

# -----------------------------------------------------------------------------
# Custom Run Targets
# -----------------------------------------------------------------------------

add_custom_target(run_unit_tests
  COMMAND $<TARGET_FILE:unittests>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMENT "Running Google Tests..."
  DEPENDS unittests
)

add_custom_target(run_lit_tests
  COMMAND ${CMAKE_COMMAND} --build . --target check-expt-opt
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running LIT Tests..."
)

add_custom_target(run_all_tests
  COMMAND ${CMAKE_COMMAND} --build . --target run_unit_tests run_lit_tests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(run_basic_benchmarks
  COMMAND $<TARGET_FILE:benchmarks>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running Basic Google Benchmarks..."
  DEPENDS benchmark
)

add_custom_target(run_asymptotic_benchmarks
  COMMAND $<TARGET_FILE:asymptotic-benchmarks>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Running Asymptotic Google Benchmarks..."
  DEPENDS asymptotic-benchmarks
)

add_custom_target(run_all_benchmarks
  COMMAND ${CMAKE_COMMAND} --build . --target run_basic_benchmarks run_asymptotic_benchmarks
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(run_all
  COMMAND ${CMAKE_COMMAND} --build . --target run_all_tests run_all_benchmarks
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
>>>>>>> e720842 (initial commit using my mlir-template)
