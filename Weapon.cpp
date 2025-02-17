#include "Weapon.h"

Weapon::Weapon() : _damage(0), _cost(0), _name("Unknown"), _type(WeaponType::BASEWEAPON) {}
Weapon::Weapon(std::string name, int damage, int cost, WeaponType type) :
	_name(name), _damage(damage), _cost(cost), _type(type) {}

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

void Weapon::printInfo() const {
	// in type kieu gi ching oi cuu voi, ma chac khong can dau nhi
	std::cout << "Weapon's name: " << _name << std::endl;
	std::cout << "Damage: " << _damage << std::endl;
	std::cout << "Cost: " << _cost << std::endl;
}

Weapon::~Weapon() {}