#include "WeaponManager.h"

WeaponManager::WeaponManager() = default;

WeaponManager::~WeaponManager() = default;

void WeaponManager::addWeapon(Weapon weapon) {
	_availableWeapons.push_back(weapon);
}

void WeaponManager::printAvailableWeapons() const {

	if (_availableWeapons.empty()) {
		std::cout << "No weapons are available!" << std::endl;
		return;
	}

	std::cout << "Available weapons for players: " << std::endl;
	for (int i = 0; i < _availableWeapons.size(); i++) {
		std::cout << "Weapon " << i + 1 << ": " << std::endl;
		_availableWeapons[i].printInfo();
	}

}

bool WeaponManager::getWeapon(Player& player, std::string weaponID) {

	for (int i = 0; i < _availableWeapons.size(); i++) {

		if (_availableWeapons[i].getName() != weaponID) {
			continue;
		}

		player.addWeapon(_availableWeapons[i]);
		return true;
	}

	std::cout << "Weapon is not available!" << std::endl;
	return false;
}