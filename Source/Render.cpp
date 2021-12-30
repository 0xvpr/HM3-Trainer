#include "Render.hpp"
#include "Drawing.hpp"
#include <cstdio>

extern bool bMaximizeMenu;
extern bool bCheatsEnabled;

extern LPD3DXFONT m_font;
extern LPD3DXFONT m_font_small;

Resolution resolution = { 0, 0 };
Coordinates menuPosition = { 30, 25 };
 /*HackMenu hackMenu[MAX_MENU_ITEMS] = { 0 };*/

void render::InitializeRenderer(LPDIRECT3DDEVICE9 pDevice) {

    (void)pDevice; // Delete when needed
    // Initialize Menu Items
}

void render::Menu(LPDIRECT3DDEVICE9 d3dDevice) {

    // resolution = *((Resolution *)(offset_resolution));
    D3DDISPLAYMODE  d3dDisplayMode;
    float           factor;
    char            buffer[32];

    // Get Resolution
    IDirect3DDevice9_GetDisplayMode(d3dDevice, 0, &d3dDisplayMode);

    // Draw Height
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Height: %u", d3dDisplayMode.Height);
    draw::DrawTextA(buffer, menuPosition.x, menuPosition.y - 25, 140, 20, draw::color::LightGrey, m_font);

    // Draw Width
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Width: %u", d3dDisplayMode.Width);
    draw::DrawTextA(buffer, menuPosition.x + 140, menuPosition.y - 25, 140, 20, draw::color::LightGrey, m_font);

    if (bMaximizeMenu) {
        factor = 1.0;

        // Title Template
        draw::DrawFilledRect(menuPosition.x, menuPosition.y, 140, 100, draw::color::DarkGrey, d3dDevice);
        draw::DrawBorderBox(menuPosition.x, menuPosition.y, 140, 100, 4, draw::color::Black, d3dDevice);

        // Draw status
        if (bCheatsEnabled) {
            draw::DrawTextA("[ Enabled ]", menuPosition.x + 7, menuPosition.y + 10, 140, 20, draw::color::Green, m_font);
        } else {
            draw::DrawTextA("[ Disabled ]", menuPosition.x + 7, menuPosition.y + 10, 140, 20, draw::color::LightGrey, m_font);
        }

        draw::DrawTextA("End to Eject", menuPosition.x + 12, menuPosition.y + 35, 140, 20, draw::color::LightGrey, m_font);
    } else {
        factor = 0.25;

        // Title Template
        draw::DrawFilledRect(30, 20, (int)(factor*140), (int)(factor*100), draw::color::DarkGrey, d3dDevice);
        draw::DrawBorderBox(30, 20, (int)(factor*140), (int)(factor*100), 2, draw::color::Black, d3dDevice);
    }

}

void render::CreateFont(LPDIRECT3DDEVICE9 pDevice, int size) {

    // Draw font
    D3DXCreateFont(
        pDevice,            // LPDIRECT3DDEVICE9 pDevice
        size,               // Height
        0,                  // Width
        FW_BOLD,            // Weight
        0,                  // MIP Levels
        false,              // Italic
        DEFAULT_CHARSET,    // Charset
        OUT_DEFAULT_PRECIS, // Precision
        DEFAULT_QUALITY,    // Quality
        DEFAULT_PITCH | FF_DONTCARE, // Pitch and Family
        "Arial",            // Font name
        &m_font             // LPD3DXFONT
    );
            
}
