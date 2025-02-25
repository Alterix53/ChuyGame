#include "Player.hpp"

Player::Player() : _name("Unknown"), _ID("Unknown"), _playerCost(BaseCost), _health(100), _attack(10), _atkSpeed(1), 
_defense(10),_weapon1(), _weapon2() , _helmet(), _leggings(), _boots(), _chestplate() {
}

Player::Player(std::string name, std::string ID, int cost) : 
	_name(name), _ID(ID), _playerCost(cost), _health(100), _attack(10), _atkSpeed(1), _defense(10),
	_weapon1(), _weapon2(), _helmet(), _leggings(), _boots(), _chestplate()
{}

Player::Player(std::string name, std::string ID, int cost, int health, int attack, int defense, float atkSpeed) :
	_name(name), _ID(ID), _playerCost(cost), _health(health), _attack(attack), _atkSpeed(atkSpeed), _defense(defense),
	_weapon1(), _weapon2(), _helmet(), _leggings(), _boots(), _chestplate()
{}

Player::Player(const Player& player) :
	_name(player._name), _ID(player._ID), _playerCost(player._playerCost), _health(player._health), _attack(player._attack), 
	_defense(player._defense), _atkSpeed(player._atkSpeed), _chestplate(player._chestplate),
	_leggings(player._leggings), _boots(player._boots), _helmet(player._helmet)
{
	_weapon1 = player._weapon1;
	_weapon2 = player._weapon2;
}

Player::~Player() {}

// below are getter and setter
void Player::setPoint(int points) {
	_playerCost = points;
}

int Player::getPoint() const {
	return _playerCost;
}

std::string Player::getName() const {
	return _name;
}

std::string Player::getID() const {
	return _ID;
}

int Player::getHealth() const {
	return _health;
}

int Player::getAttack() const {
	return _attack;
}

int Player::getDefense() const {
	return _defense;
}

int Player::getAtkSpeed() const {
	return _atkSpeed;
}

Weapon Player::getFirstWeapon() const {
	return _weapon1;
}

Weapon Player::getSecondWeapon() const {
	return _weapon2;
}

Armor Player::getArmor(ArmorPart part) const {
	switch (part) {
	case ArmorPart::HELMET:
		return _helmet;
	case ArmorPart::CHESTPLATE:
		return _chestplate;
	case ArmorPart::LEGGINGS:
		return _leggings;
	case ArmorPart::BOOTS:
		return _boots;
	default:
		return Armor();
	}
}

int Player::getTotalWeight() const {
	int totalWeight = 0;
	totalWeight += _helmet.getWeight();
	totalWeight += _chestplate.getWeight();
	totalWeight += _leggings.getWeight();
	totalWeight += _boots.getWeight();
	return totalWeight;
}

float Player::effectiveAtkspeed(float atkSpeed) const {
	float weight = static_cast<float>(getTotalWeight());
	return atkSpeed * (1.0f - (log(weight + 1.0f) / log(11.0f)));
}

float Player::calculateEffectiveAtkspeedAll() {
	this->_weapon1.setAtkSpeed(effectiveAtkspeed(this->_weapon1.getAtkSpeed()));
	this->_weapon2.setAtkSpeed(effectiveAtkspeed(this->_weapon2.getAtkSpeed()));
}

// below are the functions to add weapon and armor
// slot are 1 and 2, 1 is left, 2 is right
void Player::equipWeapon(Weapon weapon, int slot) {
	if (slot == 1) {
		weapon.setEquipped(true);
		_weapon1 = weapon;
		this->updateStatEquipWeapon(weapon);
	}
	else if (slot == 2) {
		weapon.setEquipped(true);
		_weapon2 = weapon;
		this->updateStatEquipWeapon(weapon);
	}
	else {
		std::cerr << "Invalid slot!" << std::endl;
	}
}

