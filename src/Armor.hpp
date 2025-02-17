#pragma once
#include <iostream>
#include <string>

enum class ArmorPart{ // rat minecraft
	HELMET,
	CHESTPLATE,
	LEGGINGS,
	BOOTS
};

enum class ArmorType { // cai nay thi khong nhai nhe
	BULLETPROOF,
	CHAIN,
	LEATHER,
	PLATE
};

class Armor
{
private:
	std::string _name;
	ArmorType _type;
	ArmorPart _part;
	int _resistance;
	int _cost;
	std::string getArmorPartString();
	std::string getArmorTypeString();
public:

	// constructor and destructor
	Armor();
	Armor(std::string name, ArmorType type, ArmorPart part, int resistance, int cost);
	~Armor();

	// getter and setter
	std::string getName();
	ArmorType getType();
	ArmorPart getPart();
	int getResistance();
	int getCost();

	void printInfo();

};

