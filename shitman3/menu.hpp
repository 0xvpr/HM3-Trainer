#ifndef   MENU_HEADER
#define   MENU_HEADER

#include "toggle.hpp"

#include <d3d9.h>

#include <string>
#include <array>

namespace menu {

class item : private toggle::toggleable {
public:
    item() = delete;
    item(const std::string_view hotkey, const std::string_view text);
    virtual ~item() {}

    [[nodiscard]] inline const char* repr() const { return repr_.c_str(); }

    [[nodiscard]] virtual bool is_active() const;
    [[nodiscard]] virtual bool toggle() const;

private:
    const std::string repr_;
};

class menu : private toggle::toggleable {
    struct position {
        std::int16_t x;
        std::int16_t y;
        std::int16_t width;
        std::int16_t height;
    };

    struct resolution {
        std::int16_t width;
        std::int16_t height;
    };

    static constexpr uint32_t c_font_size = 20;
    static constexpr size_t c_item_height = 25;
    static constexpr size_t c_padding     = 50;

    menu(position&& position);

public:
    static menu* instance();
    static void shutdown();
    static bool is_initialized();

    menu() = delete;
    menu(menu&) = delete;
    menu(menu&&) = delete;

    virtual ~menu() {};

    [[nodiscard]] const auto& items()                       const { return items_; }
    [[nodiscard]] const item& operator[](std::size_t index) const { return items_[index]; }

    [[nodiscard]] constexpr inline int  x()                 const { return position_.x; }
    [[nodiscard]] constexpr inline int  y()                 const { return position_.y; }
    [[nodiscard]] constexpr inline int  menu_height()       const { return c_padding + (c_item_height * (sizeof(items_)/sizeof(item)) ); }
    [[nodiscard]] constexpr inline int  game_width()        const { return resolution_.height; }
    [[nodiscard]] constexpr inline int  game_height()       const { return resolution_.width; }
    [[nodiscard]]           inline bool is_maximized()      const { return maximized_.load(); }

    [[nodiscard]] virtual bool is_active() const;
    [[nodiscard]] virtual bool toggle() const;

    void render(LPDIRECT3DDEVICE9 d3dDevice) const;

private:
    static menu*              instance_;
    mutable std::atomic<bool> maximized_;
    position                  position_;
    resolution                resolution_;
    std::array<item, 10>      items_;
};

} // namespace menu

#endif // MENU_HEADER
