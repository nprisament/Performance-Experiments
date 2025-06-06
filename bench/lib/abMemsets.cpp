#include <benchmark/benchmark.h>
#include <cstddef>

#include "../../lib/memset.hpp"

static constexpr int multiplier = 4;
static constexpr int64_t start = 1<<7, limit = 1<<20;

static void BM_Malloc(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr;

  for (auto _ : state) {
    ptr = malloc(size);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Malloc)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();

static void BM_Calloc(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr;

  for (auto _ : state) {
    ptr = calloc(size, 1);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Calloc)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();

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

static void BM_Loops32(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr = malloc(size);
  
  for (auto _ : state) {
    mmst::assignLoopFunc32(ptr, size);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Loops32)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();

static void BM_Loops16(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr = malloc(size);
  
  for (auto _ : state) {
    mmst::assignLoopFunc16(ptr, size);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Loops16)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();

static void BM_Loops8(benchmark::State& state) {
  size_t size = state.range(0);
  void * ptr = malloc(size);
  
  for (auto _ : state) {
    mmst::assignLoopFunc8(ptr, size);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Loops8)->RangeMultiplier(multiplier)->Range(start, limit)->Complexity();
