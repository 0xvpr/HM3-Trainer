#include "binkw32.hpp"
#include <windows.h>

#include <filesystem>

unsigned long __attribute__(( stdcall, used )) shitman_loader(void* m) {
    std::filesystem::path shitman_path("shitman3.dll");
    if ( (std::filesystem::exists(shitman_path)) ) {
        MessageBoxA(nullptr, "Alt + Tab, then press OK to load in shitman.dll.", "ez shitman loader", 0);
        LoadLibraryA("shitman3.dll");
    }

    FreeLibraryAndExitThread((HMODULE)m, 0);
}

int __attribute__(( constructor, used )) dll_entry(DWORD reason, HMODULE instance) {
    (void)reason;
    DisableThreadLibraryCalls(instance);
    CreateThread(nullptr, 0, shitman_loader, instance, 0, nullptr);

    return 1;
}
