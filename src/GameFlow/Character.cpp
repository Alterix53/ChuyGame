#include "Character.hpp"

namespace Character {
    
    std::string slotToString(Slot slot) {
        switch (slot) {
            case Slot::CHARACTER: return "Character";
            case Slot::INVENTORY: return "Inventory";
            case Slot::MAIN: return "Main";
            case Slot::WEAPON1: return "Weapon1";
            case Slot::WEAPON2: return "Weapon2";
            case Slot::ARMOR1: return "Armor1";
            case Slot::ARMOR2: return "Armor2";
            case Slot::ARMOR3: return "Armor3";
            case Slot::ARMOR4: return "Armor4";
            default: return "Unknown";
        }
    }

    std::string tabToString(Tab tab) {
        switch (tab) {
            case Tab::CHARACTER: return "Character";
            case Tab::INVENTORY: return "Inventory";
            default: return "Unknown";
        }
    }

    void show(Player &player) {
        std::vector<std::string> tabs = {
            "Character",
            "Inventory"
        };
        std::vector<std::string> mainSlot = {
            "ID: " + player.getID(),
            "Name: " + player.getName(),
            "    ",
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

        Tab tab = Tab::CHARACTER;
        Slot option = Slot::WEAPON1;

        std::function<void()> display = [&]() -> void {
            std::cout << std::right << std::setw(space) << tabs[0] << std::setw(20) << tabs[1] << std::endl;
            std::cout << "\n\n";
            std::cout << std::right << std::setw(space + mainSlot[0].length() + 4) << "\033[1;31mMAIN\033[0m" << "\n\n";
            std::cout << std::right << std::setw(space + mainSlot[0].length()) << mainSlot[0] << std::endl;
            std::cout << std::left << std::setw(space + 11) << "\033[1;31mWEAPON 1\033[0m" << std::setw(space) << mainSlot[1] << "\033[1;31mWEAPON 2\033[0m" << std::endl; 
            std::cout << std::left << std::setw(space) << weaponSlot1[0] << std::setw(space) << mainSlot[2] << std::setw(space) << weaponSlot2[0] << "Current Tab: " << tabToString(tab) << std::endl;
            std::cout << std::left << std::setw(space) << weaponSlot1[1] << std::setw(space) << mainSlot[3] << std::setw(space) << weaponSlot2[1] << "Current Select: " << slotToString(option) << std::endl;
            std::cout << std::right << std::setw(space + mainSlot[4].length()) << mainSlot[4] << std::endl;
            std::cout << std::right << std::setw(space + mainSlot[5].length()) << mainSlot[5] << std::endl;
            std::cout << "\n\n";
            std::cout << std::left << std::setw(space + 11) <<  "\033[1;31mARMOR 1\033[0m" << std::setw(space + 11) << "\033[1;31mARMOR 2\033[0m" << std::setw(space + 11) << "\033[1;31mARMOR 3\033[0m" << std::setw(space) << "\033[1;31mARMOR 4\033[0m" << std::endl;
            std::cout << std::left << std::setw(space) << armorSlot1[0] << std::setw(space) << armorSlot2[0] << std::setw(space) << armorSlot3[0] << std::setw(space) << armorSlot4[0] << std::endl;
            std::cout << std::left << std::setw(space) << armorSlot1[1] << std::setw(space) << armorSlot2[1] << std::setw(space) << armorSlot3[1] << std::setw(space) << armorSlot4[1] << std::endl;
        };

        while (true) {
            system("cls");
            display();
            char key = getch();
            if (key == 'q' || key == 'Q' || int(key) == 27) { 
                return;
            } else if (key == 'w' || key == 'W') {
                if (tab == Tab::CHARACTER) {
                    option = goUp(option);
                }
            } else if (key == 's' || key == 'S') {
                if (tab == Tab::CHARACTER) {
                    option = goDown(option);
                }

            } else if (key == 'a' || key == 'A') {
                if (tab == Tab::CHARACTER) {
                    option = goLeft(option);
                }
            } else if (key == 'd' || key == 'D') {
                if (tab == Tab::CHARACTER) {
                    option = goRight(option);
                }
            }  else if (key == '\n' || key == '\r') {  // choose the current option
                break;
            }
        }
    }   

    Slot goUp(const Slot &option) {
        if (option == Slot::MAIN || option == Slot::WEAPON1 || option == Slot::WEAPON2) {
            return Slot::CHARACTER;
        }
        if (option == Slot::ARMOR1) {
            return Slot::WEAPON1;
        }
        if (option == Slot::ARMOR2 || option == Slot::ARMOR3) {
            return Slot::MAIN;
        }
        if (option == Slot::ARMOR4) {
            return Slot::WEAPON2;
        }
    }
    
    Slot goDown(const Slot &option) {
        if (option == Slot::CHARACTER) {
            return Slot::WEAPON1;
        }
        if (option == Slot::MAIN) {
            return Slot::ARMOR2;
        }
        if (option == Slot::WEAPON1) {
            return Slot::ARMOR1;
        }
        if (option == Slot::WEAPON2) {
            return Slot::ARMOR4;
        }
    }

    Slot goLeft(const Slot &option) {
        if (option == Slot::INVENTORY) {
            return Slot::CHARACTER;
        }
        if (option == Slot::MAIN) {
            return Slot::WEAPON1;
        }
        if (option == Slot::WEAPON2) {
            return Slot::MAIN;
        }
        if (option == Slot::ARMOR4) {
            return Slot::ARMOR3;
        }
        if (option == Slot::ARMOR3) {
            return Slot::ARMOR2;
        }
        if (option == Slot::ARMOR2) {
            return Slot::ARMOR1;
        }
    }
    
    Slot goRight(const Slot &option) {
        if (option == Slot::CHARACTER) {
            return Slot::INVENTORY;
        }
        if (option == Slot::MAIN) {
            return Slot::WEAPON2;
        }
        if (option == Slot::WEAPON1) {
            return Slot::MAIN;
        }
        if (option == Slot::ARMOR1) {
            return Slot::ARMOR2;
        }
        if (option == Slot::ARMOR2) {
            return Slot::ARMOR3;
        }
        if (option == Slot::ARMOR3) {
            return Slot::ARMOR4;
        }
    }
}