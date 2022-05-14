#include "Render.hpp"

#include "Menu.hpp"
#include "Drawing.hpp"
#include <stdio.h>

extern bool bMaximizeMenu;
extern bool bCheatsEnabled;

extern LPD3DXFONT m_font;
extern LPD3DXFONT m_font_small;

HackMenu* menu;

void render::InitializeMenu(LPDIRECT3DDEVICE9 pDevice) {

    D3DDISPLAYMODE  d3dDisplayMode;
    IDirect3DDevice9_GetDisplayMode(pDevice, 0, &d3dDisplayMode);

    menu = new HackMenu(30, 120);

}

void render::Menu(LPDIRECT3DDEVICE9 d3dDevice) {

    D3DDISPLAYMODE  d3dDisplayMode;
    float           factor;
    char            buffer[32];

    // Get Resolution
    IDirect3DDevice9_GetDisplayMode(d3dDevice, 0, &d3dDisplayMode);

    // Draw Height
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Height: %u", d3dDisplayMode.Height);
    draw::DrawTextA(buffer, menu->X(), menu->Y() - 25, 140, 20, draw::color::LightGrey, m_font);

    // Draw Width
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Width: %u", d3dDisplayMode.Width);
    draw::DrawTextA(buffer, menu->X() + 140, menu->Y() - 25, 140, 20, draw::color::LightGrey, m_font);

    if (bMaximizeMenu) {
        factor = 1.0;

        // Title Template
        draw::DrawFilledRect(menu->X(), menu->Y(), 140, menu->MenuHeight(), draw::color::DarkGrey, d3dDevice);
        draw::DrawBorderBox(menu->X(), menu->Y(), 140, menu->MenuHeight(), 4, draw::color::Black, d3dDevice);

        // Draw status
        if (bCheatsEnabled) {
            draw::DrawTextA("[ Enabled ]", menu->X() + 7, menu->Y() + 10, 140, 20, draw::color::Green, m_font);
        } else {
            draw::DrawTextA("[ Disabled ]", menu->X() + 7, menu->Y() + 10, 140, 20, draw::color::LightGrey, m_font);
        }

        // Draw Cheats
        int i = 1;
        for (const auto& [key, value] : menu->items) {
            draw::DrawTextA(key.c_str(), menu->X() + 12, menu->Y() + 12 + (i * 25), 140, 20, (value.bEnabled ? draw::color::Green : draw::color::LightGrey), m_font);
            ++i;
        }

        draw::DrawTextA("End to Eject", menu->X() + 12, menu->Y() + menu->MenuHeight() - 20, 140, 20, draw::color::LightGrey, m_font);
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
        pDevice,                      // LPDIRECT3DDEVICE9 pDevice
        size,                         // Height
        0,                            // Width
        FW_BOLD,                      // Weight
        0,                            // MIP Levels
        false,                        // Italic
        DEFAULT_CHARSET,              // Charset
        OUT_DEFAULT_PRECIS,           // Precision
        DEFAULT_QUALITY,              // Quality
        DEFAULT_PITCH | FF_DONTCARE,  // Pitch and Family
        "Arial",                      // Font name
        &m_font                       // LPD3DXFONT
    );
            
}
