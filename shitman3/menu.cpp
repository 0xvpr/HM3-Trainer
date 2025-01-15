#include "menu.hpp"

#include "drawing.hpp"

extern std::uint32_t current_entity;

menu::menu* menu::menu::instance_ = nullptr;

static LPD3DXFONT font_ = nullptr;

menu::item::item(const std::string_view hotkey, const std::string_view text)
: repr_( std::string(hotkey).append(": ").append(text) )
{
}

bool menu::item::is_active() const {
    return is_active_.load( std::memory_order_acquire );
} 

bool menu::item::toggle() const {
    auto old = is_active_.load( std::memory_order_acquire );
    while (!is_active_.compare_exchange_weak(old, !old));
    return is_active_;
}

void menu::menu::render(LPDIRECT3DDEVICE9 device_ptr) const {
    if (font_ == nullptr) {
        D3DXCreateFont(
            device_ptr,                   // LPDIRECT3DDEVICE9 device_ptr
            c_font_size,                  // Height
            0,                            // Width
            FW_BOLD,                      // Weight
            0,                            // MIP Levels
            false,                        // Italic
            DEFAULT_CHARSET,              // Charset
            OUT_DEFAULT_PRECIS,           // Precision
            DEFAULT_QUALITY,              // Quality
            DEFAULT_PITCH | FF_DONTCARE,  // Pitch and Family
            "Arial",                      // Font name
            &font_                        // LPD3DXFONT
        );
    }

    D3DDISPLAYMODE  d3d_display_mode{};
    float           factor{0};
    char            entity_buffer[32]{};

    // Get Resolution
    IDirect3DDevice9_GetDisplayMode(device_ptr, 0, &d3d_display_mode);

    // Draw Height
    memset(entity_buffer, 0, sizeof(entity_buffer));
    snprintf(entity_buffer, sizeof(entity_buffer), "Current Entity: %u", current_entity);
    draw::draw_text( entity_buffer,
                     static_cast<int>(x()),
                     static_cast<int>(y() - 25),
                     200,
                     20,
                     draw::color::light_grey,
                     font_ );

    if (is_maximized()) {
        factor = 1.0;

        // Title Template
        draw::draw_filled_rect( static_cast<int>(x()),
                                static_cast<int>(y()),
                                240,
                                static_cast<int>(menu_height()),
                                draw::color::dark_grey,
                                device_ptr );
        draw::draw_border_box( static_cast<int>(x()),
                               static_cast<int>(y()),
                               240,
                               static_cast<int>(menu_height()),
                               4,
                               draw::color::black,
                               device_ptr );

        // Draw status
        draw::draw_text( (is_active() ? "[ Hacks Enabled ]" : "[ Hacks Disabled ]"),
                          static_cast<int>(x() + 7),
                          static_cast<int>(y() + 10),
                          200,
                          20,
                          (is_active() ? draw::color::green : draw::color::light_grey),
                          font_ );

        // Draw cheats
        int idx = 1;
        for (const auto& item : items()) {
            draw::draw_text( item.repr(),
                             x() + 12,
                             y() + 12 + static_cast<int>(idx * 25),
                             200,
                             20,
                             (item.is_active() ? draw::color::green : draw::color::light_grey),
                             font_ );

            ++idx;
        }

        draw::draw_text( "HOME to Eject",
                         static_cast<int>(x() + 12),
                         static_cast<int>(y() + menu_height() - 20),
                         200,
                         20,
                         draw::color::light_grey,
                         font_ );
    } else {
        factor = 0.25;

        // Title Template
        draw::draw_filled_rect( 30,
                                20,
                                (int)(factor*200),
                                (int)(factor*100),
                                draw::color::dark_grey,
                                device_ptr );
        draw::draw_border_box( 30,
                               20,
                               (int)(factor*200),
                               (int)(factor*100),
                               2,
                               draw::color::black,
                               device_ptr );
    }
}

menu::menu* menu::menu::instance() {
    if (instance_ == nullptr) {
        instance_ = new menu( position{30, 120, 0 ,0} );
    }

    return instance_;
}

void menu::menu::shutdown() {
    if (instance_) {
        delete instance_;
    }
}

bool menu::menu::is_initialized() {
    return instance_ != nullptr;
}

bool menu::menu::is_active() const {
    return is_active_.load( std::memory_order_acquire );
} 

bool menu::menu::toggle() const {
    auto old = is_active_.load( std::memory_order_acquire );
    while (!is_active_.compare_exchange_weak(old, !old));
    return is_active_;
}

menu::menu::menu(menu::position&& p)
: maximized_  ( true )
, position_   ( p )
, resolution_ { }
, items_      { item{ "NUM1",    "Infinite Ammo"      },
                item{ "NUM2",    "Infinite Health"    },
                item{ "NUM3",    "One Shot Kill"      },
                item{ "NUM4",    "No Reactions"       },
                item{ "NUM5",    "No Recoil"          },
                item{ "NUM6",    "Flash"              },
//              item{ "NUM9",    "Disarm Everyone"    }, // busted, causes crashes
                item{ "Shift+T", "Teleport to Cam"    },
                item{ "Shift+X", "Kill Cam Target"    },
                item{ "T",       "Teleport to Target" },
                item{ "X",       "Kill Target"        } }
{
    // 0xDEADBEEF
}
