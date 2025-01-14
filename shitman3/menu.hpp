#ifndef MENU_HEADER
#define MENU_HEADER

#include <sstream>

#include <memory>
#include <atomic>
#include <array>

static constexpr size_t c_item_height = 25;
static constexpr size_t c_padding     = 50;

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

class toggleable {
    [[nodiscard]] virtual bool is_active() const = 0;
    [[nodiscard]] virtual bool toggle()    const = 0;
};

class Item : private toggleable {
public:
    Item() = delete;
    Item(const std::string_view hotkey, const std::string_view text)
    : is_active_ ( false   )
    , hotkey_    ( hotkey )
    , text_      ( text   )
    , repr_      { '(', 'n', 'u', 'l', 'l', ')', 0 }
    {
        std::stringstream ss;
        ss << hotkey << ": " << text;

        if ( sizeof(repr_) > ss.str().size() ) {
            memcpy( repr_,
                    ss.str().c_str(),
                    ss.str().size() );
            repr_[sizeof(repr_)-1] = 0;
        }
    }

    virtual ~Item() {}

    const char* c_str_repr() const {
        return repr_;
    }

    [[nodiscard]] virtual bool is_active() const {
        return is_active_.load( std::memory_order_acquire );
    } 
    [[nodiscard]] virtual bool toggle() const {
        auto old = is_active_.load( std::memory_order_acquire );
        while (!is_active_.compare_exchange_weak(old, !old));
        return is_active_;
    }


private:
    mutable std::atomic<bool> is_active_;
    const std::string_view    hotkey_;
    const std::string_view    text_;
    char                      repr_[64];
};

class hack_menu : private toggleable {
public:
    static hack_menu* instance() {
        if (instance_ == nullptr) {
            instance_ = new hack_menu( position{30, 120, 0 ,0} );
        }

        return instance_;
    }

    static void shutdown() {
        if (instance_) {
            delete instance_;
        }
    }

    static bool is_initialized() { return instance_ != nullptr; }

    hack_menu() = delete;
    hack_menu(hack_menu&) = delete;
    hack_menu(hack_menu&&) = delete;
    virtual ~hack_menu() {};

    [[nodiscard]] const auto& items()                       const { return items_; }
    [[nodiscard]] const Item& operator[](std::size_t index) const { return items_[index]; }

    [[nodiscard]] constexpr inline int  x()                 const { return position_.x; }
    [[nodiscard]] constexpr inline int  y()                 const { return position_.y; }
    [[nodiscard]] constexpr inline int  menu_height()       const { return c_padding + (c_item_height * (sizeof(items_)/sizeof(Item)) ); }
    [[nodiscard]] constexpr inline int  game_width()        const { return resolution_.height; }
    [[nodiscard]] constexpr inline int  game_height()       const { return resolution_.width; }
    [[nodiscard]] inline bool is_maximized()                const { return maximized_.load(); }

    [[nodiscard]] virtual bool is_active() const {
        return is_active_.load( std::memory_order_acquire );
    } 
    [[nodiscard]] virtual bool toggle() const {
        auto old = is_active_.load( std::memory_order_acquire );
        while (!is_active_.compare_exchange_weak(old, !old));
        return is_active_;
    }

    hack_menu(position&& position)
    : position_    ( position )
    , maximized_   ( true )
    , is_active_   ( false )
    {
        // 0xDEADBEEF
    }

private:
    static hack_menu* instance_;

    std::array<Item, 10> items_ = {
        Item{ "NUM1",    "Infinite Ammo"      },
        Item{ "NUM2",    "Infinite Health"    },
        Item{ "NUM3",    "One Shot Kill"      },
        Item{ "NUM4",    "No Reactions"       },
        Item{ "NUM5",    "No Recoil"          },
        Item{ "NUM6",    "Flash"              },
//      Item{ "NUM9",    "Disarm Everyone"    }, // busted, causes crashes
        Item{ "Shift+T", "Teleport to Cam"    },
        Item{ "Shift+X", "Kill Cam Target"    },
        Item{ "T",       "Teleport to Target" },
        Item{ "X",       "Kill Target"        }
    };

    position                         position_;
    resolution                       resolution_;

    mutable std::atomic<bool>        maximized_;
    mutable std::atomic<bool>        is_active_;
};

#endif // MENU_HEADER
