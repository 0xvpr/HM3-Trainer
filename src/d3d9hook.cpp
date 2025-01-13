#include "d3d9hook.hpp"

[[nodiscard]]
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId) {
        return TRUE; // skip to next g_window
    }

    *(HWND *)lParam = handle;
    return false; // g_window found abort search
}

[[nodiscard]]
HWND GetProcessWindow() {
    HWND window = nullptr;
    EnumWindows(EnumWindowsCallback, (LPARAM)&window);

    return window;
}

[[nodiscard]]
bool GetD3D9Device(void** pTable, size_t Size) {
    if (!pTable) {
        return false;
    }

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!pD3D) {
        return false;
    }

    IDirect3DDevice9* pDummyDevice = nullptr;

    // options to create dummy device
    D3DPRESENT_PARAMETERS d3dpp;
    memset(&d3dpp, 0, sizeof(d3dpp));

    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetProcessWindow();
    d3dpp.Windowed = true;

    while (d3dpp.hDeviceWindow != GetForegroundWindow()) {
        // Wait for window to be Foreground
    }

    HRESULT dummyDeviceCreated = IDirect3D9_CreateDevice(pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
    if (dummyDeviceCreated != S_OK) {
        // may fail in windowed fullscreen mode, trying again with g_windowed mode
        d3dpp.Windowed = !d3dpp.Windowed;
        dummyDeviceCreated = IDirect3D9_CreateDevice(pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

        if (dummyDeviceCreated != S_OK) {
            pD3D->Release();
            return false;
        }
    }
    memcpy(pTable, *(void ***)pDummyDevice, Size);

    pDummyDevice->Release();
    pD3D->Release();
    return true;
}
