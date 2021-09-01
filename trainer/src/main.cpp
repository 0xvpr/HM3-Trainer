/////////////////////////////////////////////////
//                                             //
//  d8            8b 88888888b.  88888888b.    //
//   d8          8b  88      'Yb 88      'Yb   //
//    d8        8b   88       88 88       88   //
//     d8      8b    888888888P  888888888P    //
//      d8    8b     88          88  '88.      //
//       d8  8b      88          88    Y8b     //
//        d88b       88          88     '88.   //
//         db        88          88       Y8b. //
//                                              
///////////////////////////////////////////////////

#include "includes.h"
#include "hacks.hpp"

// ImGui Variables
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static HWND window = NULL;
EndScene oEndScene = NULL;
HANDLE game_module;
WNDPROC oWndProc;

// Render variables
extern bool bLastPass;
extern bool bInit;

// Static Variables
uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);

// Dynamic Variables
unsigned int current_entity = 0;
EntityList* entityList = nullptr;
float x_cam = 0;
float y_cam = 0;
float z_cam = 0;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}


long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    if (!bInit)
    {
        InitImGui(pDevice);
        bInit = true;
    }

	Hacks::UpdateGameState();
	Events::HandleKeyboard();
	Render::MainUI();

    // Disable all cheats before ejecting
    if (bLastPass)
    {
        kiero::shutdown();
    }

    return oEndScene(pDevice);
}


LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE; // skip to next window

    window = handle;
    return FALSE; // window found abort search
}


HWND GetProcessWindow()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}


DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool attached = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
        {
            kiero::bind(42, (void **)& oEndScene, hkEndScene);
            do
                window = GetProcessWindow();
            while (window == NULL);
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
            attached = true;
        }
    } while (!attached);

    return TRUE;
}


BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            kiero::shutdown();
            break;
    }

    return TRUE;
}
