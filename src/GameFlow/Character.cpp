#include "Character.hpp"

namespace Character {
    void show(Player player) {
        system("cls");
        std::vector<std::string> mainSlot = {
            "ID: " + player.getID(),
            "Name: " + player.getName(),
            "Health: " + std::to_string(player.getHealth()),
            "Attack: " + std::to_string(player.getAttack()),
            "Defense: " + std::to_string(player.getDefense())
        };
        std::vector<std::string> weaponSlot1 = {
            "Type: " + player.getWeapon(0).getWeaponTypeString(),
            "Name: " + player.getWeapon(0).getName(),
        };
        std::vector<std::string> weaponSlot2 = {
            "Type: " + player.getWeapon(1).getWeaponTypeString(),
            "Name: " + player.getWeapon(1).getName(),
        };
        std::cout << std::right << std::setw(40 + mainSlot[0].length()) << mainSlot[0] << std::endl;
        std::cout << std::right << std::setw(40 + mainSlot[1].length()) << mainSlot[1] << std::endl;
        std::cout << weaponSlot1[0] << std::setw(80) << weaponSlot2[0] << "\n";
        std::cout << std::left << std::setw(40) << weaponSlot1[1] << std::setw(40) << mainSlot[2] << weaponSlot2[1] << std::endl;
        std::cout << std::right << std::setw(40 + mainSlot[3].length()) << mainSlot[3] << std::endl;
        std::cout << std::right << std::setw(40 + mainSlot[4].length()) << mainSlot[4] << std::endl;
    }   
}