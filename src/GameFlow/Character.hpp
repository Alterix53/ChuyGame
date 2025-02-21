#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <functional>
#include <regex>
#include <algorithm>
#include <cctype>
#include "../Player.hpp"
#include "../Constants.hpp"
#include "../Utils.hpp"

using namespace Constants;

namespace Character {
    enum class Tab {
        CHARACTER,
        INVENTORY
    };

    enum class Slot {
        CHARACTER,
        INVENTORY,
        MAIN,
        WEAPON1,
        WEAPON2,
        ARMOR1,
        ARMOR2,
        ARMOR3,
        ARMOR4
    };

    std::string slotToString(Slot slot);
    std::string slotToStringUpper(Slot slot);
    std::string tabToString(Tab tab);
    std::string colorString(std::string str, int color);
    std::string colorString(const Slot &slot, int color, int mode = 0);
    void show(Player &player);   
    Slot goUp(const Slot &option);
    Slot goDown(const Slot &option);
    Slot goLeft(const Slot &option);
    Slot goRight(const Slot &option);
}