#include "Shop.hpp"

Shop::Shop() : _currentItemIndex(0), _firstItemIndex(0) {
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
				showItemShop<Weapon>(
					[this](std::vector<Weapon>& list, int firstIndex, int endIndex, int currentIndex) {
						this->printWeaponList(list, firstIndex, endIndex, currentIndex);
					},
					_availableWeapons
				);
			}
			if (shop_option == int(SHOP::ARMORS)) {
				showItemShop<Armor>(
					[this](std::vector<Armor>& list, int firstIndex, int endIndex, int currentIndex) {
						this->printArmorList(list, firstIndex, endIndex, currentIndex);
					},
					_availableArmors
				);
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

template <typename T>
void Shop::showItemShop(std::function<void(std::vector<T>&, int, int, int)> printItemList, std::vector<T> &mainList) {
	bool running = true;
	bool find = true;
	std::string search = "";
	char s;

	std::vector<T> list = mainList;
	int first = _firstItemIndex;
	int current = _currentItemIndex;
	while (running) {
		system("cls");
		
		int end = first + ITEMS_PER_PAGE;
		if (end > list.size()) {
			end = list.size();
		}

		printItemList(list, first, end, current);

		std::cout << "Press 'F' to search" << std::endl;
		
		char key = _getch();
		if (key == 'F' || key == 'f') {
			find = true;
			std::vector <T> filteredItems;
			while(find) {
				std::cout << "\033[20;0H";
				std::cout << "Enter the name you want to search: " << search;

				s = _getch();
				if (s == '\n' || s == '\r') {
					if (list.size() == mainList.size()) { // demo
						_currentItemIndex = current;
						_firstItemIndex = first;
					}
					current = 0;
					first = 0;

					list = filteredItems;
					find = false;
					continue;
				} else if (s == 8) {  //Backspace
					if (!search.empty()) {
						search.pop_back();
					}
				} else if (s == 27) { // tam thoi bo qua cai nay
					find = false;
					continue;
				} else {
					search += s;
				}
				filteredItems.clear();
				std::copy_if(mainList.begin(), mainList.end(), std::back_inserter(filteredItems), [&](T& w) {
					return startsWithIgnoreCase(w.getName(), search);
				});

				system("cls");
				printItemList(filteredItems, 0, filteredItems.size() < ITEMS_PER_PAGE ? filteredItems.size() : ITEMS_PER_PAGE, 0);
			}
			search = "";

		} else if (key == 'w' || key == 'W' || key == -32 && _getch() == 72) {
			if (current > 0 && current == first) {
				current--; first--;
			} else if (current > 0) {
				current--;
			}
		} else if (key == 's' || key == 'S' || key == -32 && _getch() == 80) {
			if (current < list.size() - 1 && current == first + ITEMS_PER_PAGE - 1) {
				current++; first++;
			} else if (current < list.size() - 1) {
				current++;
			}
		}
		else if (key == 27) {
			if (list.size() != mainList.size()) {
				list = mainList;
				current = _currentItemIndex;
				first = _firstItemIndex;
			}
			else running = false;
		} else if (key == '\r' || key == '\n') {
			T& selected = list[current];
			// more code to do
			Choice::show(selected.getName());
		}
	}
	_currentItemIndex = _firstItemIndex = 0;
}

void Shop::showWeaponShop() {
	bool running = true;
	bool find_weapon = false;
	bool find_armor = false;
	std::string search = "";
	char s;

	while (running) {
		system("cls");

		int start = _firstItemIndex;
		int end = _firstItemIndex + ITEMS_PER_PAGE;
		if (end > _availableWeapons.size()) {
			end = _availableWeapons.size();
		}
		printWeaponList(_availableWeapons, start, end, _currentItemIndex);
		
		// print notification that player can search for weapon
		std::cout << "Press 'F' to search for weapon" << std::endl;

		char key = _getch();
		if (key == 'F' || key == 'f')
		{
			// change to find box
			find_weapon = true;
			while (find_weapon) {
				std::cout << "\033[20;0H";
				std::cout << "Enter the name of the weapon you want to search: " << search;
				// std::getline(std::cin >> std::ws, search);
				s = _getch();
				if (s == '\n' || s == '\r') {
					find_weapon = false;
					continue;
				} else if (s == 8) {  //Backspace
					if (!search.empty()) {
						search.pop_back();  
					}
				} else if (s == 27) { // Esc
					find_weapon = false;
					continue;
				}
				else {
					search += s; 
				}

				std::vector <Weapon> filteredWeapons;

				std::copy_if(_availableWeapons.begin(), _availableWeapons.end(), std::back_inserter(filteredWeapons), [&](Weapon& w) {
					return startsWithIgnoreCase(w.getName(), search);
				});

				system("cls");
				printWeaponList(filteredWeapons, 0, filteredWeapons.size() < ITEMS_PER_PAGE ? filteredWeapons.size() : ITEMS_PER_PAGE, 0);
			}
			search = "";
		}
		else if (key == 'w' || key == 'W' || key == -32 && _getch() == 72) {
			if ((_currentItemIndex == _firstItemIndex) && _currentItemIndex > 0) {
				// case that the current item is the first item in the list and the current item is not the first item in the vector
				_firstItemIndex--;
				_currentItemIndex--;
			}
			else if (_currentItemIndex > 0) {
				// other case
				_firstItemIndex--;
			}
		}
		else if (key == 's' || key == 'S' || key == -32 && _getch() == 80) {
			if ((_currentItemIndex == _firstItemIndex + ITEMS_PER_PAGE - 1) && (_currentItemIndex < _availableWeapons.size() - 1)) {
				// case that the current item is the last item in the list and the current item is not the last item in the vector
				_firstItemIndex++;
				_currentItemIndex++;
			}
			else if (_currentItemIndex < _availableWeapons.size() - 1) {
				// other case
				_currentItemIndex;
			}
		}
		else if (key == 27) { // Esc
			running = false; // or break
		}
		else if (key == '\r' || key == '\n') {
			// choose the current item
			Weapon& selected = _availableWeapons[_currentItemIndex];
			// more code to do
			Choice::show(selected.getName());
			// std::cout << "\nYou have selected : " << selected.getName() << std::endl;
		}
		
	}
}

void Shop::showArmorShop() {
	bool running = true;
	while (running) {
		system("cls");
		int start = _firstItemIndex;
		int end = _firstItemIndex + ITEMS_PER_PAGE;
		if (end > _availableArmors.size()) {
			end = _availableArmors.size();
		}
		printArmorList(_availableArmors, start, end, _currentItemIndex);
		char key = _getch();
		if (key == 'w' || key == 'W' || key == -32 && _getch() == 72) {
			if ((_currentItemIndex == _firstItemIndex) && _currentItemIndex > 0) {
				// case that the current item is the first item in the list and the current item is not the first item in the vector
				_firstItemIndex--;
				_currentItemIndex--;
			}
			else if (_currentItemIndex > 0) {
				// other case
				_currentItemIndex--;
			}
		}
		else if (key == 's' || key == 'S' || key == -32 && _getch() == 80) {
			if ((_currentItemIndex == _firstItemIndex + ITEMS_PER_PAGE - 1) && (_currentItemIndex < _availableArmors.size() - 1)) {
				// case that the current item is the last item in the list and the current item is not the last item in the vector
				_firstItemIndex++;
				_currentItemIndex++;
			}
			else if (_currentItemIndex < _availableArmors.size() - 1) {
				// other case
				_currentItemIndex++;
			}
		}
		else if (key == 27) { // Esc
			running = false; // or break
		}
		else if (key == '\r' || key == '\n') {
			// choose the current item
			Armor& selected = _availableArmors[_currentItemIndex];
			std::cout << "\nB?n ?� ch?n: " << selected.getName() << std::endl;
			// more code to do
		}
	}
}

void Shop::printWeaponList(std::vector<Weapon> &list, int firstIndex, int endIndex, int currentIndex) {

	// print header
	std::cout << std::left << std::setw(List::Weapon::NUMBER) << "NUMBER" << " | "
		<< std::setw(List::Weapon::NAME) << "NAME" << " | "
		<< std::setw(List::Weapon::CATEGORY) << "CATEGORY" << " | "
		<< std::setw(List::Weapon::ATK) << "ATK" << " | "
		<< std::setw(List::Weapon::ATKSPD) << "ATKSPD" << " | "
		<< std::setw(List::Weapon::COST) << "COST" << std::endl;
	std::cout << std::string(List::Weapon::SEPARATOR, '-') << std::endl;

	if (list.empty()) {
		// "No weapons are available!" has length / 2 = 25 / 2 = 12 <(")
		std::cout << std::right << std::setw(List::Weapon::SEPARATOR / 2 + 12) << "No weapons are available!" << std::endl;
		std::cout << std::string(List::Weapon::SEPARATOR, '-') << std::endl;
		return;
	}

	// print weapon list
	for (int i = firstIndex; i < endIndex; i++) {
		if (i == currentIndex) {
			std::cout << "> "; // shows that player are choosing this weapon
		}
		else {
			std::cout << "  ";
		}
		// Number - 2 -> Number - "  " or "> " (length = 2)
		std::cout << std::left << std::setw(List::Weapon::NUMBER - 2) << i << " | "
			<< std::setw(List::Weapon::NAME) << list[i].getName() << " | "
			<< std::setw(List::Weapon::CATEGORY) << list[i].getWeaponTypeString() << " | "
			<< std::setw(List::Weapon::ATK) << list[i].getDamage() << " | "
			<< std::setw(List::Weapon::ATKSPD) << list[i].getAtkSpeed() << " | "
			<< std::setw(List::Weapon::COST) << list[i].getCost() << std::endl;
	}

	std::cout << std::string(List::Weapon::SEPARATOR, '-') << std::endl;
}

void Shop::printArmorList(std::vector<Armor> &list, int start, int end, int currentIndex) {
	// print header
	std::cout << std::left << std::setw(List::Armor::NUMBER) << "NUMBER" << " | "
		<< std::setw(List::Armor::NAME) << "NAME" << " | "
		<< std::setw(List::Armor::CATEGORY) << "CATEGORY" << " | "
		<< std::setw(List::Armor::DEF) << "DEF" << " | "
		<< std::setw(List::Armor::HEALTH) << "HEALTH" << " | "
		<< std::setw(List::Armor::WEIGHT) << "WEIGHT" << " | "
		<< std::setw(List::Armor::COST) << "COST" << std::endl;
	std::cout << std::string(List::Armor::SEPARATOR, '-') << std::endl;

	if (list.empty()) {
		// "No armors are available!" has length / 2 = 24 / 2 = 12 <(")
		std::cout << std::right << std::setw(List::Armor::SEPARATOR / 2 + 12) << "No armors are available!" << std::endl;
		std::cout << std::string(List::Armor::SEPARATOR, '-') << std::endl;
		return;
	}

	// print armor list
	for (int i = start; i < end; i++) {
		if (i == currentIndex) {
			std::cout << "> "; // shows that player are choosing this armor
		}
		else {
			std::cout << "  ";
		}

		std::cout << std::left << std::setw(List::Armor::NUMBER - 2) << i << " | "
			<< std::setw(List::Armor::NAME) << list[i].getName() << " | "
			<< std::setw(List::Armor::CATEGORY) << list[i].getArmorTypeString() << " | "
			<< std::setw(List::Armor::DEF) << list[i].getDefense() << " | "
			<< std::setw(List::Armor::HEALTH) << list[i].getHealth() << " | "
			<< std::setw(List::Armor::WEIGHT) << list[i].getWeight() << " | "
			<< std::setw(List::Armor::COST) << list[i].getCost() << std::endl;
	}

	std::cout << std::string(List::Armor::SEPARATOR, '-') << std::endl;
}