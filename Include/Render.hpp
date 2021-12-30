#ifndef RENDER_HPP
#define RENDER_HPP

#include "D3d9Hook.hpp"

namespace render {
    void InitializeRenderer(LPDIRECT3DDEVICE9 pDevice);
    void CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);
    void Menu(LPDIRECT3DDEVICE9 d3dDevice);
}

struct HackMenu
{
    bool bEnabled;
    char name[64];
};

struct Resolution
{
    int x;
    int y;
};

struct Coordinates
{
    int x;
    int y;
};

#endif // RENDER_HPP
