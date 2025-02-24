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
	virtual ~Item();

	// getter and setter
	std::string getName() const;
	int getCost() const;

	// functions
	virtual void calculateCost() = 0;
	virtual void printInfo() const = 0;
	virtual void printInfoInShort() const = 0;
};