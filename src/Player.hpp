#pragma once
#include <iostream>
#include <string>
#include "Weapon.hpp"
#include <vector>

class Player
{
private:
	std::string _name;
	std::string _ID;
	std::vector <Weapon> _weapons;
	int _points; // to choose weapons
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