#include <benchmark/benchmark.h>
#include <cstddef>

#include "Utils/memset.hpp"

static constexpr size_t kSize = 32 * 1024; // 32 KiB

static void BM_Malloc(benchmark::State& state) {
  void * ptr;

  for (auto _ : state) {
    ptr = malloc(kSize);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }
}

BENCHMARK(BM_Malloc);

static void BM_Calloc(benchmark::State& state) {
  void * ptr;

  for (auto _ : state) {
    ptr = calloc(kSize, 1);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }
}

BENCHMARK(BM_Calloc);

static void BM_Memset(benchmark::State& state) {
  void * ptr = malloc(kSize);
  
  for (auto _ : state) {
    mmst::memsetFunc(ptr, kSize);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
}

BENCHMARK(BM_Memset);

static void BM_Loops(benchmark::State& state) {
  void * ptr = malloc(kSize);
  
  for (auto _ : state) {
    mmst::assignLoopFunc(ptr, kSize);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
}

BENCHMARK(BM_Loops);

static void BM_Loops8(benchmark::State& state) {
  void * ptr = malloc(kSize);
  
  for (auto _ : state) {
    mmst::assignLoopFunc8(ptr, kSize);
    benchmark::DoNotOptimize(ptr);
  }

  free(ptr);
}

BENCHMARK(BM_Loops8);

static void BM_MemsetWithMalloc(benchmark::State& state) {
  void * ptr;

  for (auto _ : state) {
    ptr = malloc(kSize);
    mmst::memsetFunc(ptr,kSize);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }
}

BENCHMARK(BM_MemsetWithMalloc);

static void BM_LoopsWithMalloc(benchmark::State& state) {
  void * ptr;

  for (auto _ : state) {
    ptr = malloc(kSize);
    mmst::assignLoopFunc(ptr,kSize);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }
}

BENCHMARK(BM_LoopsWithMalloc);

static void BM_Loops8WithMalloc(benchmark::State& state) {
  void * ptr;

  for (auto _ : state) {
    ptr = malloc(kSize);
    mmst::assignLoopFunc8(ptr,kSize);
    benchmark::DoNotOptimize(ptr);
    free(ptr);
  }
}

BENCHMARK(BM_Loops8WithMalloc);
