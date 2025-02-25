#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"
#include <sstream>
#include <iomanip>

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
	float _atkSpeed;

	// phan loai cua weapon
	WeaponType _type;
public:
	Weapon();
	Weapon(std::string name, int cost, WeaponType type, int damage, float atkSpeed);
	~Weapon();

	// getter and setter
	void setDamage(int damage);	
	void setCost(int cost);
	void setAtkSpeed(float atkSpeed);

	std::string getName() const;
	int getDamage() const;
	float getAtkSpeed() const;
	int getCost() const;
	WeaponType getType() const;
	void setEquipped(bool Equipped);
	
	// get weapon type string
	std::string getWeaponTypeString() const;

	// override

	// calculate the cost of the weapon
	int calculateCost() override; // base on damage and atk speed

	// print info
	void printInfo() const override;
	void printInfoInShort() const override; // in thong tin tren 1 hang

	std::string toString() const override;
};