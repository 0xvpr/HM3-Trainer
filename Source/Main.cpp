/**
 * Creator:   VPR
 * Created:   December 24th, 2021
 * Updated:   December 24th, 2021
 * 
 * Description:
 *     Template for Video Game hacking using pure C
**/

#include "D3d9Hook.hpp"
#include "Render.hpp"
#include "Events.hpp"
#include "Memory.hpp"

uintptr_t module_base_addr = 0;
HWND dll_handle = nullptr;

LPVOID d3d9Device[119];
tEndScene oEndScene = nullptr;
char oEndScene_bytes[7] = { 0 };

bool bMaximizeMenu = true;
bool bShutdown = false;
bool bInit = false;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice) {

    if (bInit == false) {
        bInit = true;

        render::InitializeRenderer(pDevice);
        render::CreateFont(pDevice, 20);
    }
    render::Menu(pDevice);

    return oEndScene(pDevice);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {

    module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
        memcpy(oEndScene_bytes, d3d9Device[42], 7);
        oEndScene = (tEndScene)memory::TrampHook((char *)d3d9Device[42], (char *)hkEndScene, 7);
    }

    while (!(bShutdown = events::HandleKeyboard())) {
        // Main Loop
    }

    memory::Patch(d3d9Device[42], oEndScene_bytes, 7);
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {

    (void)lpReserved;
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
