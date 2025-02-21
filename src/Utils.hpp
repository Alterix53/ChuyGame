#pragma once
#include <string>
#include <vector>
#include "Weapon.hpp"
#include "Armor.hpp"
#include <conio.h>
#include <iomanip>
#include "Constants.hpp"

using namespace Constants::Frame;

WeaponType stringToWeaponType(const std::string &typeStr);
ArmorType stringToArmorType(const std::string &typeStr);
ArmorPart stringToArmorPart(const std::string &partStr);

namespace Choice {
    void clearLastTwoLines();
    void clearLines(int n);
    void display(std::string name, int option);
    bool show(std::string name = "");
}