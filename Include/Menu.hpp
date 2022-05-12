#ifndef MENU_HPP
#define MENU_HPP

#include <unordered_map>
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
    std::unordered_map<std::string, Item> items = []{
        std::unordered_map<std::string, Item> temp;

        temp["God Mode"] = Item{"<F5>", "", false };
        temp["Teleport"] = Item{"<Shift+T>", "", false };

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