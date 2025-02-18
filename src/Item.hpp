#pragma once
#include <iostream>
#include <string>

class Item
{
protected:
	std::string _name;
	int _cost;
public:
	Item();
	Item(std::string name, int cost);
	~Item();

	// getter and setter
	std::string getName();
	int getCost();

	// print info
	void printInfo();
};

