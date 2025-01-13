#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER

#include <cstdint>
#include <array>

namespace offsets {
    // Instructions
    constexpr uintptr_t               one_shot           = 0x232EA6;
    constexpr uintptr_t               stealth            = 0x149C2D;
    constexpr uintptr_t               health             = 0x1FB973;
    constexpr uintptr_t               ammo               = 0x1140E7;
    constexpr uintptr_t               syr_poison         = 0x2AD00D;
    constexpr uintptr_t               syr_sedative       = 0x2AD033;
    constexpr uintptr_t               clip_counter       = 0x114100;
    constexpr uintptr_t               recoil             = 0x249BCC;
    constexpr uintptr_t               mul                = 0x22CF9A;
    constexpr uintptr_t               speed              = 0x22BB11;

    // Object Pointers
    constexpr uintptr_t               player_xyz         = 0x41F83C;
    constexpr uintptr_t               cam_xyz            = 0x41F81C;
    constexpr uintptr_t               entity             = 0x41F83C;

    // Object Offsets
    constexpr std::array<uint16_t, 7> cam_xyz_offsets      { 0x8C, 0x150, 0x10, 0x14, 0x54, 0x90, 0x2C };
    constexpr std::array<uint16_t, 4> player_xyz_offsets = { 0xA20, 0x4, 0x50, 0x24 };
    constexpr std::array<uint16_t, 1> entity_offsets       { 0x40 };
}

#endif // OFFSETS_HEADER
