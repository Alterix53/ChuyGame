#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Player.hpp"
#include "Character.hpp"

using namespace Character;
// attribute of each box (box show an item)
const int itemsPerPage = 16;
const int itemsPerRow = 4;
const int itemsPerCol = 4;

namespace Inventory {
    static std::vector<std::string> items;
    
    static std::vector<Weapon> weapons;
    static std::vector<Armor> armors;

    // void displayInventory(Player &player);
    void addWeapon(Player &player, const Weapon& weapon);
    void addArmor(Player &player, const Armor& armor);
    void removeWeapon(Player &player, const Weapon& weapon);
    void removeArmor(Player &player, const Armor& armor);
    bool hasWeapon(Player &player, const Weapon& weapon);
    bool hasArmor(Player &player, const Armor& armor);
    void show(Player &player);
    // void listWeapons(Player &player);
    // void listArmors(Player &player);
    
}

#endif // INVENTORY_HPP