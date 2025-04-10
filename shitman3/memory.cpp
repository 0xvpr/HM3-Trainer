#include "memory.hpp"

static inline bool compare_byte_array(unsigned char* data, unsigned char* pattern, size_t pattern_size) {
    for (size_t i = 0; i < pattern_size; ++i, ++pattern, ++data) {
        if (pattern[i] == '\0') {
            continue;
        } else if (data[i] != pattern[i]) {
            return false;
        }
    }

    return true;
}

unsigned char* memory::find_pattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t pattern_size) {
    BYTE first = pattern[0];
    PBYTE last = base_addr + img_size - pattern_size;

    for (; base_addr < last; ++base_addr) {
        if (*base_addr != first) {
            continue;
        } else if (compare_byte_array(base_addr, pattern, pattern_size)) {
            return base_addr;
        }
    }

    return nullptr;
}
