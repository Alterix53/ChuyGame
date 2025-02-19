#include "Item.hpp"

Item::Item() : _name("Unknown"), _cost(0) {}
Item::Item(std::string name, int cost) : _name(name), _cost(cost) {}
Item::~Item() {}

std::string Item::getName() {
	return _name;
}

int Item::getCost() {
	return _cost;
}

void Item::calculateCost() {
	// do nothing
}

void Item::printInfo() {
	std::cout << "Item's name: " << _name << std::endl;
	std::cout << "Cost: " << _cost << std::endl;
}