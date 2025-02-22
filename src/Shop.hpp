#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include "Player.hpp"
#include "Armor.hpp"
#include <vector>
#include <iomanip>
#include <conio.h>
#include "data/Data.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

#define ITEMS_PER_PAGE 15
#define SHOP_OPTION 3

using namespace Constants;
using namespace dialog;

enum class SHOP {
	WEAPONS,
	ARMORS,
	RETURN
};

class Shop
{
private:
	// vector to store available weapon and armor
	std::vector <Weapon> _availableWeapons;
	std::vector <Armor> _availableArmors;

	// index to display the current page
	int _currentItemWeaponIndex;
	int _firstItemWeaponIndex;
	int _currentItemArmorIndex;
	int _firstItemArmorIndex;

public:
	Shop();
	~Shop();

	// add more weapon and armor to shop
	void addWeaponToShop(Weapon weapon);
	void addArmorToShop(Armor armor);

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

	// display shop
	void displayShop(int opt);
	void runShop();
	void showWeaponShop();
	void showArmorShop();
	void printWeaponList(std::vector<Weapon> &list, int firstIndex, int endIndex, int currentIndex);			// print max 15 weapons
	void printArmorList(int firstIndex, int endIndex, int currentIndex);			// print max 15 armors
};