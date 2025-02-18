#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include "Player.hpp"
#include "Armor.hpp"
#include <vector>

class Shop
{
private:
	std::vector <Weapon> _availableWeapons;
	std::vector <Armor> _availableArmors;
public:
	Shop();
	~Shop();
	void addWeaponToShop(Weapon weapon);
	void addArmorToShop(Armor armor);

	// buy weapon by name
	void getWeapon(Player& player, std::string weaponName); // minh dinh tim theo ID nhung ma chua biet lam (minh troll)
	void getArmor(Player& player, std::string armorName); 

	// buy weapon by current index
	void getWeaponByIndex(Player& player, int index);
	void getArmorByIndex(Player& player, int index);
};