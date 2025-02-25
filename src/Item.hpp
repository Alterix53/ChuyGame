#pragma once
#include <iostream>
#include <string>

class Item
{
protected:
	std::string _name;
	int _cost;
	bool _isEquipped;
public:
	Item();
	Item(std::string name, int cost);
	virtual ~Item();

	// getter and setter
	std::string getName() const;
	int getCost() const;
	bool checkIsEquipped() const;
	void setEquipped(bool Equipped);

	// functions
	virtual int calculateCost() = 0;
	virtual void printInfo() const = 0;
	virtual void printInfoInShort() const = 0;
};