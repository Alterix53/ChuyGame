#include "Data.hpp"

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

namespace WeaponData {
    json getWeapons() {
        std::ifstream file("data/weapons.json");
        if (!file) {
            std::cerr << "loi khi mo file weapons.json\n";
            return json{};
        }

        json data;
        file >> data;

        return data;
    }

    void loadData(std::vector<Weapon> &_availableWeapons) {
        json data = getWeapons();
        for (auto &weapon : data) {
            std::string name = weapon["name"];
            int cost = weapon["cost"];
            WeaponType type = stringToWeaponType(weapon["type"]);
            int damage = weapon["damage"];
            int atkSpeed = weapon["atkSpeed"];
            _availableWeapons.push_back(Weapon(name, cost, type, damage, atkSpeed));
        }
    }
}

namespace ArmorData {

    json getArmors() {
        std::ifstream file("data/armors.json");
        if (!file) {
            std::cerr << "loi khi mo file armors.json\n";
            return json{};
        }

        json data;
        file >> data;

        return data;
    }

    void loadData(std::vector<Armor> &_availableArmors) {
        json data = getArmors();
        for (auto &armor : data) {
            std::string name = armor["name"];
            ArmorType type = stringToArmorType(armor["type"]);
            ArmorPart part = stringToArmorPart(armor["part"]);
            int cost = armor["cost"];
            int health = armor["health"];
            int defense = armor["defense"];

            _availableArmors.push_back(Armor(name, type, part, defense, cost));
        }
    }
}