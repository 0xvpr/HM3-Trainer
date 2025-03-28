#ifndef MEM_HEADER
#define MEM_HEADER

#include <windows.h>

#include <cstdint>
#include <array>

namespace memory {

namespace instructions {
    constexpr std::uint8_t nop = 0x90;
    constexpr std::uint8_t rel_jmp = 0xE9;
} // namespace constants

namespace constants {
    constexpr std::uint32_t rel_jmp_offset = 5;
} // namespace constants

namespace assembly {
    struct [[nodiscard, gnu::packed]] detour_block {
        std::uint8_t rel_jmp:8;
        std::int32_t relative_addr:32;
    };

    template <std::size_t size>
    struct [[nodiscard, gnu::packed]] tramp_block {
        std::uint8_t data[size];
        std::uint8_t rel_jmp:8;
        std::int32_t relative_addr:32;
    };
} // namespace assembly

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param:  ptr
 * @param:  offsets
 *
 * @return: addr
**/
template <typename T, typename array_t, size_t size> [[nodiscard, gnu::always_inline]]
T find_dynamic_address(uintptr_t ptr, const std::array<array_t, size>& offsets) {
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
 * @template(s): typename T, size_t size
 * @param:       char* dst
 * @param:       const std::array<T, size>& instructions
 *
 * @return: void
**/
template <typename T, std::size_t size> [[gnu::always_inline]]
bool patch(void* dst, const std::array<T, size>& instructions)
{
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, instructions.data(), size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);

    unsigned char* destination = (unsigned char *)dst;
    unsigned char* source = (unsigned char *)instructions.data();
    for (size_t i = 0; i < size; ++i) {
        if (destination[i] != source[i]) {
            return false;
        }
    }

    return true;
}

/**
 * Hooks into a function and detours the target function to another function.
 *
 * @template: size_t  size
 * @param:    void*   target_fptr
 * @param:    void*   new_fptr
 *
 * @return:   bool    success
**/
template <std::size_t size> [[gnu::always_inline]]
inline bool detour( auto&& target_fptr,
             auto&& new_fptr ) requires(size >= constants::rel_jmp_offset)
{
    DWORD old_protect = 0;
    VirtualProtect(target_fptr, size, PAGE_EXECUTE_READWRITE, &old_protect);

    memset(target_fptr, instructions::nop, size);

    std::int32_t relative_addr = ((std::int32_t)new_fptr - (std::int32_t)target_fptr) - constants::rel_jmp_offset;
    auto* asm_block = reinterpret_cast<assembly::detour_block *>(+target_fptr);
    asm_block->rel_jmp       = instructions::rel_jmp;
    asm_block->relative_addr = relative_addr;

    VirtualProtect(target_fptr, size, old_protect, &old_protect);

    return true;
}

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @template: size_t  size
 * @param:    char*   target_fptr
 * @param:    char*   tramp_fptr
 *
 * @return:   char*   original_address
**/
template <std::size_t size> [[nodiscard, gnu::always_inline]]
std::uint8_t* trampoline_hook(char* target_fptr, char* tramp_fptr) requires( size >= constants::rel_jmp_offset) {
    std::uint8_t* gateway = (std::uint8_t *)VirtualAlloc(nullptr, size + memory::constants::rel_jmp_offset, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(gateway, target_fptr, size);

    std::int32_t gate_jmp_addr = (std::int32_t)((uintptr_t)(target_fptr - (uintptr_t)gateway) - memory::constants::rel_jmp_offset);
    auto* asm_block = reinterpret_cast<assembly::tramp_block<size> *>(+gateway);
    asm_block->rel_jmp = instructions::rel_jmp;
    asm_block->relative_addr = gate_jmp_addr;

    DWORD old_protect = 0;
    VirtualProtect((LPVOID)asm_block->relative_addr, size, PAGE_EXECUTE_READ, &old_protect);

    if (detour<size>(target_fptr, tramp_fptr)) {
        return gateway;
    } else {
        return nullptr;
    }
}


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
unsigned char* find_pattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t s);

} // namespace memory

#endif // MEM_HEADER
