#ifndef MENU_HEADER
#define MENU_HEADER

#include <string>
#include <map>

#define PADDING   50
#define ITEM_SIZE 25

struct Item {
    std::string hotkey;
    std::string misc;
    bool bEnabled;
};

struct Position {
    unsigned x;
    unsigned y;
    unsigned width;
    unsigned height;
};

struct Resolution {
    unsigned width;
    unsigned height;
};

class HackMenu {
public:
    std::map<unsigned, Item> items = []() -> std::map<unsigned, Item> {
        std::map<unsigned, Item> temp;

        temp[ 0] = Item{"NUM1",    "Infinite Ammo",      false };
        temp[ 1] = Item{"NUM2",    "Infinite Health",    false };
        temp[ 2] = Item{"NUM3",    "One Shot Kill",      false };
        temp[ 3] = Item{"NUM4",    "No Reactions",       false };
        temp[ 4] = Item{"NUM5",    "No Recoil",          false };
        temp[ 5] = Item{"NUM6",    "Flash",              false };
        temp[ 6] = Item{"NUM9",    "Kill Everyone",      false };
        temp[ 7] = Item{"Shift+T", "Teleport to Cam",    false };
        temp[ 8] = Item{"Shift+X", "Kill Cam Target",    false };
        temp[ 9] = Item{"T",       "Teleport to Target", false };
        temp[10] = Item{"X",       "Kill Target",        false };

        return temp;
    }();
public:
    HackMenu(unsigned x, unsigned y) : menuPosition(Position{x, y, 0, 0}) {
        // 0xDEADBEEF
    }
    ~HackMenu() { }
public:
    inline unsigned X()          const { return menuPosition.x; }
    inline unsigned Y()          const { return menuPosition.y; }
    // inline unsigned MenuWidth()  const { return GetLongestHackSize(); } // TODO
    inline unsigned MenuHeight() const { return PADDING + ITEM_SIZE * items.size(); }
    inline unsigned GameWidth()  const { return gameResolution.height; }
    inline unsigned GameHeight() const { return gameResolution.width; }
public:
    // static std::string FormatHack(Item hack);
private:
    // unsigned GetLongestHackSize() const;
private:
    Position menuPosition;
    Resolution gameResolution;
};

#endif // MENU_HEADER
