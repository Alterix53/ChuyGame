#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <functional>
#include <regex>
#include "../Player.hpp"
#include "../Constants.hpp"
#include "../Utils.hpp"

using namespace Constants::Frame;

namespace Character {
    enum class Tab {
        CHARACTER,
        INVENTORY
    };

    enum class Slot {
        MAIN,
        WEAPON1,
        WEAPON2,
        ARMOR1,
        ARMOR2,
        ARMOR3,
        ARMOR4
    };

    std::string slotToString(Slot slot);
    std::string tabToString(Tab tab);
    void show(Player &player);   
}