#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include "Armor.hpp"
#include <vector>

class Player
{
private:
	std::string _name;
	std::string _ID;

	// player's weapon + armor
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
	// int _critRate;
	// int _critDmg;
	int _points;		// cost to buy weapon
	int _weapIndex;		// shows the index of the weapon in the array

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

	// adding weapon and armor
	void updateStatEquipItem(Item item);		// update player's stat when equip an item
	void updateStatUnequipItem(Item item);		// update player's stat when unequip an item
	bool addWeapon(Weapon weapon);				// add weapon to player's inventory
	bool addArmor(Armor armor);					// add armor to player's inventory

	// print info
	void printInfo();
};