#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"

// define the armor's base stat below
#define BASE_ARMOR_DEFENSE 10
#define BASE_ARMOR_HEALTH 1000
#define BASE_ARMOR_WEIGHT 0

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
	int _weight; // decrease the player's speed
public:

	// constructor and destructor
	Armor();
	Armor(std::string name, ArmorType type, ArmorPart part, int health, int defense, int weight, int cost);
	~Armor();

	// getter and setter
	std::string getName() const;
	ArmorType getType() const;
	ArmorPart getPart() const;
	int getDefense() const;
	int getHealth() const;
	int getCost() const;
	int getWeight() const;
	
	// get the armor type and part string
	std::string getArmorPartString() const;
	std::string getArmorTypeString() const;

	// override

	// calculate the cost of the armor
	int calculateCost() override;		// base on hp and def
	
	// print the armor's info
	void printInfo() const override;
	void printInfoInShort() const override;
};