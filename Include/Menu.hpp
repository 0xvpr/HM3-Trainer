#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include <string>

#define PADDING   50
#define ITEM_SIZE 25

struct Item {
    std::string hotkey;
    std::string misc;
    bool bEnabled;
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

private:
    Position menuPosition;
    Resolution gameResolution;
public:
    std::map<std::string, Item> items = []{
        std::map<std::string, Item> temp;

        temp["NUM1 - Infinite Ammo"]   = Item{"NUM1", "", false };
        temp["NUM2 - Infinite Health"] = Item{"NUM2", "", false };
        temp["NUM3 - One Shot Kill"]   = Item{"NUM3", "", false };
        temp["NUM4 - No Reactions"]    = Item{"NUM4", "", false };
        temp["NUM5 - No Recoil"]       = Item{"NUM5", "", false };
        temp["NUM6 - Flash"]           = Item{"NUM6", "", false };
        temp["SHIFT+T - Teleport"]     = Item{"<Shift+T>", "", false };
        temp["T - Teleport to..."]     = Item{"<T>", "", false };

        return temp;
    }();
public:
    HackMenu(int x, int y) : menuPosition(Position{x, y}) {
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
};

#endif // MENU_HPP
