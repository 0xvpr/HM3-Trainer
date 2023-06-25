#ifndef DRAWING_HEADER
#define DRAWING_HEADER

#include "d3d9hook.hpp"

namespace draw {

    void DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, LPDIRECT3DDEVICE9 d3dDevice);
    void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);
    void DrawText(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font);

    namespace color {
        constexpr D3DCOLOR LightGrey = D3DCOLOR_ARGB(255, 80, 80, 80);
        constexpr D3DCOLOR DarkGrey  = D3DCOLOR_ARGB(255, 25, 25, 25);
        constexpr D3DCOLOR White     = D3DCOLOR_ARGB(255, 255, 255, 255);
        constexpr D3DCOLOR Black     = D3DCOLOR_ARGB(255, 0, 0, 0);
        constexpr D3DCOLOR Green     = D3DCOLOR_ARGB(255, 10, 200, 10);
        constexpr D3DCOLOR Blue      = D3DCOLOR_ARGB(255, 0, 42, 255);
        constexpr D3DCOLOR Red       = D3DCOLOR_ARGB(255, 255, 0, 0);
    }

}

#endif // DRAWING_HEADER
