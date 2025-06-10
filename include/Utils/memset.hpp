#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace mmst {
    inline void memsetFunc(void * ptr, size_t size) {
        memset(ptr, 0, size);
    }

    inline void memsetFunc(void * ptr, size_t size, int iterations) {
        for (int i = 0; i < iterations; i++) {
            memset(ptr, 0, size);
        }
    }

    inline void assignLoopFunc8(void * ptr, size_t size) {
        uint8_t * uint8_ptr = static_cast<uint8_t *>(ptr);
        uint8_t * itr8_ptr = static_cast<uint8_t *>(ptr);
        for (; itr8_ptr < uint8_ptr + size; itr8_ptr++) {
            *itr8_ptr = 0;
        }
    }

    inline void assignLoopFunc16(void * ptr, size_t size) {
        uint16_t * uint16_ptr = static_cast<uint16_t *>(ptr);
        uint16_t * itr_ptr = uint16_ptr;
        for (; itr_ptr < uint16_ptr + (size / 2); itr_ptr++) {
            *itr_ptr = 0ul;
        }
        if (size % 2 == 1) {
            uint8_t * itr8_ptr = reinterpret_cast<uint8_t *>(itr_ptr);
            *itr8_ptr = 0;
        }
    }

    inline void assignLoopFunc32(void * ptr, size_t size) {
        uint32_t * uint32_ptr = static_cast<uint32_t *>(ptr);
        uint32_t * itr_ptr = uint32_ptr;
        for (; itr_ptr < uint32_ptr + (size / 4); itr_ptr++) {
            *itr_ptr = 0ul;
        }
        uint8_t * uint8_ptr = reinterpret_cast<uint8_t *>(itr_ptr);
        uint8_t * itr8_ptr = reinterpret_cast<uint8_t *>(itr_ptr);
        for (; itr8_ptr < uint8_ptr + (size % 4); itr8_ptr++) {
            *itr8_ptr = 0;
        }
    }
    
    inline void assignLoopFunc(void * ptr, size_t size) {
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

    inline void assignLoopFunc(void * ptr, size_t size, int iterations) {
        for (int i = 0; i < iterations; i++) {
            assignLoopFunc(ptr, size);
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
