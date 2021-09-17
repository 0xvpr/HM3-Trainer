#include "events.hpp"

#include "hacks.hpp"
#include "entity.h"
#include "mem.hpp"

extern uintptr_t module_base_addr;

extern bool bCheatsEnabled;
extern bool bMaximizeMenu;
extern bool bIsLocked;
extern bool bLastPass;
extern bool bInGame;

extern unsigned int current_entity;
extern unsigned int menu_x;
extern unsigned int menu_y;

extern EntityList* entityList;

extern float x_cam;
extern float y_cam;
extern float z_cam;

void Events::HandleKeyboard(void)
{
  // Toggle menu options
  if (GetAsyncKeyState(VK_DELETE) & 1)
  bLastPass = true;

  if (GetAsyncKeyState(VK_END) & 1)
  bMaximizeMenu = !bMaximizeMenu;

  if (GetAsyncKeyState(VK_F1) & 1)
  bIsLocked = !bIsLocked;

  if (!bInGame)
  {
    current_entity = 0;
    x_cam = 0;
    y_cam = 0;
    z_cam = 0;
  }

  // Toggle God mode
  if ((GetAsyncKeyState(VK_TAB) & 1) > 0)
  {
    bCheatsEnabled = !bCheatsEnabled;
    Hacks::GodMode(bCheatsEnabled);
  }

  // Previous Entity
  if ((GetAsyncKeyState(VK_OEM_4) & 1) > 0 && bCheatsEnabled && bInGame)
  {
    Hacks::SetCurrentEntity(&current_entity, -1);
  }

  // Next Entity
  if ((GetAsyncKeyState(VK_OEM_6) & 1) > 0 && bCheatsEnabled && bInGame)
  {
    Hacks::SetCurrentEntity(&current_entity, 1);
  }

  // Teleport to entity
  if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState('T') & 1) > 0 && bCheatsEnabled && bInGame)
  {
    Hacks::TeleportToEntity(current_entity);
  }

  // Teleport to camera location
  if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState('T') & 1) > 0 && bCheatsEnabled && bInGame)
  {
    Hacks::TeleportToCam(x_cam, y_cam, z_cam);
  }

  // Initiate last pass
  if ((GetAsyncKeyState(VK_END) & 1))
  {
    bCheatsEnabled = false;
    bMaximizeMenu  = false;
    bLastPass = true;
  }

}
