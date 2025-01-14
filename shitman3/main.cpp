/**
 * Created by:          VPR
 * Created:             December 24th, 2021
 * 
 * Updated by:          VPR
 * Updated:             January 13th, 2025
 *
 * Description:         Hitman: Blood Money cheats.
**/



#include "d3d9hook.hpp"
#include "render.hpp"
#include "events.hpp"
#include "memory.hpp"
#include "menu.hpp"



// primitive global variables
static constexpr size_t d3d9_render_function_index = 42;
static constexpr size_t c_font_size = 20;
uintptr_t module_base_addr = 0;

// global pointers
typedef HRESULT(APIENTRY* endscene_t)(LPDIRECT3DDEVICE9 device_ptr);
endscene_t original_endscene = nullptr;
hack_menu* hack_menu::instance_ = nullptr;

// data and vtables
void* d3d9Device[119] = { 0 };
uint8_t original_endscene_bytes[7] = { 0 };



HRESULT APIENTRY endscene_hook(LPDIRECT3DDEVICE9 device_ptr) {
    static bool init = false;

    if ( !init ) {
        init = true;

        render::initialize_menu(device_ptr);
        render::create_font(device_ptr, c_font_size);
    }

    auto& menu = *hack_menu::instance();
    render::menu(device_ptr, menu);

    return original_endscene(device_ptr);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
    module_base_addr = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
        memcpy( original_endscene_bytes,
                d3d9Device[d3d9_render_function_index],
                sizeof(original_endscene_bytes));
        original_endscene = reinterpret_cast<endscene_t>(
                memory::TrampHook( reinterpret_cast<char *>(d3d9Device[d3d9_render_function_index]),
                                   reinterpret_cast<char *>(endscene_hook),
                                   sizeof(original_endscene_bytes) ) );
    }

    auto& menu = *hack_menu::instance();
    while ( events::handle_keyboard(menu) == false ) {
        // Main Loop
    }
    hack_menu::shutdown();

    memory::Patch(d3d9Device[d3d9_render_function_index], original_endscene_bytes, sizeof(original_endscene_bytes));
    VirtualFree((LPVOID)original_endscene, sizeof(original_endscene_bytes), MEM_RELEASE);
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);

    return TRUE;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(lpReserved);

    switch (dwReason) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, MainThread, hInstance, 0, 0);
            break;
        }
        case DLL_PROCESS_DETACH: { break; }
        default:                 { break; }

    }

    return TRUE;
}
