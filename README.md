# Performance-Experiments
Compilation and Code Performance Experimentation

## Build
- `cmake -S . -B build -D CMAKE_BUILD_TYPE=[Release|Debug (default)]`
- `cmake --build build`

## Run Tests
#### Using CTest Directly
- `cd build`
- `ctest` or `gmake test`

#### Using Build Targets
- `cmake --build build --target [run_tests run_benchmarks run_asymp_bench]`