#ifndef MEM_HEADER
#define MEM_HEADER


#include <type_traits>
#include <concepts>
#include <cstdint>
#include <array>

#include <windows.h>

namespace memory {

namespace instructions {
    constexpr std::uint8_t  nop     = 0x90;
    constexpr std::uint8_t  rel_jmp = 0xE9;
} // namespace constants

namespace constants {
    constexpr std::uint32_t rel_jmp_offset = 5;
} // namespace constants

namespace assembly {
    struct [[nodiscard, gnu::packed]] detour_block {
        std::uint8_t        rel_jmp       :  8;
        std::int32_t        relative_addr : 32;
    };

    template <std::size_t size>
    struct [[nodiscard, gnu::packed]] tramp_block {
        std::uint8_t        data[size];
        std::uint8_t        rel_jmp       :  8;
        std::int32_t        relative_addr : 32;
    };
} // namespace assembly

template <typename T>
concept address_type = requires {
    ( std::is_integral_v<T> && (sizeof(T) == sizeof(std::uintptr_t)) ) || std::is_pointer_v<T>;
};

template <class T>
concept function_pointer_type = requires { std::is_pointer_v<T> && std::is_function_v<std::remove_pointer_t<T>>; };

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param:  ptr
 * @param:  offsets
 *
 * @return: addr
**/
template < address_type     return_t = std::uintptr_t,
           std::integral     array_t,
           std::size_t    array_size  > [[nodiscard, gnu::always_inline]]
inline return_t find_dynamic_address(std::uintptr_t ptr, const std::array<array_t, array_size> offsets) {
    auto addr = ptr;

    for (const auto offset : offsets) {
        if (addr == 0 || *(reinterpret_cast<std::uintptr_t *>(addr)) == 0) { 
            return 0;
        }

        addr = *(std::uintptr_t *)addr;
        addr += offset;
    }

    return reinterpret_cast<return_t>(addr);
}

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param:  ptr
 * @param:  offsets
 *
 * @return: addr
**/
template < address_type     return_t = std::uintptr_t,
           std::integral     array_t,
           std::size_t    array_size  > [[nodiscard, gnu::always_inline]]
inline return_t find_dynamic_address(std::uintptr_t ptr, const array_t (&offsets)[array_size]) {
    auto addr = ptr;

    for (const auto offset : offsets) {
        addr = *(reinterpret_cast<std::uintptr_t *>(addr));
        addr += offset;

        if (*(reinterpret_cast<std::uintptr_t *>(addr)) == 0) { 
            return 0;
        }
    }

    return reinterpret_cast<return_t>(addr);
}

/**
 * Byte replacement from source to destination.
 *
 * @template(s): typename T, size_t size
 * @param:       std::int8_t* dst
 * @param:       const std::array<T, size>& instructions
 *
 * @return: void
**/
template < address_type       addr_t,
           std::integral     array_t,
           std::size_t    array_size  > [[gnu::always_inline]]
inline bool patch(addr_t addr, const array_t (&instructions)[array_size])
{
    DWORD oldprotect = 0;
    LPVOID dst = reinterpret_cast<LPVOID>(addr);

    VirtualProtect(dst, array_size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, instructions, array_size); 
    VirtualProtect(dst, array_size, oldprotect, &oldprotect);

    return true;
}

/**
 * Byte replacement from source to destination.
 *
 * @template(s): typename T, size_t size
 * @param:       std::int8_t* dst
 * @param:       const std::array<T, size>& instructions
 *
 * @return: void
**/
template < address_type       addr_t,
           std::integral     array_t,
           std::size_t    array_size  > [[gnu::always_inline]]
inline bool patch(addr_t addr, const std::array<array_t, array_size>& instructions)
{
    DWORD oldprotect = 0;
    LPVOID dst = reinterpret_cast<LPVOID>(addr);

    VirtualProtect(dst, array_size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, instructions.data(), instructions.size()); 
    VirtualProtect(dst, array_size, oldprotect, &oldprotect);

    return true;
}

/**
 * Byte replacement from source to destination.
 *
 * @template(s): typename T, size_t size
 * @param:       std::int8_t* dst
 * @param:       const std::array<T, size>& instructions
 *
 * @return: void
**/
template < std::size_t        N,
           address_type  addr_t  > [[gnu::always_inline]]
inline bool nop_sled(addr_t addr) {
    DWORD oldprotect = 0;
    LPVOID dst = reinterpret_cast<LPVOID>(addr);

    VirtualProtect(dst, N, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memset(dst, instructions::nop, N); 
    VirtualProtect(dst, N, oldprotect, &oldprotect);

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
template < std::size_t                     size,
           address_type           target_addr_t,
           function_pointer_type     new_fptr_t > [[gnu::always_inline]]
inline bool detour( target_addr_t   target_addr,
                    new_fptr_t         new_fptr) requires( size >= constants::rel_jmp_offset )
{
    DWORD old_protect = 0;
    VirtualProtect((LPVOID)+target_addr, size, PAGE_EXECUTE_READWRITE, &old_protect);

    memset((LPVOID)+target_addr, instructions::nop, size);

    std::int32_t relative_addr = static_cast<std::int32_t>((reinterpret_cast<std::uint32_t>(+new_fptr) - reinterpret_cast<std::uint32_t>(+target_addr) - memory::constants::rel_jmp_offset));
    auto* asm_block = reinterpret_cast<assembly::detour_block *>(+target_addr);
    asm_block->rel_jmp       = instructions::rel_jmp;
    asm_block->relative_addr = relative_addr;

    VirtualProtect((LPVOID)+target_addr, size, old_protect, &old_protect);

    return true;
}

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @template: size_t  size
 * @param:    std::int8_t*   target_fptr
 * @param:    std::int8_t*   tramp_fptr
 *
 * @return:   std::int8_t*   original_address
**/
template < function_pointer_type  target_fptr_t,
           function_pointer_type   tramp_fptr_t  > [[nodiscard, gnu::always_inline]]
inline std::uint8_t* trampoline_hook( target_fptr_t  target_fptr,
                                      tramp_fptr_t   tramp_fptr  ) 
{
    constexpr std::size_t size = 7;

    std::uint8_t* gateway = reinterpret_cast<std::uint8_t *>( VirtualAlloc( nullptr,
                                                                            size + memory::constants::rel_jmp_offset,
                                                                            MEM_COMMIT | MEM_RESERVE,
                                                                            PAGE_EXECUTE_READWRITE ) );
    memcpy(gateway, target_fptr, size);

    std::int32_t gate_jmp_addr = static_cast<std::int32_t>((reinterpret_cast<std::uintptr_t>(+target_fptr) - reinterpret_cast<std::uintptr_t>(+gateway) - memory::constants::rel_jmp_offset));
    auto& asm_block = *(reinterpret_cast<assembly::tramp_block<size> *>(+gateway));
    asm_block.rel_jmp = instructions::rel_jmp;
    asm_block.relative_addr = gate_jmp_addr;

    DWORD old_protect = 0;
    VirtualProtect(gateway, size, PAGE_EXECUTE_READ, &old_protect);

    if (detour<size>(+target_fptr, +tramp_fptr)) {
        return gateway;
    } else {
        return nullptr;
    }
}

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @template: size_t  size
 * @param:    std::int8_t*   target_fptr
 * @param:    std::int8_t*   tramp_fptr
 *
 * @return:   std::int8_t*   original_address
**/
template <std::size_t size> [[nodiscard, gnu::always_inline]]
inline std::uint8_t* trampoline_hook( std::int8_t*  target_fptr,
                                      std::int8_t*  tramp_fptr ) requires( size >= constants::rel_jmp_offset)
{
    std::uint8_t* gateway = reinterpret_cast<std::uint8_t *>( VirtualAlloc( nullptr,
                                                                            size + memory::constants::rel_jmp_offset,
                                                                            MEM_COMMIT | MEM_RESERVE,
                                                                            PAGE_EXECUTE_READWRITE ) );
    memcpy(gateway, target_fptr, size);

    std::int32_t gate_jmp_addr = static_cast<std::int32_t>((reinterpret_cast<std::uintptr_t>(+target_fptr) - reinterpret_cast<std::uintptr_t>(+gateway) - memory::constants::rel_jmp_offset));
    auto& asm_block = *(reinterpret_cast<assembly::tramp_block<size> *>(+gateway));
    asm_block.rel_jmp = instructions::rel_jmp;
    asm_block.relative_addr = gate_jmp_addr;

    DWORD old_protect = 0;
    VirtualProtect(gateway, size, PAGE_EXECUTE_READ, &old_protect);

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
std::uint8_t* find_pattern( std::uint8_t*  base_addr,
                            std::size_t    img_size,
                            std::uint8_t*  pattern,
                            std::size_t    s  );

} // namespace memory

#endif // MEM_HEADER
