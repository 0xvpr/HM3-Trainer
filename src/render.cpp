#include "render.hpp"

#include "drawing.hpp"
#include "menu.hpp"

extern unsigned int current_entity;

extern bool bMaximizeMenu;
extern bool bCheatsEnabled;

extern LPD3DXFONT m_font;
extern LPD3DXFONT m_font_small;

HackMenu* menu;

HackMenu* render::InitializeMenu(LPDIRECT3DDEVICE9 pDevice) {
    D3DDISPLAYMODE  d3dDisplayMode;
    IDirect3DDevice9_GetDisplayMode(pDevice, 0, &d3dDisplayMode);

    menu = new HackMenu(30, 120);

    return menu;
}

void render::Menu(LPDIRECT3DDEVICE9 d3dDevice) {
    D3DDISPLAYMODE  d3dDisplayMode;
    float           factor;
    char            buffer[32];

    // Get Resolution
    IDirect3DDevice9_GetDisplayMode(d3dDevice, 0, &d3dDisplayMode);

    // Draw Height
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Current Entity: %u", current_entity);
    draw::DrawTextA(buffer, static_cast<int>(menu->X()), static_cast<int>(menu->Y() - 25), 200, 20, draw::color::LightGrey, m_font);

    if (bMaximizeMenu) {
        factor = 1.0;

        // Title Template
        draw::DrawFilledRect(static_cast<int>(menu->X()), static_cast<int>(menu->Y()), 240, static_cast<int>(menu->MenuHeight()), draw::color::DarkGrey, d3dDevice);
        draw::DrawBorderBox(static_cast<int>(menu->X()), static_cast<int>(menu->Y()), 240, static_cast<int>(menu->MenuHeight()), 4, draw::color::Black, d3dDevice);

        // Draw status
        if (bCheatsEnabled) {
            draw::DrawTextA("[ Hacks Enabled ]", static_cast<int>(menu->X() + 7), static_cast<int>(menu->Y() + 10), 200, 20, draw::color::Green, m_font);
        } else {
            draw::DrawTextA("[ Hacks Disabled ]", static_cast<int>(menu->X() + 7), static_cast<int>(menu->Y() + 10), 200, 20, draw::color::LightGrey, m_font);
        }

        // Draw Cheats
        int i = 1;
        for (const auto& [key, value] : menu->items) {
            draw::DrawTextA((value.hotkey + ": " + value.misc).c_str(), menu->X() + 12, menu->Y() + 12 + (i * 25), 200, 20, (value.bEnabled ? draw::color::Green : draw::color::LightGrey), m_font);
            ++i;
        }

        draw::DrawTextA("HOME to Eject", static_cast<int>(menu->X() + 12), static_cast<int>(menu->Y() + menu->MenuHeight() - 20), 200, 20, draw::color::LightGrey, m_font);
    } else {
        factor = 0.25;

        // Title Template
        draw::DrawFilledRect(30, 20, (int)(factor*200), (int)(factor*100), draw::color::DarkGrey, d3dDevice);
        draw::DrawBorderBox(30, 20, (int)(factor*200), (int)(factor*100), 2, draw::color::Black, d3dDevice);
    }

}

void render::CreateFont(LPDIRECT3DDEVICE9 pDevice, int size) {
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
