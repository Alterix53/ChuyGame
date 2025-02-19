#include "Armor.hpp"

// begin implementation of Armor class
Armor::Armor() : Item(), _type(ArmorType::BASE_ARMOR_TYPE), _part(ArmorPart::BASE_ARMOR_PART)
, _defense(0), _health(0) {} 

Armor::Armor(std::string name, ArmorType type, ArmorPart part, int defense, int cost) : 
	Item(name, cost), _type(type), _part(part), _defense(defense), _health(0) { }

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