#pragma once
#include <string>
#include <vector>
#include "Weapon.hpp"
#include "Armor.hpp"
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include "Constants.hpp"
#include <cstdlib>  

using namespace Constants::Frame;

namespace utils {
    WeaponType stringToWeaponType(const std::string &typeStr);
    ArmorType stringToArmorType(const std::string &typeStr);
    ArmorPart stringToArmorPart(const std::string &partStr);
    std::string toLower(const std::string& str);
    bool startsWithIgnoreCase(const std::string& full, const std::string& prefix);
    std::string makeJsonWeapon(const Weapon &weapon);
    std::string makeJsonArmor(const Armor &armor);
    std::string colorString(std::string str, int color, int mode = 0);
    
    void clearScreen();

    namespace dialog {
        namespace Choice {
            void clearLastTwoLines();
            void clearLines(int n);
            void equip(std::string name, int option, bool isEquip);
            bool showEquip(std::string name, bool isEquip);
            void display(std::string name, int option);
            bool show(std::string name = "");
        }
    }
}
