#include "Character.hpp"

namespace Character {
    void display(Player &player) {
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
        std::vector<std::string> armorSlot1 = {
            "Type: " + player.getArmor(ArmorPart::HELMET).getArmorTypeString(),
            "Name: " + player.getArmor(ArmorPart::HELMET).getName(),
        };
        std::vector<std::string> armorSlot2 = {
            "Type: " + player.getArmor(ArmorPart::CHESTPLATE).getArmorTypeString(),
            "Name: " + player.getArmor(ArmorPart::CHESTPLATE).getName(),
        };
        std::vector<std::string> armorSlot3 = {
            "Type: " + player.getArmor(ArmorPart::LEGGINGS).getArmorTypeString(),
            "Name: " + player.getArmor(ArmorPart::LEGGINGS).getName(),
        };
        std::vector<std::string> armorSlot4 = {
            "Type: " + player.getArmor(ArmorPart::BOOTS).getArmorTypeString(),
            "Name: " + player.getArmor(ArmorPart::BOOTS).getName(),
        };

        std::cout << std::right << std::setw(space + mainSlot[0].length()) << mainSlot[0] << std::endl;
        std::cout << std::right << std::setw(space + mainSlot[1].length()) << mainSlot[1] << std::endl;
        std::cout << weaponSlot1[0] << std::setw(2 * space) << weaponSlot2[0] << "\n";
        std::cout << std::left << std::setw(space) << weaponSlot1[1] << std::setw(space) << mainSlot[2] << weaponSlot2[1] << std::endl;
        std::cout << std::right << std::setw(space + mainSlot[3].length()) << mainSlot[3] << std::endl;
        std::cout << std::right << std::setw(space + mainSlot[4].length()) << mainSlot[4] << std::endl;
        std::cout << "\n\n\n";
        std::cout << std::left << std::setw(space) << armorSlot1[0] << std::setw(space) << armorSlot2[0] << std::setw(space) << armorSlot3[0] << std::setw(space) << armorSlot4[0] << std::endl;
        std::cout << std::left << std::setw(space) << armorSlot1[1] << std::setw(space) << armorSlot2[1] << std::setw(space) << armorSlot3[1] << std::setw(space) << armorSlot4[1] << std::endl;
    }
    
    void show(Player &player) {
        system("cls");
        display(player);
    }   
}