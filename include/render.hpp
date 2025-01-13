#ifndef RENDER_HEADER
#define RENDER_HEADER

#include "d3d9hook.hpp"
#include "menu.hpp"

namespace render {
    void InitializeMenu(LPDIRECT3DDEVICE9 pDevice);
    void CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);
    void Menu(LPDIRECT3DDEVICE9 d3dDevice, HackMenu* menu);
}

#endif // RENDER_HEADER
