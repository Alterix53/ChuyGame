#include "Weapon.hpp"

Weapon::Weapon() : Item(), _type(WeaponType::BASEWEAPON), _damage(0), _atkSpeed(0) {}
Weapon::Weapon(std::string name, int cost, WeaponType type, int damage, int atkSpeed) :
	Item(name, cost), _type(type), _damage(damage), _atkSpeed(atkSpeed) {}

std::string Weapon::getName() {
	return _name;
}
int Weapon::getCost() {
	return _cost;	
}

void Weapon::setCost(int cost) {
	_cost = cost;
}

int Weapon::getDamage() {
	return _damage;
}

void Weapon::setDamage(int damage) {
	_damage = damage;
}

int Weapon::getAtkSpeed() {
	return _atkSpeed;
}

WeaponType Weapon::getType() {
	return _type;
}

std::string Weapon::getWeaponTypeString() {
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

void Weapon::printInfo() {
	
	std::cout << "Weapon's name: " << _name << std::endl;
	std::cout << "Type: " << getWeaponTypeString() << std::endl;
	std::cout << "Damage: " << _damage << std::endl;
	std::cout << "Attack Speed: " << _atkSpeed << std::endl;
	std::cout << "Cost: " << _cost << std::endl;

}

Weapon::~Weapon() {}