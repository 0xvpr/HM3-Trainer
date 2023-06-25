#ifndef MEM_HEADER
#define MEM_HEADER

#include <windows.h>
#include <cstdint>
#include <array>

namespace memory {

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param:  ptr
 * @param:  offsets
 *
 * @return: addr
**/
template <typename T, size_t size> [[nodiscard]]
T FindDynamicAddress(uintptr_t ptr, const std::array<unsigned, size>& offsets) {

    auto addr = ptr;

    for (const auto offset : offsets) {
        addr = *(uintptr_t *)addr;
        addr += offset;

        if (*(uintptr_t *)addr == 0) { 
            return 0;
        }
    }

    return reinterpret_cast<T>(addr);
}

/**
 * Byte replacement from source to destination.
 *
 * @param:  char* destination
 * @param:  char* source
 * @param:  size_t size
 *
 * @return: void
**/
bool Patch(void* dst, void* src, size_t size);

/**
 * Hooks into a function and detours the target function to another function.
 *
 * @param:  void* targetFunc
 * @param:  void* myFunc
 * @param:  size_t size
 *
 * @return: bool
**/
bool Detour(void* targetFunc, void* myFunc, size_t size);

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @param:  char* src
 * @param:  char* dst
 * @param:  size_t size
 *
 * @return: char*
**/
char* TrampHook(char* targetFunc, char* myFunc, size_t size);

/**
 * Scans a given chunk of data for the given pattern and mask.
 *
 * @param:  base_addr       The base address of where the scan data is from.
 * @param:  img_size        The size of the module.
 * @param:  pattern         The pattern to scan for.
 * @param:  pattern_size    The size of the pattern to scan for.
 *
 * @return: Pointer of the pattern found, 0 otherwise.
**/
unsigned char* FindPattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t s);

}

#endif // MEM_HEADER
