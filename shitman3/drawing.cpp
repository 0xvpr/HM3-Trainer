#include "drawing.hpp"

void draw::draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice) {
     draw::draw_filled_rect(x, y, w, thickness, color, d3dDevice);                 // Top horizontal line
     draw::draw_filled_rect(x, y, thickness, h, color, d3dDevice);                 // Left vertical line
     draw::draw_filled_rect((x + w), y, thickness, h, color, d3dDevice);           // Right vertical line
     draw::draw_filled_rect(x, y + h, w + thickness, thickness, color, d3dDevice); // Bottom horizontal line
}

void draw::draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice) {
    D3DRECT BarRect = { x, y, x + w, y + h };

    IDirect3DDevice9_Clear(d3dDevice, 1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

void draw::draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font) {
    RECT rct = { x, y, x + width, y + height };

    font->DrawTextA(nullptr, text, -1, &rct, DT_NOCLIP, color);
}
