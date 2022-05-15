#include "Events.hpp"

#include "Menu.hpp"
#include "Hacks.hpp"
#include "Entity.hpp"
#include "Offsets.hpp"

extern uintptr_t module_base_addr;

bool bCheatsEnabled = false;

extern HackMenu* menu;

static unsigned current_entity = 0;

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
        } else {
            hacks::ToggleInfiniteAmmo(menu->items["NUM1 - Infinite Ammo"].bEnabled);
            hacks::ToggleInfiniteHealth(menu->items["NUM2 - Infinite Health"].bEnabled);
            hacks::ToggleOneShot(menu->items["NUM3 - One Shot Kill"].bEnabled);
            hacks::ToggleStealth(menu->items["NUM4 - No Reactions"].bEnabled);
            hacks::ToggleNoRecoil(menu->items["NUM5 - No Recoil"].bEnabled);
        }

    }

    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD1) & 1) {
        menu->items["NUM1 - Infinite Ammo"].bEnabled = !menu->items["NUM1 - Infinite Ammo"].bEnabled;
        hacks::ToggleInfiniteAmmo(menu->items["NUM1 - Infinite Ammo"].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD2) & 1) {
        menu->items["NUM2 - Infinite Health"].bEnabled = !menu->items["NUM2 - Infinite Health"].bEnabled;
        hacks::ToggleInfiniteHealth(menu->items["NUM2 - Infinite Health"].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD3) & 1) {
        menu->items["NUM3 - One Shot Kill"].bEnabled = !menu->items["NUM3 - One Shot Kill"].bEnabled;
        hacks::ToggleOneShot(menu->items["NUM3 - One Shot Kill"].bEnabled); 
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD4) & 1) {
        menu->items["NUM4 - No Reactions"].bEnabled = !menu->items["NUM4 - No Reactions"].bEnabled;
        hacks::ToggleStealth(menu->items["NUM4 - No Reactions"].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD5) & 1) {
        menu->items["NUM5 - No Recoil"].bEnabled = !menu->items["NUM5 - No Recoil"].bEnabled;
        hacks::ToggleNoRecoil(menu->items["NUM5 - No Recoil"].bEnabled);
    }
    if (bCheatsEnabled && GetAsyncKeyState(VK_NUMPAD6) & 1) {
        menu->items["NUM6 - Flash"].bEnabled = !menu->items["NUM6 - Flash"].bEnabled;
        hacks::ToggleFlash(menu->items["NUM6 - Flash"].bEnabled);
    }

    // Previous Entity
    if ((GetAsyncKeyState(VK_OEM_4) & 1) > 0 && bCheatsEnabled) {
        SetCurrentEntity(-1);
    }

    // Next Entity
    if ((GetAsyncKeyState(VK_OEM_6) & 1) > 0 && bCheatsEnabled) {
        SetCurrentEntity(1);
    }

    if (((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && (GetAsyncKeyState('T') & 1) && bCheatsEnabled) {
        hacks::TeleportToCam();
    }

    if (!((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && (GetAsyncKeyState('T') & 1) && bCheatsEnabled) {
        hacks::TeleportToEntity(current_entity);
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
