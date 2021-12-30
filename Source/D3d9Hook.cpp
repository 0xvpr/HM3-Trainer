#include "D3d9Hook.hpp"

static HWND g_window;

[[nodiscard]]
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {

    (void)lParam;

    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId) {
        return TRUE; // skip to next g_window
    }

    g_window = handle;
    return FALSE; // g_window found abort search
}

[[nodiscard]]
HWND GetProcessWindow() {

    g_window = NULL;
    EnumWindows(EnumWindowsCallback, (LPARAM)nullptr);

    return g_window;
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

    IDirect3DDevice9* pDummyDevice = NULL;

    // options to create dummy device
    D3DPRESENT_PARAMETERS d3dpp;
    memset(&d3dpp, 0, sizeof(d3dpp));

    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetProcessWindow();
    d3dpp.Windowed = true;

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
