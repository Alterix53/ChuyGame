#include "Shop.hpp"

Shop::Shop() : _currentItemWeaponIndex(0), _firstItemWeaponIndex(0), _firstItemArmorIndex(0), _currentItemArmorIndex(0) {
	WeaponData::loadData(this->_availableWeapons);
	ArmorData::loadData(this->_availableArmors);
}

Shop::~Shop() = default;

void Shop::addWeaponToShop(Weapon weapon) {
	_availableWeapons.push_back(weapon);
}

void Shop::addArmorToShop(Armor armor) {
	_availableArmors.push_back(armor);
}

void Shop::printAvailableWeapons() {
	if (_availableWeapons.empty()) {
		std::cout << "No weapons are available!" << std::endl;
		return;
	}
	std::cout << "Available weapons for players: " << std::endl;
	std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(8) << "Damage";
	std::cout << std::right << std::setw(8) << "AtkSpeed" << std::right << std::setw(8) << "Cost" << std::endl;
	for (int i = 0; i < _availableWeapons.size(); i++) {
		std::cout << std::left << std::setw(20) << _availableWeapons[i].getName() << std::right << std::setw(8) << _availableWeapons[i].getDamage();
		std::cout << std::right << std::setw(8) << _availableWeapons[i].getAtkSpeed() << std::right << std::setw(8) << _availableWeapons[i].getCost() << std::endl;
	}
}

void Shop::printAvailableArmors() {
	if (_availableArmors.empty()) {
		std::cout << "No armors are available!" << std::endl;
		return;
	}

	std::cout << "Available armors for players: " << std::endl;
	std::cout << std::left << std::setw(20) << "Name" << std::right << std::setw(8) << "Defense";
	std::cout << std::right << std::setw(8) << "Defense" << std::right << std::setw(8) << "Cost" << std::endl;
	for (int i = 0; i < _availableArmors.size(); i++) {
		std::cout << std::left << std::setw(20) << _availableArmors[i].getName() << std::right << std::setw(8) << _availableArmors[i].getDefense();
		std::cout << std::right << std::setw(8) << _availableArmors[i].getDefense() << std::right << std::setw(8) << _availableArmors[i].getCost() << std::endl;
	}
}

void Shop::getWeapon(Player& player, std::string weaponName) {

	for (int i = 0; i < _availableWeapons.size(); i++) {

		if (_availableWeapons[i].getName() != weaponName) 
			continue;

		player.buyWeapon(_availableWeapons[i]);
			return;
	}

	std::cout << "Weapon is not available!" << std::endl;
}

void Shop::getArmor(Player& player, std::string armorName) {
	for (int i = 0; i < _availableArmors.size(); i++) {

		if (_availableArmors[i].getName() != armorName)
			continue;

		player.buyArmor(_availableArmors[i]);
		return;

	}

	std::cout << "Armor is not available!" << std::endl;
}

// the index is the current index in the vector
void Shop::getWeaponByIndex(Player& player, int index) {
	if (index < 0 || index >= _availableWeapons.size()) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	player.buyWeapon(_availableWeapons[index]);
}

void Shop::getArmorByIndex(Player& player, int index) {
	if (index < 0 || index >= _availableArmors.size()) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	player.buyArmor(_availableArmors[index]);
}

std::vector <Weapon> Shop::filterWeaponByType(WeaponType type) {
	std::vector <Weapon> filteredWeapons;
	for (int i = 0; i < _availableWeapons.size(); i++) {
		if (_availableWeapons[i].getType() == type) {
			filteredWeapons.push_back(_availableWeapons[i]);
		}
	}
	return filteredWeapons;
}

std::vector <Armor> Shop::filterArmorByType(ArmorType type) {
	std::vector <Armor> filteredArmors;
	for (int i = 0; i < _availableArmors.size(); i++) {
		if (_availableArmors[i].getType() == type) {
			filteredArmors.push_back(_availableArmors[i]);
		}
	}
	return filteredArmors;
}