void Player::equipArmor(Armor armor) {

	ArmorPart part = armor.getPart();
	switch (part) {
	case ArmorPart::HELMET:
		armor.setEquipped(true);
		_helmet = armor; 
		this->updateStatEquipArmor(armor);
		break;
	case ArmorPart::CHESTPLATE:
		armor.setEquipped(true);
		_chestplate = armor;
		this->updateStatEquipArmor(armor);
		break;
	case ArmorPart::LEGGINGS:
		armor.setEquipped(true);
		_leggings = armor;
		this->updateStatEquipArmor(armor);
		break;
	case ArmorPart::BOOTS:
		armor.setEquipped(true);
		_boots = armor;
		this->updateStatEquipArmor(armor);
		break;
	default:
		std::cerr << "Invalid armor part!" << std::endl;
		return;
	}
}

void Player::buyWeapon(Weapon weapon) {
	int cost = weapon.getCost();
	if (_playerCost < cost) {
		std::cerr << utils::colorString("You don't have enough points to buy this weapon!", Constants::Color::RED) << std::endl;
		Sleep(Constants::others::TIME_DELAY);
		return;
	}

	_inventoryWeapon.push_back(weapon);
	_playerCost -= cost;

	std::cerr << utils::colorString("You have successfully purchased this weapon!", Constants::Color::GREEN);
	Sleep(Constants::others::TIME_DELAY);
}

void Player::buyArmor(Armor armor) {

	int cost = armor.getCost();
	if (_playerCost < cost) {
		std::cerr << utils::colorString("You don't have enough points to buy this armor!", Constants::Color::RED) << std::endl;
		Sleep(Constants::others::TIME_DELAY);
		return;
	}

	_inventoryArmor.push_back(armor);
	_playerCost -= cost;

	std::cerr << utils::colorString("You have successfully purchased this armor!", Constants::Color::GREEN);
	Sleep(Constants::others::TIME_DELAY);
}

std::vector<Weapon> Player::getInventoryWeapon() const {
	return _inventoryWeapon;
}

std::vector<Armor> Player::getInventoryArmor() const {
	return _inventoryArmor;
}

void Player::printInfo() const {

	// basic info
	std::cout << "Player's name: " << _name << std::endl;
	std::cout << "ID: " << _ID << std::endl;
	std::cout << "Remainding points: " << _playerCost << std::endl << std::endl;

	// Player's stat
	std::cout << "Player's current stat: " << std::endl;
	std::cout << "Health: " << _health << std::endl;
	std::cout << "Attack: " << _attack << std::endl;
	std::cout << "Defense: " << _defense << std::endl << std::endl;

	// weapons
	std::cout << "Weapons: ";
	if (_weapon1.getName() == "Unknown" && _weapon2.getName() == "Unknown") {
		std::cout << "No weapons!" << std::endl;
	}
	else {
		std::cout << std::endl;
		if (_weapon1.getName() != "Unknown") {
			std::cout << "Weapon 1: " << std::endl;
			_weapon1.printInfo();
		}
		if (_weapon2.getName() != "Unknown") {
			std::cout << "Weapon 1: " << std::endl;
			_weapon1.printInfo();
		}
	}

	// armors
	bool hasArmor = false;
	std::cout << "Armors: " << std::endl;
	if (_helmet.getArmorPartString() != "Unknown") {
		hasArmor = true;
		std::cout << "Helmet: " << std::endl;
		_helmet.printInfo();
	}

	if (_chestplate.getArmorPartString() != "Unknown") {
		hasArmor = true;
		std::cout << "Chestplate: " << std::endl;
		_chestplate.printInfo();
	}

	if (_leggings.getArmorPartString() != "Unknown") {
		hasArmor = true;
		std::cout << "Leggings: " << std::endl;
		_leggings.printInfo();
	}

	if (_boots.getArmorPartString() != "Unknown") {
		hasArmor = true;
		std::cout << "Boots: " << std::endl;
		_boots.printInfo();
	}

	if (!hasArmor) {
		std::cout << "No armors!" << std::endl;
	}
}

