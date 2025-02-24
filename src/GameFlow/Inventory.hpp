#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "../Player.hpp"

// attribute of each box (box show an item)
const int itemsPerPage = 16;
const int itemsPerRow = 4;
const int itemsPerCol = 4;

namespace Inventory {
    extern std::vector<std::string> items;

    void displayInventory(Player &player);
    void addItem(const std::string& item);
    // void addWeapon(Player &player, const Weapon& weapon);
    // void addArmor(Player &player, const Armor& armor);
    // void removeWeapon(Player &player, const Weapon& weapon);
    // void removeArmor(Player &player, const Armor& armor);
    // bool hasWeapon(Player &player, const Weapon& weapon);
    // bool hasArmor(Player &player, const Armor& armor);
    void show(Player &player);
    // void listWeapons(Player &player);
    // void listArmors(Player &player);
    
}