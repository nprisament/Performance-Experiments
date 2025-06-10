#include <benchmark/benchmark.h>
#include <cstddef>

#include "Utils/memset.hpp"

static constexpr int multiplier = 4;
static constexpr int64_t start = 1<<7, limit = 1<<20;

static void BM_Memset(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr = malloc(size);
  
  for (auto _ : state) {
    mmst::memsetFunc(ptr, size);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Memset)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();

static void BM_Loops64(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr = malloc(size);
  
  for (auto _ : state) {
    mmst::assignLoopFunc(ptr, size);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Loops64)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();
