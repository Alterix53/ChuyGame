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
