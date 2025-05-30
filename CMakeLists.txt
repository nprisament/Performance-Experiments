cmake_minimum_required(VERSION 3.14)
project(performance-experiments)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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
