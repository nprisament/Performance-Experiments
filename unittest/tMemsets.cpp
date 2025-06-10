#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <sys/types.h>

#include "Utils/memset.hpp"

class MemsetTest : public ::testing::Test {
  void TearDown() override {
    if (ptr) free(ptr);
  }

protected:
  void alloc() {
    ptr = malloc(size);
  }

  void * ptr;
  size_t size = 100;
  int iterations = 1000;
};

template <typename T>
static void testAllZero(void *ptr, size_t size) {
  for (size_t i = 0; i < size / sizeof(T); i++) {
    EXPECT_EQ(static_cast<T*>(ptr)[i], 0)
        << "Memory not initialized to zero at index: " << i;
  }
}

TEST_F(MemsetTest, Calloc) {
  mmst::callocFunc(ptr, size, iterations);
}

TEST_F(MemsetTest, Memset) {
  alloc();
  mmst::memsetFunc(ptr, size, iterations);
  testAllZero<uint8_t>(ptr, size);
}

TEST_F(MemsetTest, LoopAssign) {
  alloc();
  mmst::assignLoopFunc(ptr, size, iterations);
  testAllZero<uint8_t>(ptr, size);
}
