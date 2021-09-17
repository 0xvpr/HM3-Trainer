#pragma once

#include <vector>

namespace offsets
{
  unsigned XYZ_BASE_ADDR_PLAYER = 0x0041F83C;
  unsigned XYZ_BASE_ADDR_CAM  = 0x0041F81C;
  unsigned ONE_SHOT_ADDRESS   = 0x00632EA6;
  unsigned HEALTH_ADDRESS     = 0x005FB973;
  unsigned AMMO_ADDRESS     = 0x005140E7;
  unsigned ENTITY_COUNT     = 0x0059B864;
  unsigned ENTITY_BASE      = 0x0041F83C;

  std::vector<unsigned> XYZ_OFFSETS_CAM  = { 0x8C, 0x150, 0x10, 0x14, 0x54, 0x90, 0x2C };
  std::vector<unsigned> XYZ_OFFSETS_PLAYER = { 0xA20, 0x4, 0x50, 0x24 };
  std::vector<unsigned> ENTITY_OFFSETS   = { 0x40 };
}
