#include "Shop.hpp"

Shop::Shop() = default;

Shop::~Shop() = default;

void Shop::addWeaponToShop(Weapon weapon) {
	_availableWeapons.push_back(weapon);
}

void Shop::addArmorToShop(Armor armor) {
	_availableArmors.push_back(armor);
}

//void Shop::printAvailableWeapons() const {
//
//	if (_availableWeapons.empty()) {
//		std::cout << "No weapons are available!" << std::endl;
//		return;
//	}
//
//	std::cout << "Available weapons for players: " << std::endl;
//	for (int i = 0; i < _availableWeapons.size(); i++) {
//		std::cout << "Weapon " << i + 1 << ": " << std::endl;
//		//_availableWeapons[i].printInfo();
//	}
//
//}

void Shop::getWeapon(Player& player, std::string weaponName) {

	for (int i = 0; i < _availableWeapons.size(); i++) {

		if (_availableWeapons[i].getName() != weaponName) 
			continue;

		player.addWeapon(_availableWeapons[i]);
			return;
	}

	std::cout << "Weapon is not available!" << std::endl;
}

void Shop::getArmor(Player& player, std::string armorName) {
	for (int i = 0; i < _availableArmors.size(); i++) {

		if (_availableArmors[i].getName() != armorName)
			continue;

		player.addArmor(_availableArmors[i]);
		return;

	}

	std::cout << "Armor is not available!" << std::endl;
}