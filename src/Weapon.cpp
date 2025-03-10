#include "Weapon.hpp"

Weapon::Weapon() : Item(), _type(WeaponType::BASEWEAPON), _damage(0), _atkSpeed(0.0f) {}
Weapon::Weapon(std::string name, int cost, WeaponType type, int damage, float atkSpeed) :
	Item(name, cost), _type(type), _damage(damage), _atkSpeed(atkSpeed) {}

Weapon::~Weapon() = default;

void Weapon::setCost(int cost) {
	_cost = cost;
}

void Weapon::setAtkSpeed(float atkSpeed) {
	_atkSpeed = atkSpeed;
}

void Weapon::setDamage(int damage) {
	_damage = damage;
}
 
std::string Weapon::getName() const {
	return _name;
}
int Weapon::getCost() const {
	return _cost;	
}
int Weapon::getDamage() const {
	return _damage;
}
float Weapon::getAtkSpeed() const {
	return _atkSpeed;
}

WeaponType Weapon::getType() const {
	return _type;
}

void Weapon::setEquipped(bool Equipped) {
	_isEquipped = Equipped;
}

std::string Weapon::getWeaponTypeString() const {
	switch (_type) {
	case WeaponType::SWORD:
		return "Sword";
	case WeaponType::BOW:
		return "Bow";
	case WeaponType::DAGGER:
		return "Dagger";
	case WeaponType::AXE:
		return "Axe";
	default:
		return "Unknown";
	}
}

int Weapon::calculateCost() {
	// lai nua, hay thay cong thuc theo y cua ban <(") (hien tai la 2*dam + 10*atk + 12)
	_cost = _damage * 3 + _atkSpeed * 15 + 20;
	return _cost;
}

void Weapon::printInfoInShort() const {
	std::cout << _name << " - " << _damage << " damage - " << _atkSpeed << " atk speed - " << _cost << " points" << std::endl;
	std::cout << "Equipped: " << (_isEquipped ? "Yes" : "No") << std::endl;
}

void Weapon::printInfo() const {
	std::cout << "Weapon's name: " << _name << std::endl;
	std::cout << "Type: " << getWeaponTypeString() << std::endl;
	std::cout << "Damage: " << _damage << std::endl;
	std::cout << "Attack Speed: " << _atkSpeed << std::endl;
	std::cout << "Cost: " << _cost << std::endl;
	std::cout << "Equipped: " << (_isEquipped ? "Yes" : "No") << std::endl;
}

std::string Weapon::toString() const {
	std::stringstream ss;
	ss << "name: " << _name << "\n"
	   << "type: " << getWeaponTypeString() << "\n"
	   << "damage: " << _damage << "\n"
	   << "atkspd: " << std::fixed << std::setprecision(2) << _atkSpeed;
	return ss.str();
}