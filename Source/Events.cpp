#include "Events.hpp"
#include "Hacks.hpp"

bool bCheatsEnabled = false;

bool events::HandleKeyboard(void) {
    
    if (GetAsyncKeyState(VK_TAB) & 1) {
        bCheatsEnabled = !bCheatsEnabled;
        hacks::ToggleGodMode(bCheatsEnabled);
    }

    if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState('T') & 1)) {
        hacks::TeleportToCam(bCheatsEnabled);
    }

    if (GetAsyncKeyState(VK_END)) {
        hacks::ToggleGodMode(false);
        return true;
    }

    return false;
}
