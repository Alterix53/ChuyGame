#include "Utils.hpp"

namespace utils {
    WeaponType stringToWeaponType(const std::string &typeStr) {
        if (typeStr == "Sword") return WeaponType::SWORD;
        if (typeStr == "Bow") return WeaponType::BOW;
        if (typeStr == "Dagger") return WeaponType::DAGGER;
        if (typeStr == "Axe") return WeaponType::AXE;
        throw std::invalid_argument("Invalid WeaponType: " + typeStr);
    }

    ArmorType stringToArmorType(const std::string &typeStr) {
        if (typeStr == "Bulletproof") return ArmorType::BULLETPROOF;
        if (typeStr == "Chain") return ArmorType::CHAIN;
        if (typeStr == "Leather") return ArmorType::LEATHER;
        if (typeStr == "Plate") return ArmorType::PLATE;
        if (typeStr == "Unknown") return ArmorType::BASE_ARMOR_TYPE;
        throw std::invalid_argument("Invalid ArmorType: " + typeStr);
    }

    ArmorPart stringToArmorPart(const std::string &partStr) {
        if (partStr == "Helmet") return ArmorPart::HELMET;
        if (partStr == "Chestplate") return ArmorPart::CHESTPLATE;
        if (partStr == "Leggings") return ArmorPart::LEGGINGS;
        if (partStr == "Boots") return ArmorPart::BOOTS;
        if (partStr == "Unknown") return ArmorPart::BASE_ARMOR_PART;
        throw std::invalid_argument("Invalid ArmorPart: " + partStr);
    }

    std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    bool startsWithIgnoreCase(const std::string& full, const std::string& prefix) {
        std::string fullLower = toLower(full);
        std::string prefixLower = toLower(prefix);
        return fullLower.substr(0, prefixLower.size()) == prefixLower;
    }

    std::string makeJsonWeapon(const Weapon &weapon) {
        std::string weaponJson = "{\"type\":\"" + weapon.getWeaponTypeString() + "\",\"name\":\"" + weapon.getName() + "\",\"damage\":" + std::to_string(weapon.getDamage()) + ", \"atkSpeed\": " + std::to_string(weapon.getAtkSpeed()) +  ", \"cost\": " + std::to_string(weapon.getCost()) + "}";
        return weaponJson;
    }

    std::string makeJsonArmor(const Armor &armor) {
        std::string armorJson = "{\"type\": \"" + armor.getArmorTypeString() + "\",\"name\":\"" + armor.getName() + "\", \"part\": \"" + armor.getArmorPartString() + "\",\"health\":" + std::to_string(armor.getHealth()) + ",\"defense\":" + std::to_string(armor.getDefense()) + ",\"weight\":" + std::to_string(armor.getWeight()) + ",\"cost\":" + std::to_string(armor.getCost()) + "}";
        return armorJson;
    }

    std::string colorString(std::string str, int color, int mode) {
        std::string string = "\033["+ std::to_string(mode) + ";" + std::to_string(color) + "m" + str + "\033[0m";
        return string;   
    }

    namespace dialog {
        namespace Choice {
            
            void clearLastTwoLines() {
                std::cout << "\033[A\033[2K";
                std::cout << "\033[A\033[2K"; 
                std::cout << "\r"; 
            }

            void clearLines(int n) {
                for (int i = 0; i < n; i++) {
                    std::cout << "\033[A\033[2K";
                }
                std::cout << "\r\n";
            }

            void equip(std::string name, int option, bool isEquip) {
                std::vector<std::string> options = {"YES", "NO"};
                int width = std::min(Constants::List::Armor::NAME, int(name.length()) + 1);
                int numberLines = !isEquip ? 23 : 25;
                int changed = numberLines - 24;
                
                std::cout << A << std::string(width + numberLines, E) << B << std::endl;
                if (!isEquip) {
                    std::cout << F << " Do you want to equip: " << std::left << std::setw(width) << name << F << "\n";
                } else {
                    std::cout << F << " Do you want to unequip: " << std::left << std::setw(width) << name << F << "\n";
                }
                std::cout << F << std::string(width + numberLines, ' ') << F << std::endl;
                std::cout << F;

                if (option == 0) {
                    std::cout << std::right << std::setw(24) << "\033[1;33m" + options[0] + "\033[0m";
                    std::cout << std::right << std::setw(11) << options[1];
                } else {
                    std::cout << std::right << std::setw(13) << options[0];
                    std::cout << std::right << std::setw(22) << "\033[1;33m" + options[1] + "\033[0m";
                }
                std::cout << std::string(width + changed, ' ') << F << std::endl;
                std::cout << D << std::string(width + numberLines, E) << C << std::endl;
            }
            
            bool showEquip(std::string name, bool isEquip) {
                int option = 0;
                std::cout << "\n\n\n\n\n\n\n";
                while (true) {
                    clearLines(6);
                    equip(name, option, isEquip);
                    
                    char key = getch();
                    if (key == -32) { 
                        key = _getch();
                    }
                    if (key == 'a' || key == 'A' || key == 'd' || key == 'D') {
                        option = (option == 0) ? 1 : 0;
                    } else if (key == 75 || key == 77) {
                        option = (option == 0) ? 1 : 0;
                    } else if (key == 27) {
                        clearLines(7);
                        return false;
                    } else if (key == '\r' || key == '\n') {
                        clearLines(7);
                        return option == 0; // 0: YES, 1: NO
                    }
                }
            }
            
            void display(std::string name, int option) {
                std::vector<std::string> options = {"YES", "NO"};
                int width = std::min(Constants::List::Armor::NAME, int(name.length()) + 1);
                std::cout << A << std::string(width + 34, E) << B << std::endl;
                std::cout << F << " Are you sure you want to select: " << std::left << std::setw(width) << name << F << "\n";
                std::cout << F << std::string(width + 34, ' ') << F << std::endl;
                std::cout << F;

                if (option == 0) {
                    std::cout << std::right << std::setw(26) << "\033[1;33m" + options[0] + "\033[0m";
                    std::cout << std::right << std::setw(15) << options[1];
                } else {
                    std::cout << std::right << std::setw(15) << options[0];
                    std::cout << std::right << std::setw(26) << "\033[1;33m" + options[1] + "\033[0m";
                }
                std::cout << std::string(width + 4, ' ') << F << std::endl;
                std::cout << D << std::string(width + 34, E) << C << std::endl;
            }

            /*
            * @param name: name of the item
            * @return true if the user choose YES, false if the user choose NO
            */
            bool show(std::string name) {
                int option = 0;
                std::cout << "\n\n\n\n\n\n\n";
                while (true) {
                    clearLines(6);
                    display(name, option);
                    
                    char key = getch();
                    if (key == -32) { 
                        key = _getch();
                    }
                    if (key == 'a' || key == 'A' || key == 'd' || key == 'D') {
                        option = (option == 0) ? 1 : 0;
                    } else if (key == 75 || key == 77) {
                        option = (option == 0) ? 1 : 0;
                    } else if (key == 27) {
                        clearLines(7);
                        return false;
                    } else if (key == '\r' || key == '\n') {
                        clearLines(7);
                        return option == 0; // 0: YES, 1: NO
                    }
                }
            }
        }
    }
}