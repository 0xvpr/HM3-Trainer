#ifndef HACKS_HPP
#define HACKS_HPP

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>

namespace hacks {
    void TeleportToCam();
    void TeleportToEntity(unsigned target);
    void ToggleInfiniteAmmo(bool bEnabled);
    void ToggleInfiniteHealth(bool bEnabled);
    void ToggleOneShot(bool bEnabled);
    void ToggleStealth(bool bEnabled);
}

#endif /* _HACKS_H */
