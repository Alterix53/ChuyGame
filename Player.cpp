#include "Player.h"

Player::Player() : _name("Unknown"), _ID("Unknown"), _points(0) {}

Player::Player(std::string name, std::string ID, int points) : 
	_name(name), _ID(ID), _points(points) {}

Player::Player(const Player& player) :
	_name(player._name), _ID(player._ID), _points(player._points), _weapons(player._weapons) {}

Player::~Player() {}

void Player::setPoint(int points) {
	_points = points;
}

int Player::getPoint() {
	return _points;
}

bool Player::addWeapon(Weapon weapon) {
	int cost = weapon.getCost();
	if (cost > _points) {
		std::cout << "Not enough points to buy this weapon!" << std::endl;
		return false;
	}

	_weapons.push_back(weapon);
	_points -= cost;
	return true;
}

void Player::printInfo() const {

	std::cout << "Player's name: " << _name << std::endl;
	std::cout << "ID: " << _ID << std::endl;
	std::cout << "Remainding points: " << _points << std::endl;
	std::cout << "Weapons: ";

	if (_weapons.empty()) {
		std::cout << "No weapons!" << std::endl;
		return;
	}

	std::cout << std::endl;
	for (int i = 0; i < _weapons.size(); i++) {
		std::cout << "Weapon " << i + 1 << ": " << std::endl;
		_weapons[i].printInfo();
	}
}