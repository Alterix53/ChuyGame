#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"

// define the armor's base stat below
#define BASE_ARMOR_DEFENSE 10
#define BASE_ARMOR_HEALTH 1000

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
	// int _weight;

public:

	// constructor and destructor
	Armor();
	Armor(std::string name, ArmorType type, ArmorPart part, int health, int defense, int cost);
	~Armor();

	// getter and setter
	std::string getName();
	ArmorType getType();
	ArmorPart getPart();
	int getDefense();
	int getHealth();
	int getCost();

	// calculate the cost of the armor
	void calculateCost();		// base on hp and def

	// get the armor type and part string
	std::string getArmorPartString();
	std::string getArmorTypeString();

	// print the armor's info
	void printInfo();
	void printInfoInShort();
};