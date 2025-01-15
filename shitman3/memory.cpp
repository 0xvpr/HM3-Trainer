#include "memory.hpp"

bool memory::detour(void* targetFunc, void* myFunc, size_t size) {
    if (size < 5) {
        return false;
    }

    DWORD dwProtect;
    VirtualProtect(targetFunc, size, PAGE_EXECUTE_READWRITE, &dwProtect);

    memset(targetFunc, 0x90, size); // memset nop
    uintptr_t relative_addr = ((uintptr_t)myFunc - (uintptr_t)targetFunc) - 5;

    *(unsigned char *)targetFunc = 0xE9; // replace with jmp
    *(uintptr_t *)((uintptr_t)targetFunc + 1) = relative_addr;
    VirtualProtect(targetFunc, size, dwProtect, &dwProtect);

    return true;
}

bool memory::detour(void* targetFunc, void(* myFuncPtr)(void), size_t size) {
    if (size < 5) {
        return false;
    }

    DWORD dwProtect;
    VirtualProtect(targetFunc, size, PAGE_EXECUTE_READWRITE, &dwProtect);

    memset(targetFunc, 0x90, size); // memset nop
    uintptr_t relative_addr = ((uintptr_t)myFuncPtr - (uintptr_t)targetFunc) - 5;

    *(unsigned char *)targetFunc = 0xE9; // replace with jmp
    *(uintptr_t *)((uintptr_t)targetFunc + 1) = relative_addr;
    VirtualProtect(targetFunc, size, dwProtect, &dwProtect);

    return true;
}

char* memory::trampoline_hook(char* src, char* dst, size_t size) {
    if (size < 5) {
        return 0;
    }

    char* gateway = (char *)VirtualAlloc(nullptr, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(gateway, src, size);

    uintptr_t gateJmpAddress = (uintptr_t)(src - gateway - 5);
    *(gateway + size) = (char)0xE9;
    *(uintptr_t *)(gateway + size + 1) = gateJmpAddress;

    if (memory::detour(src, dst, size)) {
        return gateway;
    } else {
        return nullptr;
    }
}

static inline BOOL CompareByteArray(unsigned char* data, unsigned char* pattern, size_t pattern_size) {
    for (size_t i = 0; i < pattern_size; i++, pattern++, data++) {
        if (*pattern == '\0') {
            continue;
        } else if (*data != *pattern) {
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
        } else if (CompareByteArray(base_addr, pattern, pattern_size)) {
            return base_addr;
        }
    }

    return NULL;
}
