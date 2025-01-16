#include "d3d9hook.hpp"

[[nodiscard]]
static BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam) {
    DWORD wndProcId = 0;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId) {
        return true; // skip to next window
    }

    *(HWND *)lParam = handle;
    return false; // window found abort search
}

[[nodiscard]]
static inline HWND GetProcessWindow() {
    HWND window = nullptr;
    EnumWindows(enum_windows_callback, (LPARAM)&window);

    return window;
}

bool d3d9::get_device(void** vtable, size_t size) {
    if (!vtable) {
        return false;
    }

    IDirect3D9* d3d_ptr = Direct3DCreate9(D3D_SDK_VERSION);

    if (!d3d_ptr) {
        return false;
    }


    // options to create dummy device
    D3DPRESENT_PARAMETERS d3dpp{
        .SwapEffect    = D3DSWAPEFFECT_DISCARD,
        .hDeviceWindow = GetProcessWindow(),
        .Windowed      = true
    };

    while (d3dpp.hDeviceWindow != GetForegroundWindow()) {
        // Wait for window to be Foreground
    }

    IDirect3DDevice9* dummy_device_ptr = nullptr;
    HRESULT dummyDeviceCreated = IDirect3D9_CreateDevice(d3d_ptr, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &dummy_device_ptr);
    if (dummyDeviceCreated != S_OK) {
        // may fail in windowed fullscreen mode, trying again with windowed mode
        d3dpp.Windowed = !d3dpp.Windowed;
        dummyDeviceCreated = IDirect3D9_CreateDevice(d3d_ptr, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &dummy_device_ptr);

        if (dummyDeviceCreated != S_OK) {
            d3d_ptr->Release();
            return false;
        }
    }
    memcpy(vtable, *reinterpret_cast<void ***>(dummy_device_ptr), size);

    dummy_device_ptr->Release();
    d3d_ptr->Release();

    return true;
}
