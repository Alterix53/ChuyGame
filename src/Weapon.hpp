#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"


enum class WeaponType {
	SWORD,
	BOW,
	DAGGER,
	AXE,
	BASEWEAPON // default weapon
};

class Weapon : public Item
{
private:

	// weapon's only stat
	int _damage;
	int _atkSpeed;

	// phan loai cua weapon
	WeaponType _type;
public:
	Weapon();
	Weapon(std::string name, int cost, WeaponType type, int damage, int atkSpeed);
	~Weapon();

	// getter and setter
	std::string getName();
	void setDamage(int damage);	
	int getDamage();
	int getAtkSpeed();
	void setCost(int cost);
	int getCost();
	WeaponType getType();

	// print info
	void printInfo();

	// get weapon type string
	std::string getWeaponTypeString();
};