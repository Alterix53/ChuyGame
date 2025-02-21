#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include "Armor.hpp"
#include <vector>

#define MAX_WEAPON 2
#define WEAPON_INDEX 0

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
	int _points;		// cost to buy weapon
	int _weapIndex;		// shows the index of the weapon in the array
	// int _critRate;
	// int _critDmg;

	// player's inventory
	std::vector<Weapon> _inventoryWeapon;
	std::vector<Armor> _inventoryArmor;

public:
	// constructor and destructor
	Player();													// default constructor
	Player(std::string name, std::string ID, int points);		// constructor with parameters, contain basic player's info only
	Player(std::string name, std::string ID, int points, int health, int attack, int defense, int atkSpeed); // constructor with parameters, contain all player's info
	Player(const Player& player); // copy de chi khong biet
	~Player();

	// getter and setter
	void setPoint(int points);
	int getPoint();
	std::string getName();
	std::string getID();
	int getHealth();
	int getAttack();
	int getDefense();
	int getAtkSpeed();
	Weapon getWeapon(int index);
	Armor getArmor(ArmorPart part);
	// int getCritRate();
	// int getCritDmg();

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
	void printInfo();
	void printPlayerStat();					// only print stat
	void printPlayerInventory();			// shows inventory	
};