#include "Armor.hpp"

// begin implementation of Armor class
Armor::Armor() : Item(), _type(ArmorType::BASE_ARMOR_TYPE), _part(ArmorPart::BASE_ARMOR_PART)
, _defense(BASE_ARMOR_DEFENSE), _health(BASE_ARMOR_HEALTH), _weight(BASE_ARMOR_WEIGHT) {}

Armor::Armor(std::string name, ArmorType type, ArmorPart part, int health, int defense, int weight, int cost) : 
	Item(name, cost), _type(type), _part(part), _defense(defense), _health(health), _weight(weight) { }

Armor::~Armor() {}

// getter and setter
std::string Armor::getName() const {
	return _name;
}

ArmorType Armor::getType() const {
	return _type;
}

ArmorPart Armor::getPart() const {
	return _part;
}

int Armor::getDefense() const {
	return _defense;
}

int Armor::getCost() const {
	return _cost;
}

int Armor::getHealth() const {
	return _health;
}

int Armor::getWeight() const {
	return _weight;
}

void Armor::setEquipped(bool Equipped) {
	_isEquipped = Equipped;
}

// calculate the cost of the armor
int Armor::calculateCost() {
	// hay thay cong thuc theo y cua ban <(") (hien tai la 10hp + 2def + 12)
	_cost = _defense * 2 + _health * 10 + 12;
	return _cost;
}

// get armor part string
std::string Armor::getArmorPartString() const {
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
std::string Armor::getArmorTypeString() const {
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
void Armor::printInfo() const {
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

void Armor::printInfoInShort() const {
	std::cout << _name << " - " << _health << " health - " << _defense << " defense - " << _cost << " points" << std::endl;
}

std::string Armor::toString() const {
	std::stringstream ss;
	ss << "name: " << _name << "\n"
	   << "type: " << getArmorTypeString() << "\n"
	   << "part: " << getArmorPartString() << "\n"
	   << "hp: " << _health << std::right << std::setw(std::max(0, int(26   - (3 + std::to_string(_health).length()) - std::to_string(_defense).length()))) << "def: " << _defense << "\n";
	return ss.str();
}