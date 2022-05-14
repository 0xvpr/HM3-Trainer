#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include <stdint.h>
#include <vector>

namespace offsets {
    // Instructions
    constexpr unsigned one_shot_addr                   = 0x232EA6;
    constexpr unsigned stealth_addr                    = 0x149C2D;
    constexpr unsigned health_addr                     = 0x1FB973;
    constexpr unsigned ammo_addr                       = 0x1140E7;

    // Object Pointers
    constexpr unsigned player_xyz_addr                 = 0x41F83C;
    constexpr unsigned cam_xyz_addr                    = 0x41F81C;
    constexpr unsigned entity_addr                     = 0x41F83C;

    // Object Offsets
    const std::vector<unsigned> cam_xyz_offsets    = { 0x8C, 0x150, 0x10, 0x14, 0x54, 0x90, 0x2C };
    const std::vector<unsigned> player_xyz_offsets = { 0xA20, 0x4, 0x50, 0x24 };
    const std::vector<unsigned> entity_offsets     = { 0x40 };
}

#endif // OFFSETS_HPP
