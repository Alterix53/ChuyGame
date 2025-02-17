#pragma once
#include <iostream>
#include <string>

enum class WeaponType {
	SWORD,
	BOW,
	DAGGER,
	AXE,
	BASEWEAPON // default weapon
};

class Weapon
{
public:
	Weapon();
	Weapon(std::string name, int damage, int cost, WeaponType type);
	~Weapon();

	std::string getName();
	void setDamage(int damage);	
	int getDamage();
	void setCost(int cost);
	int getCost();

	void printInfo() const;
protected:
	int _damage;
	int _cost;
	std::string _name;
	WeaponType _type;
};

// minh thieu doan tao ID cho weapon (vi khong biet co can thiet khong (va cung chua biet tao randomID khong bi trung(huhu)))