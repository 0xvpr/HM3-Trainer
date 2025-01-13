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
template <typename T, typename array_t, size_t size> [[nodiscard]]
T FindDynamicAddress(uintptr_t ptr, const std::array<array_t, size>& offsets) {

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
 * @param:  T* source
 * @param:  size_t size
 *
 * @return: void
**/
template <typename T, std::size_t size>
bool Patch(void* dst, const std::array<T, size>& src) {
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, src.data(), size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);

    unsigned char* destination = (unsigned char *)dst;
    unsigned char* source = (unsigned char *)src.data();
    for (size_t i = 0; i < size; i++, destination++, source++) {
        if (*destination != *source ) {
            return false;
        }
    }

    return true;
}

/**
 * Byte replacement from source to destination.
 *
 * @param:  char* destination
 * @param:  T* source
 * @param:  size_t size
 *
 * @return: void
**/
template <typename T>
bool Patch(void* dst, T* src, size_t size) {
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, src, size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);

    unsigned char* destination = (unsigned char *)dst;
    unsigned char* source = (unsigned char *)src;
    for (size_t i = 0; i < size; i++, destination++, source++) {
        if (*destination != *source ) {
            return false;
        }
    }

    return true;
}


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
 * Hooks into a function and detours the target function to another function.
 *
 * @param:  void* targetFunc
 * @param:  void(* myFuncPtr)(void)
 * @param:  size_t size
 *
 * @return: bool
**/
bool Detour(void* targetFunc, void (* myFuncPtr)(void), size_t size);

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @param:  char* src
 * @param:  char* dst
 * @param:  size_t size
 *
 * @return: char*
**/
[[nodiscard]]
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
[[nodiscard]]
unsigned char* FindPattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t s);

} // namespace memory

#endif // MEM_HEADER
