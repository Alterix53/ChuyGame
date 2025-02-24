#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include "Armor.hpp"
#include <vector>
#include <type_traits>
#include <conio.h>

#define MAX_WEAPON 2
#define WEAPON_INDEX 0

const int BaseCost = 5000; // anh ching thich bao nhieu tien? Chinh: 5 cu duoc khong ?

class Player
{
private:
	// player's info
	std::string _name;
	std::string _ID;

	// player's current equip weapon + armor
	Weapon _weapon[2];  // player's weapon, max 2 weapons
	Armor _helmet;		// this var only contains the helmet
	Armor _leggings;	// this var only contains the leggings
	Armor _boots;		// this var only contains the boots
	Armor _chestplate;	// this var only contains the chestplate

	// player's base stat
	int _health;
	int _attack;
	int _defense;
	int _atkSpeed;
	int _playerCost;		// cost to buy weapon
	int _weapIndex;		// shows the index of the weapon in the array
	// int _critRate;
	// int _critDmg;

	// player's inventory
	std::vector<Weapon> _inventoryWeapon;
	std::vector<Armor> _inventoryArmor;

public:
	// constructor and destructor
	Player();													// default constructor
	Player(std::string name, std::string ID, int cost);		// constructor with parameters, contain basic player's info only
	Player(std::string name, std::string ID, int cost, int health, int attack, int defense, int atkSpeed); // constructor with parameters, contain all player's info
	Player(const Player& player); // copy de chi khong biet
	~Player();

	// getter and setter
	void setPoint(int points);
	int getPoint() const;
	std::string getName() const;
	std::string getID() const;
	int getHealth() const;
	int getAttack() const;
	int getDefense() const;
	int getAtkSpeed() const;
	std::vector<Armor> getInventoryArmor() const;
	std::vector<Weapon> getInventoryWeapon() const;
	// int getCritRate();
	// int getCritDmg();
	Weapon getWeapon(int index) const;
	Armor getArmor(ArmorPart part) const;

	// adding weapon and armor to inventory
	void buyWeapon(Weapon weapon);				// buy and add weapon to player's inventory
	void buyArmor(Armor armor);					// buy and add armor to player's inventory

	// equip weapon and armor
	void equipWeapon(Weapon weapon);					// equip weapon from player's inventory
	void equipArmor(Armor armor);					// equip armor from player's inventory

	// unequipped weapon and armor
	void unequipWeapon(int index);				// unequip weapon from player's inventory
	void unequipArmor(ArmorPart part);			// unequip armor from player's inventory

	// update player's stat
	void updateStatEquipWeapon(Weapon weapon);		// update player's stat when equip an item
	void updateStatUnequipWeapon(Weapon weapon);		// update player's stat when unequip an item
	void updateStatEquipArmor(Armor armor);			// update player's stat when equip an item
	void updateStatUnequipArmor(Armor armor);		// update player's stat when unequip an item

	// print info
	void printInfo() const;
	void printPlayerStat() const;					// only print stat

	// print inventory
	void printPlayerInventory() const;			
};