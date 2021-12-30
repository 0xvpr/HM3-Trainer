#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include <cstddef>
#include <vector>

namespace offsets {
    // Pointers
    const unsigned player_xyz_addr                 = 0x41F83C;
    const unsigned cam_xyz_addr                    = 0x41F81C;
    const unsigned one_shot_addr                   = 0x632EA6;
    const unsigned health_addr                     = 0x5FB973;
    const unsigned ammo_addr                       = 0x5140E7;
    const unsigned entity_addr                     = 0x41F83C;

    // Offsets
    const std::vector<unsigned> cam_xyz_offsets    = { 0x8C, 0x150, 0x10, 0x14, 0x54, 0x90, 0x2C };
    const std::vector<unsigned> player_xyz_offsets = { 0xA20, 0x4, 0x50, 0x24 };
    const std::vector<unsigned> entity_offsets     = { 0x40 };
}

#endif // OFFSETS_HPP