void Shop::runShop() {
    bool inShop = true;
    int shop_option = 0;

    while (inShop) {
        system("cls");
        displayShop(shop_option);
        char key_shop = getch();

        if (key_shop == 'w' || key_shop == 'W') {
            shop_option = (shop_option > 0) ? shop_option - 1 : SHOP_OPTION - 1;
        }
        else if (key_shop == 's' || key_shop == 'S') {
            shop_option = (shop_option < SHOP_OPTION - 1) ? shop_option + 1 : 0;
        }
        else if (key_shop == -32) {
            key_shop = getch();

            if (key_shop == 72) {
                shop_option = (shop_option > 0) ? shop_option - 1 : SHOP_OPTION - 1;
            }
            else if (key_shop == 80) {
                shop_option = (shop_option < SHOP_OPTION - 1) ? shop_option + 1 : 0;
            }
        } else if (key_shop == '\n' || key_shop == '\r') {   // choose the current shop_option
			if (shop_option == int(SHOP::WEAPONS)) {
				showWeaponShop();
			}
			if (shop_option == int(SHOP::ARMORS)) {
				showArmorShop();
			}
			if (shop_option == int(SHOP::RETURN)) 
				break;
		}
    }
}

void Shop::displayShop(int opt) {
	std::string options[] = { "Weapon", "Armor", "Return" };

	std::cout << "\033[1;31m";
	std::cout << "\t\t\t  CHOOSE THE ITEM'S CATEGORY" << "\n\n";
	std::cout << "\033[0m";
	for (int i = 0; i < SHOP_OPTION; i++) {
		if (i == opt) {
			std::cout << "\033[1;32m";
			std::cout << "\t\t\t> " << options[i] << " <" << std::endl;
			std::cout << "\033[0m";
		}
		else {
			std::cout << "\t\t\t  " << options[i] << "  " << std::endl;
		}
	}
}

void Shop::showWeaponShop() {
	bool running = true;
	while (running) {
		system("cls");

		int start = _firstItemWeaponIndex;
		int end = _firstItemWeaponIndex + ITEMS_PER_PAGE;
		if (end > _availableWeapons.size()) {
			end = _availableWeapons.size();
		}
		printWeaponList(start, end, _currentItemWeaponIndex);

		char key = _getch();
		if (key == 'w' || key == 'W' || key == -32 && _getch() == 72) {
			if ((_currentItemWeaponIndex = _firstItemWeaponIndex) && _currentItemWeaponIndex > 0) {
				// case that the current item is the first item in the list and the current item is not the first item in the vector
				_firstItemWeaponIndex--;
				_currentItemWeaponIndex--;
			}
			else if (_currentItemWeaponIndex > 0) {
				// other case
				_currentItemWeaponIndex--;
			}
		}
		else if (key == 's' || key == 'S' || key == -32 && _getch() == 80) {
			if ((_currentItemWeaponIndex = _firstItemWeaponIndex + ITEMS_PER_PAGE - 1) && (_currentItemWeaponIndex < _availableWeapons.size() - 1)) {
				// case that the current item is the last item in the list and the current item is not the last item in the vector
				_firstItemWeaponIndex++;
				_currentItemWeaponIndex++;
			}
			else if (_currentItemWeaponIndex < _availableWeapons.size() - 1) {
				// other case
				_currentItemWeaponIndex++;
			}
		}
		else if (key == 27) { // Esc
			running = false; // or break
		}
		else if (key == '\r' || key == '\n') {
			// choose the current item
			Weapon& selected = _availableWeapons[_currentItemWeaponIndex];
			std::cout << "\nB?n ?� ch?n: " << selected.getName() << std::endl;
			// more code to do
		}
		
	}
}

