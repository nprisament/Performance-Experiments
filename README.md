# Performance-Experiments
Compilation and Code Performance Experimentation

## Setup
- Follow the Unix-like compiling instructions here: [MLIR Getting Started](https://mlir.llvm.org/getting_started/)
- run `ninja` in the `llvm-project/build` directory to build `MLIR`
- run `sudo ninja install` in the same directory to allow `CMake` to link `MLIR` to this project
- Install `LLVM` dependencies including `FileCheck` (which is used by the build of Google Benchmark), do the following in `llvm-project/build`:
    - run
    ```bash
    cmake -G Ninja -S ../llvm -B . \
        -DLLVM_ENABLE_PROJECTS="llvm" \
        -DCMAKE_BUILD_TYPE=Debug \
        -DLLVM_INCLUDE_TESTS=ON \
        -DLLVM_INSTALL_UTILS=ON \
        -DLLVM_INCLUDE_TOOLS=ON
    ```
    - run `ninja`
    - run `sudo ninja install`, This allows `CMake` to link against `FileCheck` and other LLVM binaries

#### Additional Optional Setup
- install `clang`: `sudo apt-get install clang`
- set `clang` as the default C compiler for CMake by running `sudo update-alternatives --config cc` and selecting `clang`

## Build
- `cmake -S . -B build -D CMAKE_BUILD_TYPE=[Release|Debug (default)]`
- `cmake --build build`

#### Resolving Build Issues
- run `rm -rf build` from the project root
- run `cmake -S . -B build`

#### Dependancies
- `/lib` is independant of `MLIR`
- `/test/lib` is independant of `MLIR`
- `/bench/lib` is independant of `MLIR`
- `/src` is dependant on `MLIR`
- `/test` is dependant on `MLIR`
- `/bench` is dependant on `MLIR`

When targets are built without `MLIR`, only the independant folders are built

#### Build Targets by File Name
- `/test/*.cpp` is built into the `perf-expr-tests` target for testing
- `/bench/b*.cpp` is built into the `perf-expr-bench` target for benchmarking
- `/bench/ab*.cpp` is built into the `perf-expr-asymp-bench` target for asymptotic benchmarking
- `/exec/expr-opt.cpp` is built using the `expr-opt` target which is disabled by-default

## Run Tests
#### Using CTest Directly
- `cd build`
- `ctest` or `gmake test`

#### Using Build Targets
- `cmake --build build --target [run_tests run_benchmarks run_asymp_bench]`