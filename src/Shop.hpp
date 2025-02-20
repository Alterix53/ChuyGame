#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include "Player.hpp"
#include "Armor.hpp"
#include <vector>
#include <algorithm>
#include <iomanip>

class Shop
{
private:
	std::vector <Weapon> _availableWeapons;
	std::vector <Armor> _availableArmors;
public:
	Shop();
	~Shop();

	// add more weapon and armor to shop
	void addWeaponToShop(Weapon weapon);
	void buyArmorToShop(Armor armor);

	// print available weapon and armor
	void printAvailableWeapons();
	void printAvailableArmors();

	// sort weapon and armor by cost
	// void sortWeaponByCost();
	// void sortArmorByCost();

	// filter the weapon and armor by type
	std::vector <Weapon> filterWeaponByType(WeaponType type);
	std::vector <Armor> filterArmorByType(ArmorType type);

	// buy weapon by name
	void getWeapon(Player& player, std::string weaponName); // minh dinh tim theo ID nhung ma chua biet lam (minh troll)
	void getArmor(Player& player, std::string armorName); 

	// buy weapon by current index
	void getWeaponByIndex(Player& player, int index);
	void getArmorByIndex(Player& player, int index);

};