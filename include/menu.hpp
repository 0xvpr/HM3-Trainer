#ifndef MENU_HEADER
#define MENU_HEADER

#include <array>

#define PADDING   50
#define ITEM_SIZE 25

struct Item {
    bool bEnabled;
    char hotkey[64];
    char misc[64];
    bool toggle() {
        bEnabled = !bEnabled;

        return bEnabled;
    }
};

struct Position {
    int x;
    int y;
    int width;
    int height;
};

struct Resolution {
    int width;
    int height;
};

class HackMenu {
public:
    std::array<Item, 10> items = {
        Item{ false, "NUM1",    "Infinite Ammo"      },
        Item{ false, "NUM2",    "Infinite Health"    },
        Item{ false, "NUM3",    "One Shot Kill"      },
        Item{ false, "NUM4",    "No Reactions"       },
        Item{ false, "NUM5",    "No Recoil"          },
        Item{ false, "NUM6",    "Flash"              },
/*      Item{ false, "NUM9",    "Disarm Everyone"    }, */ // busted, causes crashes
        Item{ false, "Shift+T", "Teleport to Cam"    },
        Item{ false, "Shift+X", "Kill Cam Target"    },
        Item{ false, "T",       "Teleport to Target" },
        Item{ false, "X",       "Kill Target"        }
    };
public:
    HackMenu() = delete;
    HackMenu(HackMenu&) = delete;
    HackMenu(HackMenu&&) = delete;
    HackMenu(Position&& position)
      : menuPosition(position)
    {
        // 0xDEADBEEF
    }
    ~HackMenu() { }
public:
    inline int X()          const { return menuPosition.x; }
    inline int Y()          const { return menuPosition.y; }
    // inline int MenuWidth()  const { return GetLongestHackSize(); } // TODO
    inline int MenuHeight() const { return PADDING + ITEM_SIZE * sizeof(items)/sizeof(Item); }
    inline int GameWidth()  const { return gameResolution.height; }
    inline int GameHeight() const { return gameResolution.width; }
public:
    // static std::string FormatHack(Item hack);
private:
    // int GetLongestHackSize() const;
private:
    Position menuPosition;
    Resolution gameResolution;
};

#endif // MENU_HEADER
