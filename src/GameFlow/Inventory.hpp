#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "../Player.hpp"
#include "../Utils.hpp"

// attribute of each box (box show an item)
const int itemsPerPage = 16;
const int itemsPerRow = 4;
const int itemsPerCol = 4;

using namespace utils::dialog;

namespace Inventory {
    // extern std::vector<std::string> items;

    // void addItem(const std::string& item);
    // void addWeapon(Player &player, const Weapon& weapon);
    // void addArmor(Player &player, const Armor& armor);
    // void removeWeapon(Player &player, const Weapon& weapon);
    // void removeArmor(Player &player, const Armor& armor);
    // bool hasWeapon(Player &player, const Weapon& weapon);
    // bool hasArmor(Player &player, const Armor& armor);
    void show(Player &player);
    void compareWeapon(Player &player, Weapon w1, Weapon w2);
    void compareArmor(Player &player, Armor a1, Armor a2); 
    std::vector<std::string> splitLines(const std::string& text);
    void displayInventory(std::vector<Item*> &items, Player &player, std::pair<int, int> inventoryPos, int pageNumber);
    void drawGrid(const std::vector<Item*>& data, int cols = 4, int rows = 4, int pageNumber = 1);
        // void listWeapons(Player &player);
    // void listArmors(Player &player);
    
}