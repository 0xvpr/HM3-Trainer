#include "render.hpp"

#include "drawing.hpp"
#include "menu.hpp"

#include <string>
#include <cstdio>

extern unsigned current_entity;
LPD3DXFONT m_font = nullptr;

void render::initialize_menu(LPDIRECT3DDEVICE9 device_ptr) {
    D3DDISPLAYMODE  d3dDisplayMode{};
    IDirect3DDevice9_GetDisplayMode(device_ptr, 0, &d3dDisplayMode);
}

void render::create_font(LPDIRECT3DDEVICE9 device_ptr, int size) {
    D3DXCreateFont(
        device_ptr,                   // LPDIRECT3DDEVICE9 device_ptr
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

void render::menu(LPDIRECT3DDEVICE9 d3dDevice, const hack_menu& menu) {
    D3DDISPLAYMODE  d3dDisplayMode{};
    float           factor{0};
    char            entity_buffer[32]{};

    // Get Resolution
    IDirect3DDevice9_GetDisplayMode(d3dDevice, 0, &d3dDisplayMode);

    // Draw Height
    memset(entity_buffer, 0, sizeof(entity_buffer));
    snprintf(entity_buffer, sizeof(entity_buffer), "Current Entity: %u", current_entity);
    draw::draw_text( entity_buffer,
                     static_cast<int>(menu.x()),
                     static_cast<int>(menu.y() - 25),
                     200,
                     20,
                     draw::color::light_grey,
                     m_font );

    if (menu.is_maximized()) {
        factor = 1.0;

        // Title Template
        draw::draw_filled_rect( static_cast<int>(menu.x()),
                                static_cast<int>(menu.y()),
                                240,
                                static_cast<int>(menu.menu_height()),
                                draw::color::dark_grey,
                                d3dDevice );
        draw::draw_border_box( static_cast<int>(menu.x()),
                               static_cast<int>(menu.y()),
                               240,
                               static_cast<int>(menu.menu_height()),
                               4,
                               draw::color::black,
                               d3dDevice );

        // Draw status
            draw::draw_text( (menu.is_active() ? "[ Hacks Enabled ]" : "[ Hacks Disabled ]"),
                              static_cast<int>(menu.x() + 7),
                              static_cast<int>(menu.y() + 10),
                              200,
                              20,
                              (menu.is_active() ? draw::color::green : draw::color::light_grey),
                              m_font );

        // Draw cheats
        int idx = 1;
        for (const auto& item : menu.items()) {
            draw::draw_text( item.c_str_repr(),
                             menu.x() + 12,
                             menu.y() + 12 + static_cast<int>(idx * 25),
                             200,
                             20,
                             (item.is_active() ? draw::color::green : draw::color::light_grey),
                             m_font );

            ++idx;
        }

        draw::draw_text( "HOME to Eject",
                         static_cast<int>(menu.x() + 12),
                         static_cast<int>(menu.y() + menu.menu_height() - 20),
                         200,
                         20,
                         draw::color::light_grey,
                         m_font );
    } else {
        factor = 0.25;

        // Title Template
        draw::draw_filled_rect( 30,
                                20,
                                (int)(factor*200),
                                (int)(factor*100),
                                draw::color::dark_grey,
                                d3dDevice );
        draw::draw_border_box( 30,
                               20,
                               (int)(factor*200),
                               (int)(factor*100),
                               2,
                               draw::color::black,
                               d3dDevice );
    }
}
