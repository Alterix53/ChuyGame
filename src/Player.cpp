#include "Player.hpp"
#include <typeinfo>

Player::Player() : _name("Unknown"), _ID("Unknown"), _points(0), _health(100), _attack(10), _atkSpeed(1), 
_defense(10), _weapIndex(0), _weapon{ Weapon(), Weapon() }, _helmet(), _leggings(), _boots(), _chestplate() {
}

Player::Player(std::string name, std::string ID, int points) : 
	_name(name), _ID(ID), _points(points), _health(100), _attack(10), _atkSpeed(1), _defense(10),
	_weapIndex(0),	_weapon{ Weapon(), Weapon() }, _helmet(), _leggings(), _boots(), _chestplate()
{}

Player::Player(std::string name, std::string ID, int points, int health, int attack, int atkSpeed, int defense) :
	_name(name), _ID(ID), _points(points), _health(health), _attack(attack), _atkSpeed(atkSpeed), _defense(defense),
	_weapIndex(0),	_weapon{ Weapon(), Weapon() }, _helmet(), _leggings(), _boots(), _chestplate()
{}

Player::Player(const Player& player) :
	_name(player._name), _ID(player._ID), _points(player._points), _health(player._health), _attack(player._attack), 
	_defense(player._defense), _weapIndex(player._weapIndex), _atkSpeed(player._atkSpeed), _chestplate(player._chestplate),
	_leggings(player._leggings), _boots(player._boots), _helmet(player._helmet)
{
	_weapon[0] = player._weapon[0];
	_weapon[1] = player._weapon[1];
}

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
		std::cerr << "Not enough points to buy this weapon!" << std::endl;
		return false;
	}

	if (_weapIndex >= 2) {
		std::cerr << "You can only have 2 weapons!" << std::endl;
		return false;
	}

	_weapon[_weapIndex++] = weapon;
	_points -= cost;
	return true;
}

void Player::printInfo() {

	// basic info
	std::cout << "Player's name: " << _name << std::endl;
	std::cout << "ID: " << _ID << std::endl;
	std::cout << "Remainding points: " << _points << std::endl << std::endl;

	// Player's stat
	std::cout << "Player's current stat: " << std::endl;
	std::cout << "Health: " << _health << std::endl;
	std::cout << "Attack: " << _attack << std::endl;
	std::cout << "Defense: " << _defense << std::endl << std::endl;

	// weapons
	std::cout << "Weapons: ";
	if (_weapIndex == 0) {
		std::cout << "No weapons!" << std::endl;
		return;
	}

	std::cout << std::endl;
	for (int i = 0; i < _weapIndex; i++) {
		std::cout << "Weapon " << i + 1 << ": " << std::endl;
		_weapon[i].printInfo();
	}

	// armors
	std::cout << "Armors: " << std::endl;
	if (_helmet.getArmorPartString() == "Unknown") {
		std::cout << "Helmet: " << std::endl;
		_helmet.printInfo();
	}
}

void Player::updateStatEquipItem(Item item) {
	// if the equipped item is a weapon
	if (typeid(item) == typeid(Weapon)) {
		
	}
}