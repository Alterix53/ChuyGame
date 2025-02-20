#pragma once
#include <string>
#include "Weapon.hpp"
#include "Armor.hpp"

WeaponType stringToWeaponType(const std::string &typeStr);
ArmorType stringToArmorType(const std::string &typeStr);
ArmorPart stringToArmorPart(const std::string &partStr);