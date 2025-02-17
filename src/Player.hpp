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
	Armor _leggings;	// .  .  .   .  .   .  .   .  leggings
	Armor _boots;		// .  .  .   .  .   .  .   .  boots
	Armor _chestplate;	// .  .  .   .  .   .  .   .  chestplate

	// player's base stat
	int _health;
	int _attack;
	int _defense;
	int _points;		// cost to buy weapon
	int _weapIndex;		// shows the index of the weapon in the array

public:
	// constructor and destructor
	Player();													// default constructor
	Player(std::string name, std::string ID, int points);		// constructor with parameters	
	Player(const Player& player); // copy de chi khong biet
	~Player();

	// getter and setter
	void setPoint(int points);
	int getPoint();


	bool addWeapon(Weapon weapon);
	void printInfo() const;
};