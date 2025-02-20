#pragma once
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <string>
#include "../Weapon.hpp"
#include "../Armor.hpp"
#include "../Utils.hpp"

using json = nlohmann::json;

namespace WeaponData {
    json getWeapons();
    void loadData(std::vector<Weapon> &_availableWeapons);
}

namespace ArmorData {
    json getArmors();
    void loadData(std::vector<Armor> &_availableArmors);
}