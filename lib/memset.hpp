#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace mmst {
    inline void memsetFunc(void * ptr, size_t size, int iterations) {
        for (int i = 0; i < iterations; i++) {
            memset(ptr, 0, size);
        }
    }

    inline void assignLoopFunc(void * ptr, size_t size, int iterations) {
        for (int i = 0; i < iterations; i++) {
            uint64_t * uint64_ptr = static_cast<uint64_t *>(ptr);
            uint64_t * itr_ptr = uint64_ptr;
            for (; itr_ptr < uint64_ptr + (size / 8); itr_ptr++) {
                *itr_ptr = 0ul;
            }
            uint8_t * uint8_ptr = reinterpret_cast<uint8_t *>(itr_ptr);
            uint8_t * itr8_ptr = reinterpret_cast<uint8_t *>(itr_ptr);
            for (; itr8_ptr < uint8_ptr + (size % 8); itr8_ptr++) {
                *itr8_ptr = 0;
            }
        }
    }

    inline void callocFunc(void *& ptr, size_t size, int iterations) {
        for (int i = 0; i < iterations; i++) {
            ptr = calloc(size, 1);
            free(ptr);
        }

        ptr = nullptr;
    }
}
