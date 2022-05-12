#ifndef RENDER_HPP
#define RENDER_HPP

#include "D3d9Hook.hpp"

namespace render {
    void InitializeMenu(LPDIRECT3DDEVICE9 pDevice);
    void CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);
    void Menu(LPDIRECT3DDEVICE9 d3dDevice);
}

#endif // RENDER_HPP
