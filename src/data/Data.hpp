#pragma once
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include "../Weapon.hpp"
#include "../Armor.hpp"
#include <string>

using json = nlohmann::json;

WeaponType stringToWeaponType(const std::string &typeStr);
ArmorType stringToArmorType(const std::string &typeStr);
ArmorPart stringToArmorPart(const std::string &partStr);

namespace WeaponData {
    json getWeapons();
    void loadData(std::vector<Weapon> &_availableWeapons);
}

namespace ArmorData {
    json getArmors();
    void loadData(std::vector<Armor> &_availableArmors);
}