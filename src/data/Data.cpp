#include "Data.hpp"

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
            int health = armor["health"];
            int defense = armor["defense"];
            int cost = armor["cost"];

            _availableArmors.push_back(Armor(name, type, part, health, defense, cost));
        }
    }
}