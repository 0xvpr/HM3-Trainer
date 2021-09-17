#include "hacks.hpp"

#include "offsets.hpp"
#include "entity.h"
#include "mem.hpp"

#include <cmath>

extern unsigned int current_entity;
extern uintptr_t module_base_addr;
extern EntityList* entityList;

extern bool bCheatsEnabled;
extern bool bMaximizeMenu;
extern bool bIsLocked;
extern bool bLastPass;
extern bool bInGame;

extern float x_cam;
extern float y_cam;
extern float z_cam;

bool ValidCoordinate(float coordinate)
{
  if (coordinate == 0)
    return false;

  if (std::isnan(coordinate))
    return false;

  return true;
}

void Hacks::TeleportToCam(float x_cam, float y_cam, float z_cam)
{
  PlayerCoords* player = (PlayerCoords *)FindDMAddress(module_base_addr + offsets::XYZ_BASE_ADDR_PLAYER, offsets::XYZ_OFFSETS_PLAYER);

  player->x = x_cam;
  player->y = y_cam;
  player->z = z_cam;
}

void Hacks::TeleportToEntity(unsigned int current_entity)
{
  Entity* entity = entityList->ents[current_entity].entity;
  PlayerCoords* player = (PlayerCoords *)FindDMAddress(module_base_addr + offsets::XYZ_BASE_ADDR_PLAYER, offsets::XYZ_OFFSETS_PLAYER);

  if (entityList != nullptr && !std::isnan(entity->x) && !std::isnan(entity->y) && !std::isnan(entity->z) && entity != nullptr)
  {
    player->x = entity->x + 10;  // +10 to avoid collision math
    player->y = entity->y + 10;
    player->z = entity->z + 10;
  }

}

void Hacks::GodMode(bool bCheatsEnabled)
{
  char* AMMO_OP_CODES     = (char*)"\x49";
  char* HEALTH_OP_CODES     = (char*)"\xD8\x64\x24\x08";
  char* ONE_SHOT_OP_CODES   = (char*)"\xD8\x64\x24\x04\xD9\x91\x28\x09\x00\x00";

  char* AMMO_OP_CODES_NEW   = (char *)"\x90";
  char* HEALTH_OP_CODES_NEW   = (char *)"\x90\x90\x90\x90";
  char* ONE_SHOT_OP_CODES_NEW = (char *)"\xD8\xA1\x28\x09\x00\x00\x90\x90\x90\x90";

  char* AMMO_ADDRESS      = (char *)0x005140E7;
  char* HEALTH_ADDRESS    = (char *)0x005FB973;
  char* ONE_SHOT_ADDRESS    = (char *)0x00632EA6;

  size_t AMMO_OP_CODE_LENGTH   = 1;
  size_t HEALTH_OP_CODE_LENGTH   = 4;
  size_t ONE_SHOT_OP_CODE_LENGTH = 10;

  if (bCheatsEnabled)
  {
    Patch(AMMO_ADDRESS, AMMO_OP_CODES_NEW, AMMO_OP_CODE_LENGTH);
    Patch(HEALTH_ADDRESS, HEALTH_OP_CODES_NEW, HEALTH_OP_CODE_LENGTH);
    Patch(ONE_SHOT_ADDRESS, ONE_SHOT_OP_CODES_NEW, ONE_SHOT_OP_CODE_LENGTH); // Accidental Kills NO LONGER KILL
  }
  else
  {
    Patch(AMMO_ADDRESS, AMMO_OP_CODES, AMMO_OP_CODE_LENGTH);
    Patch(HEALTH_ADDRESS, HEALTH_OP_CODES, HEALTH_OP_CODE_LENGTH);
    Patch(ONE_SHOT_ADDRESS, ONE_SHOT_OP_CODES, ONE_SHOT_OP_CODE_LENGTH); // Accidental Kills NO LONGER KILL
  }

}

void Hacks::SetCurrentEntity(unsigned int* current_entity, int operation)
{
  if (!entityList)
  {
  *current_entity = 0;
  return;
  }

  switch (operation)
  {
  case 1:
    if (*current_entity > entityList->n_entities - 2)
    *current_entity = 0;
    else
    *current_entity += 1;
    break;
  case -1:
    if (*current_entity == 0)
    *current_entity = entityList->n_entities - 1;
    else
    *current_entity -= 1;
    break;
  default:
    break;
  }

}

void Hacks::UpdateStatus(void)
{
  if (entityList)
  bInGame = entityList->n_entities > 0;
  else
  bInGame = false;
}

void Hacks::UpdateCurrentEntity(void)
{
  if (!entityList)
  current_entity = 0;
}

void Hacks::UpdateEntityList()
{
  if (bCheatsEnabled)
  entityList = *(EntityList **)(module_base_addr + offsets::ENTITY_BASE);
  else
  entityList = nullptr;
}

void Hacks::UpdatePlayerCamCoords(void)
{
  if (bCheatsEnabled && bInGame)
  Hacks::UpdatePlayerCamCoords(&x_cam, &y_cam, &z_cam);
}

void Hacks::UpdatePlayerCamCoords(float* x_cam, float* y_cam, float* z_cam)
{ 
  PlayerCoords* coords = (PlayerCoords *)FindDMAddress(module_base_addr + offsets::XYZ_BASE_ADDR_CAM, offsets::XYZ_OFFSETS_CAM);

  *x_cam = coords->x;
  *y_cam = coords->y;
  *z_cam = coords->z;

}

void Hacks::UpdateGameState(void)
{
  Hacks::UpdateEntityList();
  Hacks::UpdateStatus();
  Hacks::UpdateCurrentEntity();
  Hacks::UpdatePlayerCamCoords();
}