void Shop::showArmorShop() {
	bool running = true;
	while (running) {
		system("cls");
		int start = _firstItemArmorIndex;
		int end = _firstItemArmorIndex + ITEMS_PER_PAGE;
		if (end > _availableArmors.size()) {
			end = _availableArmors.size();
		}
		printArmorList(start, end, _currentItemArmorIndex);
		char key = _getch();
		if (key == 'w' || key == 'W' || key == -32 && _getch() == 72) {
			if ((_currentItemArmorIndex = _firstItemArmorIndex) && _currentItemArmorIndex > 0) {
				// case that the current item is the first item in the list and the current item is not the first item in the vector
				_firstItemArmorIndex--;
				_currentItemArmorIndex;
			}
			else if (_currentItemArmorIndex > 0) {
				// other case
				_currentItemArmorIndex;
			}
		}
		else if (key == 's' || key == 'S' || key == -32 && _getch() == 80) {
			if ((_currentItemArmorIndex = _firstItemArmorIndex + ITEMS_PER_PAGE - 1) && (_currentItemArmorIndex < _availableArmors.size() - 1)) {
				// case that the current item is the last item in the list and the current item is not the last item in the vector
				_firstItemArmorIndex++;
				_currentItemArmorIndex++;
			}
			else if (_currentItemArmorIndex < _availableArmors.size() - 1) {
				// other case
				_currentItemArmorIndex++;
			}
		}
		else if (key == 27) { // Esc
			running = false; // or break
		}
		else if (key == '\r' || key == '\n') {
			// choose the current item
			Armor& selected = _availableArmors[_currentItemArmorIndex];
			std::cout << "\nB?n ?� ch?n: " << selected.getName() << std::endl;
			// more code to do
		}
	}
}

void Shop::printWeaponList(int firstIndex, int endIndex, int currentIndex) {

	// print header
	std::cout << std::left << std::setw(8) << "NUMBER" << " | "
		<< std::setw(20) << "NAME" << " | "
		<< std::setw(10) << "CATEGORY" << " | "
		<< std::setw(5) << "ATK" << " | "
		<< std::setw(7) << "ATKSPD" << " | "
		<< std::setw(6) << "COST" << std::endl;
	std::cout << std::string(70, '-') << std::endl;

	// print weapon list
	for (int i = firstIndex; i < endIndex; i++) {
		if (i == currentIndex) {
			std::cout << "> "; // shows that player are choosing this weapon
		}
		else {
			std::cout << "  ";
		}
		std::cout << std::left << std::setw(6) << i << " | "
			<< std::setw(20) << _availableWeapons[i].getName() << " | "
			<< std::setw(10) << _availableWeapons[i].getWeaponTypeString() << " | "
			<< std::setw(5) << _availableWeapons[i].getDamage() << " | "
			<< std::setw(7) << _availableWeapons[i].getAtkSpeed() << " | "
			<< std::setw(6) << _availableWeapons[i].getCost() << std::endl;
	}
}

void Shop::printArmorList(int start, int end, int currentIndex) {
	// print header
	std::cout << std::left << std::setw(8) << "NUMBER" << " | "
		<< std::setw(20) << "NAME" << " | "
		<< std::setw(11) << "CATEGORY" << " | "
		<< std::setw(5) << "DEF" << " | "
		<< std::setw(7) << "HEALTH" << " | "
		<< std::setw(8) << "WEIGHT" << " | "
		<< std::setw(6) << "COST" << std::endl;
	std::cout << std::string(81, '-') << std::endl;
	// print armor list
	for (int i = start; i < end; i++) {
		if (i == currentIndex) {
			std::cout << "> "; // shows that player are choosing this armor
		}
		else {
			std::cout << "  ";
		}
		std::cout << std::left << std::setw(6) << i << " | "
			<< std::setw(20) << _availableArmors[i].getName() << " | "
			<< std::setw(10) << _availableArmors[i].getArmorTypeString() << " | "
			<< std::setw(5) << _availableArmors[i].getDefense() << " | "
			<< std::setw(7) << _availableArmors[i].getHealth() << " | "
			<< std::setw(8) << _availableArmors[i].getWeight() << " | "
			<< std::setw(6) << _availableArmors[i].getCost() << std::endl;
	}
}