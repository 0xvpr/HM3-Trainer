#ifndef RENDER_HEADER
#define RENDER_HEADER

#include "d3d9hook.hpp"
#include "menu.hpp"

namespace render {
    void initialize_menu(LPDIRECT3DDEVICE9 device_ptr);
    void create_font(LPDIRECT3DDEVICE9 device_ptr, int size);
    void menu(LPDIRECT3DDEVICE9 d3dDevice, const hack_menu& menu);
}

#endif // RENDER_HEADER
