#include "Item.hpp"

Item::Item() : _name("Unknown"), _cost(0) , _isEquipped(false)  {}
Item::Item(std::string name, int cost) : _name(name), _cost(cost) , _isEquipped(false)   {}
Item::~Item() {}

std::string Item::getName() const {
	return _name;
}

int Item::getCost() const {
	return _cost;
}

bool Item::checkIsEquipped() const {
	return _isEquipped;
}

void Item::setEquipped(bool Equipped) {
	_isEquipped = Equipped;
}

std::string Item::toString() const {
	return _name;
}