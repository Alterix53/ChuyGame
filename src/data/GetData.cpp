#include <fstream>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

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
}