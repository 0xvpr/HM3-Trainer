#include "Events.hpp"

#include "Hacks.hpp"
#include "Entity.hpp"
#include "Offsets.hpp"

extern uintptr_t module_base_addr;

bool bCheatsEnabled = false;

unsigned current_entity = 0;

static inline
void SetCurrentEntity(unsigned& current_entity, int operation) {

    auto entityList = *(EntityList **)(module_base_addr + offsets::entity_addr);
    if (!entityList) {
        current_entity = 0;
        return;
    }

    auto bInGame = []{
        auto entityList = *(EntityList **)(module_base_addr + offsets::entity_addr);
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
        hacks::ToggleGodMode(bCheatsEnabled);
    }

    // Previous Entity
    if ((GetAsyncKeyState(VK_OEM_4) & 1) > 0 && bCheatsEnabled)
    {
        SetCurrentEntity(current_entity, -1);
    }

    // Next Entity
    if ((GetAsyncKeyState(VK_OEM_6) & 1) > 0 && bCheatsEnabled) 
    {
        SetCurrentEntity(current_entity, 1);
    }

    if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState('T') & 1) && bCheatsEnabled) {
        hacks::TeleportToCam();
    }

    if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState('T') & 1) && bCheatsEnabled) {
        hacks::TeleportToEntity(current_entity);
    }

    if (GetAsyncKeyState(VK_END)) {
        hacks::ToggleGodMode(false);
        return true;
    }

    return false;
}
