#ifndef DRAWING_HEADER
#define DRAWING_HEADER

#include <d3d9.h>
#include <d3dx9.h>

namespace draw {

namespace color {
    constexpr D3DCOLOR light_grey = D3DCOLOR_ARGB(255, 80, 80, 80);
    constexpr D3DCOLOR dark_grey  = D3DCOLOR_ARGB(255, 25, 25, 25);
    constexpr D3DCOLOR white      = D3DCOLOR_ARGB(255, 255, 255, 255);
    constexpr D3DCOLOR black      = D3DCOLOR_ARGB(255, 0, 0, 0);
    constexpr D3DCOLOR green      = D3DCOLOR_ARGB(255, 10, 200, 10);
    constexpr D3DCOLOR blue       = D3DCOLOR_ARGB(255, 0, 42, 255);
    constexpr D3DCOLOR red        = D3DCOLOR_ARGB(255, 255, 0, 0);
} // namespace color

void draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, LPDIRECT3DDEVICE9 d3dDevice);
void draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);
void draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font);

} // namespace draw

#endif // DRAWING_HEADER
