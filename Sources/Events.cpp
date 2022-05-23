#include "Events.hpp"

#include "Menu.hpp"
#include "Hacks.hpp"
#include "Entity.hpp"
#include "Offsets.hpp"

enum cheats {
    infinite_ammo   = 0,
    infinite_health = 1,
    one_shot_kill   = 2,
    no_reactions    = 3,
    no_recoil       = 4,
    flash           = 5,
    teleport_to_cam = 6,
    kill_cam_target = 7,
    teleport_to_ent = 8,
    kill_target_ent = 9,
    kill_everyone   = 10
};

bool bCheatsEnabled = false;

extern uintptr_t module_base_addr;

extern HackMenu* menu;

unsigned current_entity = 0;

static inline
void SetCurrentEntity(int operation) {

    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    if (!entityList) {
        current_entity = 0;
        return;
    }

    auto bInGame = [&entityList]{
        //auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
        return entityList->n_entities > 1 && entityList->n_entities < 167;
    }();

    if (!bInGame) {
        return;
    }

    switch (operation)
    {
    case 1:
        if (current_entity > entityList->n_entities - 2) {
            current_entity = 0;
        } else {
            current_entity += 1;
        }
        break;
    case -1:
        if (current_entity == 0) {
            current_entity = entityList->n_entities - 1;
        } else {
            current_entity -= 1;
        }
        break;
    default:
        break;
    }

}

bool events::HandleKeyboard(void) {
    
    if (GetAsyncKeyState(VK_TAB) & 1) {
        bCheatsEnabled = !bCheatsEnabled;

        if (!bCheatsEnabled) {
            hacks::ToggleInfiniteAmmo(false);
            hacks::ToggleInfiniteHealth(false);
            hacks::ToggleOneShot(false);
            hacks::ToggleStealth(false);
            hacks::ToggleNoRecoil(false);
            hacks::ToggleFlash(false);
        } else {
            hacks::ToggleInfiniteAmmo(menu->items[cheats::infinite_ammo].bEnabled);
            hacks::ToggleInfiniteHealth(menu->items[cheats::infinite_health].bEnabled);
            hacks::ToggleOneShot(menu->items[cheats::one_shot_kill].bEnabled);
            hacks::ToggleStealth(menu->items[cheats::no_reactions].bEnabled);
            hacks::ToggleNoRecoil(menu->items[cheats::no_recoil].bEnabled);
            hacks::ToggleFlash(menu->items[cheats::flash].bEnabled);
        }

    }

    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD1) & 1) {
        menu->items[cheats::infinite_ammo].bEnabled = !menu->items[cheats::infinite_ammo].bEnabled;
        hacks::ToggleInfiniteAmmo(menu->items[cheats::infinite_ammo].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD2) & 1) {
        menu->items[cheats::infinite_health].bEnabled = !menu->items[cheats::infinite_health].bEnabled;
        hacks::ToggleInfiniteHealth(menu->items[cheats::infinite_health].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD3) & 1) {
        menu->items[cheats::one_shot_kill].bEnabled = !menu->items[cheats::one_shot_kill].bEnabled;
        hacks::ToggleOneShot(menu->items[cheats::one_shot_kill].bEnabled); 
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD4) & 1) {
        menu->items[cheats::no_reactions].bEnabled = !menu->items[cheats::no_reactions].bEnabled;
        hacks::ToggleStealth(menu->items[cheats::no_reactions].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD5) & 1) {
        menu->items[cheats::no_recoil].bEnabled = !menu->items[cheats::no_recoil].bEnabled;
        hacks::ToggleNoRecoil(menu->items[cheats::no_recoil].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD6) & 1) {
        menu->items[cheats::flash].bEnabled = !menu->items[cheats::flash].bEnabled;
        hacks::ToggleFlash(menu->items[cheats::flash].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD9) & 1) {
        hacks::KillEveryone();
    }

    // Previous Entity
    if (bCheatsEnabled && (GetAsyncKeyState(VK_OEM_4) & 1) > 0) {
        SetCurrentEntity(-1);
    }

    // Next Entity
    if (bCheatsEnabled && (GetAsyncKeyState(VK_OEM_6) & 1) > 0) {
        SetCurrentEntity(1);
    }

    if (bCheatsEnabled && ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && (GetAsyncKeyState('T') & 1)) {
        hacks::TeleportToCam();
    }

    if (bCheatsEnabled && !((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && GetAsyncKeyState('X') & 1) {
        hacks::KillCurrentEntity(current_entity);
    }

    if (bCheatsEnabled && !((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && (GetAsyncKeyState('T') & 1)) {
        hacks::TeleportToEntity(current_entity);
    }

    if (bCheatsEnabled && ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && GetAsyncKeyState('X') & 1) {
        hacks::KillTargetInCrosshair();
    }

    if (GetAsyncKeyState(VK_HOME)) {
        hacks::ToggleInfiniteAmmo(false);
        hacks::ToggleInfiniteHealth(false);
        hacks::ToggleOneShot(false);
        hacks::ToggleStealth(false);
        hacks::ToggleNoRecoil(false);
        return true;
    }

    return false;
}
