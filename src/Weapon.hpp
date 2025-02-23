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
	void setDamage(int damage);	
	void setCost(int cost);

	std::string getName() const;
	int getDamage() const;
	int getAtkSpeed() const;
	int getCost() const;
	WeaponType getType() const;

	// get weapon type string
	std::string getWeaponTypeString() const;

	// override

	// calculate the cost of the weapon
	void calculateCost() override; // base on damage and atk speed

	// print info
	void printInfo() const override;
	void printInfoInShort() const override; // in thong tin tren 1 hang
};