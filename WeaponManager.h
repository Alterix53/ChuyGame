#pragma once
#include <iostream>
#include <string>
#include "Weapon.h"
#include "Player.h"
#include <vector>

class WeaponManager
{
private:
	std::vector <Weapon> _availableWeapons;
public:
	WeaponManager();
	~WeaponManager();
	void addWeapon(Weapon weapon);
	void printAvailableWeapons() const;
	
	bool getWeapon(Player& player, std::string weaponID); // minh dinh tim theo ID nhung ma chua biet lam (minh troll)
};