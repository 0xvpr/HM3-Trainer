#ifndef   PATCHES_HEADER
#define   PATCHES_HEADER

#include <cstdint>
#include <array>

namespace patches {
    constexpr std::array<std::uint8_t, 1> ammo_original {
        0x49                                     // dec     eax
    };
    constexpr std::array<std::uint8_t, 1> ammo_patch {
        0x40                                     // inc     eax
    };
    constexpr std::array<std::uint8_t, 6> clip_counter_original {
        0xFF, 0x8E, 0x9C, 0x00, 0x00, 0x00       // dec     dword ptr [esi + 0x9C]
    };
    constexpr std::array<std::uint8_t, 6> clip_counter_patch {
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90                                     // nop
    };

    constexpr std::array<std::uint8_t, 4> health_original {
        0xD8, 0x64, 0x24, 0x08                   // fsub    dword ptr [esp + 0x8]
    };
    constexpr std::array<std::uint8_t, 4> health_patch {
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90                                     // nop
    };

    constexpr std::array<std::uint8_t, 1> syr_sedative_original {
        0x48                                     // dec eax
    };
    constexpr std::array<std::uint8_t, 1> syr_sedative_patch {
        0x90                                     // nop
    };

    constexpr std::array<std::uint8_t, 1> syr_poison_original {
        0x48                                     // dec eax
    };
    constexpr std::array<std::uint8_t, 1> syr_poison_patch {
        0x90                                     // nop
    };

    constexpr std::array<std::uint8_t, 10> one_shot_original {
        0xD8, 0x64, 0x24, 0x04,                  // fsub    dword ptr [esp + 0x4]
        0xD9, 0x91, 0x28, 0x09, 0x00, 0x00       // fst     dword ptr [ecx + 0x928]
    };
    constexpr std::array<std::uint8_t, 10> one_shot_patch {
        0xD8, 0xA1, 0x28, 0x09, 0x00, 0x00,      // fsub    dword ptr [ecx + 0x928]
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90                                     // nop
    };

    constexpr std::array<std::uint8_t, 2> stealth_original {
        0x3B, 0xC3                               // cmp     eax, ebx
    };

    constexpr std::array<std::uint8_t, 2> stealth_patch {
        0x39, 0xC0                               // cmp     eax, eax
    };

    constexpr std::array<std::uint8_t, 7> mul_original {
        0xC7, 0x46, 0x14, 0x00, 0x00, 0x80, 0x3F // mov     dword ptr [esi + 0x14], 0x3F800000
    };
    constexpr std::array<std::uint8_t, 6> speed_original {
        0xD9, 0x59, 0x24,                        // fstp    dword ptr [ecx + 0x24]
        0xC2, 0x04, 0x00                         // ret     4
    };

    constexpr std::array<std::uint8_t, 6> recoil_original {
        0xD9, 0x99, 0xF8, 0x00, 0x00, 0x00       // fstp    dword ptr [ecx + 0xF8]
    };


} // namespace patches

#endif // PATCHES_HEADER
