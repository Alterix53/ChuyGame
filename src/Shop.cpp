#include "Shop.hpp"

Shop::Shop() {
	WeaponData::loadData(this->_availableWeapons);
	ArmorData::loadData(this->_availableArmors);
}

Shop::~Shop() = default;

void Shop::addWeaponToShop(Weapon weapon) {
	_availableWeapons.push_back(weapon);
}

void Shop::buyArmorToShop(Armor armor) {
	_availableArmors.push_back(armor);
}

void Shop::printAvailableWeapons() {
	if (_availableWeapons.empty()) {
		std::cout << "No weapons are available!" << std::endl;
		return;
	}
	std::cout << "Available weapons for players: " << std::endl;
	std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(8) << "Damage";
	std::cout << std::right << std::setw(8) << "AtkSpeed" << std::right << std::setw(8) << "Cost" << std::endl;
	for (int i = 0; i < _availableWeapons.size(); i++) {
		std::cout << std::left << std::setw(20) << _availableWeapons[i].getName() << std::right << std::setw(8) << _availableWeapons[i].getDamage();
		std::cout << std::right << std::setw(8) << _availableWeapons[i].getAtkSpeed() << std::right << std::setw(8) << _availableWeapons[i].getCost() << std::endl;
	}
}

void Shop::printAvailableArmors() {
	if (_availableArmors.empty()) {
		std::cout << "No armors are available!" << std::endl;
		return;
	}

	std::cout << "Available armors for players: " << std::endl;
	std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(8) << "Defense";
	std::cout << std::right << std::setw(8) << "Defense" << std::right << std::setw(8) << "Cost" << std::endl;
	for (int i = 0; i < _availableArmors.size(); i++) {
		std::cout << std::left << std::setw(20) << _availableArmors[i].getName() << std::right << std::setw(8) << _availableArmors[i].getDefense();
		std::cout << std::right << std::setw(8) << _availableArmors[i].getDefense() << std::right << std::setw(8) << _availableArmors[i].getCost() << std::endl;
	}
}

void Shop::getWeapon(Player& player, std::string weaponName) {

	for (int i = 0; i < _availableWeapons.size(); i++) {

		if (_availableWeapons[i].getName() != weaponName) 
			continue;

		player.buyWeapon(_availableWeapons[i]);
			return;
	}

	std::cout << "Weapon is not available!" << std::endl;
}

void Shop::getArmor(Player& player, std::string armorName) {
	for (int i = 0; i < _availableArmors.size(); i++) {

		if (_availableArmors[i].getName() != armorName)
			continue;

		player.buyArmor(_availableArmors[i]);
		return;

	}

	std::cout << "Armor is not available!" << std::endl;
}

// the index is the current index in the vector
void Shop::getWeaponByIndex(Player& player, int index) {
	if (index < 0 || index >= _availableWeapons.size()) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	player.buyWeapon(_availableWeapons[index]);
}

void Shop::getArmorByIndex(Player& player, int index) {
	if (index < 0 || index >= _availableArmors.size()) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	player.buyArmor(_availableArmors[index]);
}

std::vector <Weapon> Shop::filterWeaponByType(WeaponType type) {
	std::vector <Weapon> filteredWeapons;
	for (int i = 0; i < _availableWeapons.size(); i++) {
		if (_availableWeapons[i].getType() == type) {
			filteredWeapons.push_back(_availableWeapons[i]);
		}
	}
	return filteredWeapons;
}

std::vector <Armor> Shop::filterArmorByType(ArmorType type) {
	std::vector <Armor> filteredArmors;
	for (int i = 0; i < _availableArmors.size(); i++) {
		if (_availableArmors[i].getType() == type) {
			filteredArmors.push_back(_availableArmors[i]);
		}
	}
	return filteredArmors;
}
