#ifndef HACKS_HEADER
#define HACKS_HEADER

#include <windows.h>
#include <tlhelp32.h>

namespace hacks {
    void TeleportToCam(void);
    void TeleportToEntity(unsigned target);
    void ToggleInfiniteAmmo(bool bEnabled);
    void ToggleInfiniteHealth(bool bEnabled);
    void ToggleOneShot(bool bEnabled);
    void ToggleStealth(bool bEnabled);
    void ToggleNoRecoil(bool bEnabled);
    void ToggleFlash(bool bEnabled);
    void KillCurrentEntity(unsigned target);
    void KillTargetInCrosshair(void);
    void DisarmEveryone(void);
}

#endif /* _HACKS_H */
