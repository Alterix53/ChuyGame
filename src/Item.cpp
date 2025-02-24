#include "Item.hpp"

Item::Item() : _name("Unknown"), _cost(0) {}
Item::Item(std::string name, int cost) : _name(name), _cost(cost) {}
Item::~Item() {}

std::string Item::getName() const {
	return _name;
}

int Item::getCost() const {
	return _cost;
}