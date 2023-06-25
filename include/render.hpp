#ifndef RENDER_HEADER
#define RENDER_HEADER

#include "d3d9hook.hpp"
#include "menu.hpp"

namespace render {
    HackMenu* InitializeMenu(LPDIRECT3DDEVICE9 pDevice);
    void CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);
    void Menu(LPDIRECT3DDEVICE9 d3dDevice);
}

#endif // RENDER_HEADER
