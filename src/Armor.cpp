#include "Armor.hpp"

// begin implementation of Armor class
Armor::Armor() : Item(), _type(ArmorType::BASE_ARMOR_TYPE), _part(ArmorPart::BASE_ARMOR_PART)
, _defense(BASE_ARMOR_DEFENSE), _health(BASE_ARMOR_HEALTH) {}

Armor::Armor(std::string name, ArmorType type, ArmorPart part, int health, int defense, int cost) : 
	Item(name, cost), _type(type), _part(part), _defense(defense), _health(health) { }

Armor::~Armor() {}

// getter and setter
std::string Armor::getName() {
	return _name;
}

ArmorType Armor::getType() {
	return _type;
}

ArmorPart Armor::getPart() {
	return _part;
}

int Armor::getDefense() {
	return _defense;
}

int Armor::getCost() {
	return _cost;
}

int Armor::getHealth() {
	return _health;
}

// calculate the cost of the armor
void Armor::calculateCost() {
	// hay thay cong thuc theo y cua ban <(") (hien tai la 10hp + 2def + 12)
	_cost = _defense * 2 + _health * 10 + 12; 
}

// get armor part string
std::string Armor::getArmorPartString() {
	switch (_part) {
	case ArmorPart::HELMET:
		return "Helmet";
	case ArmorPart::CHESTPLATE:
		return "Chestplate";
	case ArmorPart::LEGGINGS:
		return "Leggings";
	case ArmorPart::BOOTS:
		return "Boots";
	default:
		return "Unknown";
	}
}

// get armor type string
std::string Armor::getArmorTypeString() {
	switch (_type) {
	case ArmorType::BULLETPROOF:
		return "Bulletproof";
	case ArmorType::CHAIN:
		return "Chain";
	case ArmorType::LEATHER:
		return "Leather";
	case ArmorType::PLATE:
		return "Plate";
	default:
		return "Unknown";
	}
}

// print armor info
void Armor::printInfo() {

	std::string part = getArmorPartString();
	std::string type = getArmorTypeString();

	std::cout << "Armor Info:" << std::endl;
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Type: " << type << std::endl;
	std::cout << "Part: " << part << std::endl;
	std::cout << "Health: " << _health << std::endl;
	std::cout << "defense: " << _defense << std::endl;
	std::cout << "Cost: " << _cost << std::endl;

}

void Armor::printInfoInShort() {
	std::cout << _name << " - " << _health << " health - " << _defense << " defense - " << _cost << " points" << std::endl;
}