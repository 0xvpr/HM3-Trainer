/**
 * Created by:          VPR
 * Created:             December 24th, 2021
 * 
 * Updated by:          VPR
 * Updated:             March 28th, 2025
 *
 * Description:         Hitman: Blood Money cheats.
**/



#include "d3d9hook.hpp"
#include "memory.hpp"
#include "menu.hpp"


// global pointers
static d3d9::endscene_t original_endscene = nullptr;

// render device data and vtable
void* d3d9_device[119] = { 0 };
std::array<uint8_t, 7> original_endscene_bytes = { 0 };


HRESULT APIENTRY endscene_hook(LPDIRECT3DDEVICE9 device_ptr) {
    auto& menu = *menu::menu::instance();
    menu.render(device_ptr);

    return original_endscene(device_ptr);
}

DWORD WINAPI main_thread(HINSTANCE instance) {
    if ( d3d9::get_device(d3d9_device, sizeof(d3d9_device)) ) {
        memcpy( original_endscene_bytes.data(),
                d3d9_device[d3d9::render_function_index],
                sizeof(original_endscene_bytes));

        original_endscene = reinterpret_cast<d3d9::endscene_t>(
            memory::trampoline_hook(
                reinterpret_cast<char *>(d3d9_device[d3d9::render_function_index]),
                reinterpret_cast<char *>(endscene_hook)
            )
        );
    }

    auto& menu = *menu::menu::instance();
    menu.run(); // main loop
    menu::menu::shutdown();

    memory::patch( d3d9_device[d3d9::render_function_index], original_endscene_bytes );
    VirtualFree( (LPVOID)original_endscene, sizeof(original_endscene_bytes), MEM_RELEASE );
    FreeLibraryAndExitThread(instance, 0);
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(lpReserved);

    switch (dwReason) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main_thread, hInstance, 0, 0);
            break;
        }
        case DLL_PROCESS_DETACH: { break; }
        default:                 { break; }

    }

    return true;
}
