/**
 * Created by:          VPR
 * Created:             December 24th, 2021
 * 
 * Updated by:          VPR
 * Updated:             June 25th, 2023
 *
 * Description:         Hitman 3 (Hitman: Blood Money) cheats.
**/

#include "d3d9hook.hpp"
#include "render.hpp"
#include "events.hpp"
#include "memory.hpp"
#include "menu.hpp"

HackMenu* g_menu;

uintptr_t module_base_addr = 0;
HWND dll_handle = nullptr;

LPVOID d3d9Device[119];
tEndScene oEndScene = nullptr;
unsigned char oEndScene_bytes[7] = { 0 };

bool bMaximizeMenu = true;
bool bShutdown = false;
bool bInit = false;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
    if (bInit == false) {
        bInit = true;

        g_menu = render::InitializeMenu(pDevice);
        render::CreateFont(pDevice, 20);
    }
    render::Menu(pDevice);

    return oEndScene(pDevice);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
        memcpy(oEndScene_bytes, d3d9Device[42], sizeof(oEndScene_bytes));
        oEndScene = (tEndScene)memory::TrampHook((char *)d3d9Device[42], (char *)hkEndScene, sizeof(oEndScene_bytes));
    }

    while (!(bShutdown = events::HandleKeyboard(g_menu))) {
        // Main Loop
    }
    delete g_menu;

    memory::Patch(d3d9Device[42], oEndScene_bytes, sizeof(oEndScene_bytes));
    VirtualFree((LPVOID)oEndScene, sizeof(oEndScene_bytes), MEM_RELEASE);
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(lpReserved);

    switch (dwReason) {
        case DLL_PROCESS_ATTACH: {
            dll_handle = (HWND)hInstance;
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, MainThread, hInstance, 0, 0);
            break;
        }
        case DLL_PROCESS_DETACH: { break; }
        default:                 { break; }

    }

    return TRUE;
}