// weapon truyen vao la weapon dang mac, index la slot (ben trai hay phai) cua weapon
void Player::unequipWeapon(int index) {
	if (index == 1) {
		_weapon1.setEquipped(false);
		this->updateStatUnequipWeapon(_weapon1);
		_weapon1 = Weapon();
	}
	else if (index == 2) {
		_weapon2.setEquipped(false);
		this->updateStatUnequipWeapon(_weapon2);
		_weapon2 = Weapon();
	}
	else {
		std::cerr << "Invalid slot!" << std::endl;
	}
}

void Player::unequipArmor(ArmorPart part) {
	switch (part) {
	case ArmorPart::HELMET:
		this->updateStatUnequipArmor(_helmet);
		_helmet.setEquipped(false);
		_helmet = Armor();
		break;
	case ArmorPart::CHESTPLATE:
		_chestplate.setEquipped(false);
		this->updateStatUnequipArmor(_chestplate);
		_chestplate = Armor();
		break;
	case ArmorPart::LEGGINGS:
		_leggings.setEquipped(false);
		this->updateStatUnequipArmor(_leggings);
		_leggings = Armor();
		break;
	case ArmorPart::BOOTS:
		//if (_boots.getArmorPartString() == "Unknown") {
		//	std::cerr << "You don't have boots!" << std::endl;
		//	return;
		//}
		_boots.setEquipped(false);
		this->updateStatUnequipArmor(_boots);
		_boots = Armor();
		break;
	default:
		std::cerr << "Invalid armor part!" << std::endl;
		return;
	}
}

void Player::updateStatEquipWeapon(Weapon weapon) {
	_attack += weapon.getDamage();
	_atkSpeed += weapon.getAtkSpeed();
}

void Player::updateStatUnequipWeapon(Weapon weapon) {
	_attack -= weapon.getDamage();
	_atkSpeed -= weapon.getAtkSpeed();
}

void Player::updateStatEquipArmor(Armor armor) {
	_health += armor.getHealth();
	_defense += armor.getDefense();
	_atkSpeed -= armor.getWeight();
}

void Player::updateStatUnequipArmor(Armor armor) {
	_defense -= armor.getDefense();
	_health -= armor.getHealth();
	_atkSpeed += armor.getWeight();
}

// ham nay dung de in ra thong so cua player (khong in ra thong tin cua weapon va armor)
void Player::printPlayerStat() const {
	std::cout << "Health: " << _health << std::endl;
	std::cout << "Attack: " << _attack << std::endl;
	std::cout << "Defense: " << _defense << std::endl;
}

// TODO: change the way to print the inventory
void Player::printPlayerInventory() const {
	std::cout << "Inventory: " << std::endl;
	std::cout << "Weapons: " << (!_inventoryWeapon.empty() ? _inventoryWeapon.size() : 0) << std::endl;
	if (_inventoryWeapon.empty()) {
		std::cout << "No weapons!" << std::endl;
	}
	else {
		for (int i = 0; i < _inventoryWeapon.size(); i++) {
			std::cout << "Weapon " << i + 1 << ": " << std::endl;
			_inventoryWeapon[i].printInfoInShort();
		}
	}
	std::cout << "Armors: " << (!_inventoryArmor.empty() ? _inventoryArmor.size() : 0) << std::endl;
	if (_inventoryArmor.empty()) {
		std::cout << "No armors!" << std::endl;
	}
	else {
		for (int i = 0; i < _inventoryArmor.size(); i++) {
			std::cout << "Armor " << i + 1 << ": " << std::endl;
			_inventoryArmor[i].printInfoInShort();
		}
	}
}

std::vector <Weapon> Player::getWeaponList() { return _inventoryWeapon; }
std::vector <Armor> Player::getArmorList() {return _inventoryArmor; }