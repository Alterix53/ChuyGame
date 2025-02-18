#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"

enum class ArmorPart{ // rat minecraft
	HELMET,
	CHESTPLATE,
	LEGGINGS,
	BOOTS,
	BASE_ARMOR_PART
};

enum class ArmorType { // cai nay thi khong nhai nhe
	BULLETPROOF,
	CHAIN,
	LEATHER,
	PLATE,
	BASE_ARMOR_TYPE
};

class Armor : public Item
{
private:
	// phan loai
	ArmorType _type;
	ArmorPart _part;

	// thong so rieng cua armor
	int _defense;
	int _health;

public:

	// constructor and destructor
	Armor();
	Armor(std::string name, ArmorType type, ArmorPart part, int defense, int cost);
	~Armor();

	// getter and setter
	std::string getName();
	ArmorType getType();
	ArmorPart getPart();
	int getDefense();
	int getCost();

	// get the armor type and part string
	std::string getArmorPartString();
	std::string getArmorTypeString();

	void printInfo();
};