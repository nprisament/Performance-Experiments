cmake_minimum_required(VERSION 3.14)
project(performance-experiments)

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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Find all cpp files in the test directory
file(GLOB TEST_SOURCES "test/*.cpp")

# Create a test executable
add_executable(perf-expr-tests ${TEST_SOURCES})
target_link_libraries(perf-expr-tests gtest_main)

# Discover tests and add them to CTest
include(GoogleTest)
gtest_discover_tests(perf-expr-tests)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        main
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable building tests for google benchmark" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

# Find all cpp files in the test directory
file(GLOB BENCH_SOURCES "bench/b*.cpp")
file(GLOB ASYMPTOTIC_BENCH_SOURCES "bench/ab*.cpp")

# Create a test executable
add_executable(perf-expr-bench ${BENCH_SOURCES})
target_link_libraries(perf-expr-bench benchmark::benchmark_main)
add_executable(perf-expr-asymp-bench ${ASYMPTOTIC_BENCH_SOURCES})
target_link_libraries(perf-expr-asymp-bench benchmark::benchmark_main)

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

# set_property(target target1 PROPERTY EXCLUDE_FROM_ALL ON)
