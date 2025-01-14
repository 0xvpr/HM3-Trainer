#include "events.hpp"

#include "offsets.hpp"
#include "entity.hpp"
#include "hacks.hpp"
#include "menu.hpp"

#include <windows.h>

enum cheats : std::size_t {
    infinite_ammo   =  0,
    infinite_health =  1,
    one_shot_kill   =  2,
    no_reactions    =  3,
    no_recoil       =  4,
    flash           =  5,
    teleport_to_cam =  6,
    kill_cam_target =  7,
    teleport_to_ent =  8,
    kill_target_ent =  9,
    kill_everyone   = 10
};

extern uintptr_t module_base_addr;
uint32_t current_entity = 0;

static inline
void set_current_entity(int operation) {
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    if (!entityList || !(entityList->n_entities > 7 && entityList->n_entities < 167)) {
        current_entity = 0;
        return;
    }

    switch (operation) {
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

bool events::handle_keyboard(hack_menu& menu) {
    if (GetAsyncKeyState(VK_TAB) & 1) {
        bool active = menu.toggle();

        hacks::toggle_infinite_ammo  ( active & menu[cheats::infinite_ammo].is_active()   );
        hacks::toggle_infinite_health( active & menu[cheats::infinite_health].is_active() );
        hacks::toggle_one_shot       ( active & menu[cheats::one_shot_kill].is_active()   );
        hacks::toggle_stealth        ( active & menu[cheats::no_reactions].is_active()    );
        hacks::toggle_no_recoil      ( active & menu[cheats::no_recoil].is_active()       );
        hacks::toggle_flash          ( active & menu[cheats::flash].is_active()           );

        return false;
    }

    if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD1) & 1) {
        hacks::toggle_infinite_ammo( menu[cheats::infinite_ammo].toggle() );
    }
    if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD2) & 1) {
        hacks::toggle_infinite_health( menu[cheats::infinite_health].toggle() );
    }
    if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD3) & 1) {
        hacks::toggle_one_shot( menu[cheats::one_shot_kill].toggle() );
    }
    if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD4) & 1) {
        hacks::toggle_stealth( menu[cheats::no_reactions].toggle() );
    }
    if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD5) & 1) {
        hacks::toggle_no_recoil( menu[cheats::no_recoil].toggle() );
    }
    if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD6) & 1) {
        hacks::toggle_flash( menu[cheats::flash].toggle() );
    }

//  // broken
//  if (menu.is_active() && GetAsyncKeyState(VK_NUMPAD9) & 1) {
//      hacks::DisarmEveryone();
//  }

    // Previous Entity
    if (menu.is_active() && (GetAsyncKeyState(VK_OEM_4) & 1) > 0) {
        set_current_entity(-1);
    }

    // Next Entity
    if (menu.is_active() && (GetAsyncKeyState(VK_OEM_6) & 1) > 0) {
        set_current_entity(1);
    }

    if (menu.is_active() && ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && (GetAsyncKeyState('T') & 1)) {
        hacks::teleport_to_cam();
    }

    if (menu.is_active() && !((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && GetAsyncKeyState('X') & 1) {
        hacks::kill_current_entity(current_entity);
    }

    if (menu.is_active() && !((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && (GetAsyncKeyState('T') & 1)) {
        hacks::teleport_to_entity(current_entity);
    }

    if (menu.is_active() && ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 1) && GetAsyncKeyState('X') & 1) {
        hacks::kill_target_in_crosshair();
    }

    if (GetAsyncKeyState(VK_HOME)) {
        hacks::toggle_infinite_health( false );
        hacks::toggle_infinite_ammo  ( false );
        hacks::toggle_no_recoil      ( false );
        hacks::toggle_one_shot       ( false );
        hacks::toggle_stealth        ( false );
        hacks::toggle_flash          ( false );

        return true;
    }

    return false;
}
