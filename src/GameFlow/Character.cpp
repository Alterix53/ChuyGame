#include "Character.hpp"

namespace Character {
    std::vector<std::string> sign = {
        "\033[0;33m" + slotToStringUpper(Slot::MAIN) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::WEAPON1) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::WEAPON2) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::ARMOR1) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::ARMOR2) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::ARMOR3) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::ARMOR4) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::CHARACTER) + "\033[0m",
        "\033[0;31m" + slotToStringUpper(Slot::INVENTORY) + "\033[0m",
    };
    
    std::string slotToString(Slot slot) {
        switch (slot) {
            case Slot::CHARACTER: return "Character";
            case Slot::INVENTORY: return "Inventory";
            case Slot::MAIN: return "Main";
            case Slot::WEAPON1: return "Weapon 1";
            case Slot::WEAPON2: return "Weapon 2";
            case Slot::ARMOR1: return "Armor 1";
            case Slot::ARMOR2: return "Armor 2";
            case Slot::ARMOR3: return "Armor 3";
            case Slot::ARMOR4: return "Armor 4";
            default: return "Unknown";
        }
    }

    std::string slotToStringUpper(Slot slot) {
        std::string string = slotToString(slot);
        std::transform(string.begin(), string.end(), string.begin(), ::toupper);
        return string;
    }

    std::string tabToString(Tab tab) {
        switch (tab) {
            case Tab::CHARACTER: return "Character";
            case Tab::INVENTORY: return "Inventory";
            default: return "Unknown";
        }
    }

    std::string colorString(std::string str, int color) {
        return "\033[1;" + std::to_string(color) + "m" + str + "\033[0m";
    }

    std::string colorString(const Slot &slot, int color, int mode) {
        std::string str = slotToStringUpper(slot);
        std::string string = "\033["+ std::to_string(mode) + ";" + std::to_string(color) + "m" + str + "\033[0m";
        return string;   
    }
    void show(Player &player) {
        Tab tab = Tab::CHARACTER;
        Slot option = Slot::MAIN;

        std::vector<std::string> mainSlot = {}, weaponSlot1 = {}, weaponSlot2 = {},
         armorSlot1 = {}, armorSlot2 = {}, armorSlot3 = {}, armorSlot4 = {};

        std::function<void()> inital = [&]() -> void {
            std::vector<std::string> tabs = {
                "Character",
                "Inventory" 
            };
            mainSlot = {
                "ID: " + player.getID(),
                "Name: " + player.getName(),
                "    ",
                "Health: " + std::to_string(player.getHealth()),
                "Attack: " + std::to_string(player.getAttack()),
                "Defense: " + std::to_string(player.getDefense())
            };
            weaponSlot1 = {
                "Type: " + player.getFirstWeapon().getWeaponTypeString(),
                "Name: " + player.getFirstWeapon().getName(),
            };    
            weaponSlot2 = {
                "Type: " + player.getSecondWeapon().getWeaponTypeString(),
                "Name: " + player.getSecondWeapon().getName(),
            };
            armorSlot1 = {
                "part: " + player.getArmor(ArmorPart::HELMET).getArmorPartString(),
                "Name: " + player.getArmor(ArmorPart::HELMET).getName(),
            };
            armorSlot2 = {
                "part: " + player.getArmor(ArmorPart::CHESTPLATE).getArmorPartString(),
                "Name: " + player.getArmor(ArmorPart::CHESTPLATE).getName(),
            };
            armorSlot3 = {
                "part: " + player.getArmor(ArmorPart::LEGGINGS).getArmorPartString(),
                "Name: " + player.getArmor(ArmorPart::LEGGINGS).getName(),
            };
            armorSlot4 = {
                "part: " + player.getArmor(ArmorPart::BOOTS).getArmorPartString(),
                "Name: " + player.getArmor(ArmorPart::BOOTS).getName(),
            };
        };

        std::function<void()> display = [&]() -> void {
            std::cout << std::right << std::setw(Frame::space + 11) << sign[int(Slot::CHARACTER)] << std::setw(Frame::space) << sign[int(Slot::INVENTORY)] << std::endl;
            std::cout << "\n\n";
            std::cout << std::right << std::setw(Frame::space + mainSlot[0].length() + 4) << sign[int(Slot::MAIN)] << "\n\n";
            std::cout << std::right << std::setw(Frame::space + mainSlot[0].length()) << mainSlot[0] << std::endl;
            std::cout << std::left << std::setw(Frame::space + 11) << sign[int(Slot::WEAPON1)] << std::setw(Frame::space) << mainSlot[1] << sign[int(Slot::WEAPON2)] << std::endl; 
            std::cout << std::left << std::setw(Frame::space) << weaponSlot1[0] << std::setw(Frame::space) << mainSlot[2] << std::setw(Frame::space) << weaponSlot2[0] << "Current Tab: " << tabToString(tab) << std::endl;
            std::cout << std::left << std::setw(Frame::space) << weaponSlot1[1] << std::setw(Frame::space) << mainSlot[3] << std::setw(Frame::space) << weaponSlot2[1] << "Current Select: " <<  colorString(option, 33, 0) << std::endl;
            std::cout << std::right << std::setw(Frame::space + mainSlot[4].length()) << mainSlot[4] << std::endl;
            std::cout << std::right << std::setw(Frame::space + mainSlot[5].length()) << mainSlot[5] << std::endl;
            std::cout << "\n\n";
            std::cout << std::left << std::setw(Frame::space + 11) <<  sign[int(Slot::ARMOR1)] << std::setw(Frame::space + 11) << sign[int(Slot::ARMOR2)] << std::setw(Frame::space + 11) << sign[int(Slot::ARMOR3)] << std::setw(Frame::space) << sign[int(Slot::ARMOR4)] << std::endl;
            std::cout << std::left << std::setw(Frame::space) << armorSlot1[0] << std::setw(Frame::space) << armorSlot2[0] << std::setw(Frame::space) << armorSlot3[0] << std::setw(Frame::space) << armorSlot4[0] << std::endl;
            std::cout << std::left << std::setw(Frame::space) << armorSlot1[1] << std::setw(Frame::space) << armorSlot2[1] << std::setw(Frame::space) << armorSlot3[1] << std::setw(Frame::space) << armorSlot4[1] << std::endl;
            std::cout << "\n\n\n";
            std::cout << std::right << std::setw(Frame::space * 2) << "Press ESC or Q to exit" << std::endl;
        };

        bool move = false;

        while (true) {
            system("cls");
            inital();
            display();
            char key = getch();
            if (key == 'q' || key == 'Q' || int(key) == 27) { 
                saveSlotSign();
                return;
            } else if (key == 'w' || key == 'W') {
                move = true;
                if (tab == Tab::CHARACTER) {
                    option = goUp(option);
                }
            } else if (key == 's' || key == 'S') {
                move = true;
                if (tab == Tab::CHARACTER) {
                    option = goDown(option);
                }

            } else if (key == 'a' || key == 'A') {
                move = true;
                if (tab == Tab::CHARACTER) {
                    option = goLeft(option);
                }
            } else if (key == 'd' || key == 'D') {
                move = true;
                if (tab == Tab::CHARACTER) {
                    option = goRight(option);
                }
            }  else if (key == '\n' || key == '\r') {  // choose the current option

                // TODO: implement the action for each option
                if (option == Slot::CHARACTER) {
                    tab = Tab::CHARACTER;
                } else if (option == Slot::INVENTORY) {
                    tab = Tab::INVENTORY;
                    Inventory::show(player);

                    tab = Tab::CHARACTER;
                    option = Slot::MAIN;
                } 
            } else {
                move = false;
            }
            if (move){ 
                sign[int(option)] = colorString(option, 33, 1);
                for (int i = 0; i < sign.size(); i++) {
                    if (i != int(option)) {
                        sign[i] = colorString(Slot(i), 31, 0);
                    }
                }
            }
        }
    }   

    void saveSlotSign() {
        sign = {
            "\033[0;33m" + slotToStringUpper(Slot::MAIN) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::WEAPON1) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::WEAPON2) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::ARMOR1) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::ARMOR2) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::ARMOR3) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::ARMOR4) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::CHARACTER) + "\033[0m",
            "\033[0;31m" + slotToStringUpper(Slot::INVENTORY) + "\033[0m",
        };
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