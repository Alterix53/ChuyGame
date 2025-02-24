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
#include "Inventory.hpp" // shows inventory

using namespace Constants;

namespace Character {
    enum class Tab {
        CHARACTER,
        INVENTORY
    };

    enum class Slot {
        CHARACTER = 7,
        INVENTORY = 8,
        MAIN = 0,
        WEAPON1 = 1,
        WEAPON2 = 2,
        ARMOR1 = 3,
        ARMOR2 = 4,
        ARMOR3 = 5,
        ARMOR4 = 6
    };
    
    extern std::vector<std::string> sign;

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