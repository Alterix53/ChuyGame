#include "Utils.hpp"

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
    
    void display(std::string name, int option) {
        std::vector<std::string> options = {"YES", "NO"};
        int width = std::min(Constants::List::Armor::NAME, int(name.length()) + 1);
        std::cout << A << std::string(width + 34, E) << B << std::endl;
        std::cout << F << " Are you sure you want to select: " << std::setw(width) << name << F << "\n";
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

    bool show(std::string name) {
        int option = 0;
        std::cout << "\n\n\n\n";
        while (true) {
            clearLines(6);
            display(name, option);
            
            char key = getch();
            if (key == 'a' || key == 'A' || key == 'd' || key == 'D') {
                option = (option == 0) ? 1 : 0;
            } else if (key == '\r' || key == '\n') {
                if (option == 0) {
                    return true;
                }
                return false;
            }
        }
    }
}