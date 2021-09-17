#pragma once

#include "entity.h"

#include <windows.h>
#include <tlhelp32.h>
#include <cstdint>
#include <vector>

namespace Hacks
{
  /**
   * Enables infinite health, infinite ammo, and one shot kill
   *
   * @param bCheatsEnabled
   * @return void
  */
  void GodMode(bool bCheatsEnabled);

  /**
   * Increases or decreases current entity by providing 1 or -1, respectively, 
   * as the second function argument.
   *
   * @param &current_entity, -1 or 1
   * @return void
  */
  void SetCurrentEntity(unsigned int* current_entity, int operation);

  /**
   * Teleports the player to the overhead camera's target position.
   *
   * @param initial_offset, offsets, &x_cam, &y_cam, &z_cam
   * @return void
  */
  void TeleportToCam(float x_cam, float y_cam, float z_cam);

  /**
   * Attemps to teleport the player to entity location if the entity's 
   * location is not null.
   *
   * @param initial_offset, offsets, current_entity
   * @return void
  */
  void TeleportToEntity(unsigned int current_entity);

  /**
   * Stores the player's overhead camera target into last three float
   * parameters.
   *
   * @param initial_offset, offsets, &x_cam, &y_cam, &z_cam
   * @return void
  */
  void UpdatePlayerCamCoords(float* x_cam, float* y_cam, float* z_cam);

  void UpdateStatus(void);

  void UpdateCurrentEntity(void);

  void UpdatePlayerCamCoords(void);

  void UpdateEntityList(void);

  void UpdateGameState(void);
};
