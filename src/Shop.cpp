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

// void Shop::getArmor(Player& player, std::string armorName) {
// 	for (int i = 0; i < _availableArmors.size(); i++) {

// 		if (_availableArmors[i].getName() != armorName)
// 			continue;

// 		player.buyArmor(_availableArmors[i]);
// 		return;

// 	}

// 	std::cout << "Armor is not available!" << std::endl;
// }

// the index is the current index in the vector

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

void Shop::runShop(Player& buyer) {
    bool inShop = true;
    int shop_option = 0;

    while (inShop) {
        system("cls");
        displayShop(shop_option);
        char key_shop = getch();
		if (key_shop == -32) { 
            key_shop = _getch();
        }

        if (key_shop == 'w' || key_shop == 'W' || key_shop == 72) {
            shop_option = (shop_option > 0) ? shop_option - 1 : SHOP_OPTION - 1;
        }
        else if (key_shop == 's' || key_shop == 'S' || key_shop == 80) {
            shop_option = (shop_option < SHOP_OPTION - 1) ? shop_option + 1 : 0;
        } else if (key_shop == 27) { // esc
			break;
        } else if (key_shop == '\n' || key_shop == '\r') {   // choose the current shop_option
			if (shop_option == int(SHOP::WEAPONS)) {
				showItemShop<Weapon>(
					[this](std::vector<Weapon>& list, int firstIndex, int endIndex, int currentIndex) {
						this->printWeaponList(list, firstIndex, endIndex, currentIndex);
					},
					_availableWeapons,
					buyer
				);
			}
			else if (shop_option == int(SHOP::ARMORS)) {
				showItemShop<Armor>(
					[this](std::vector<Armor>& list, int firstIndex, int endIndex, int currentIndex) {
						this->printArmorList(list, firstIndex, endIndex, currentIndex);
					},
					_availableArmors,
					buyer
				);
			}
			else if (shop_option == int(SHOP::RETURN)) 
				break;
		}
    }
}

void Shop::displayShop(int opt) {
	std::string options[] = { "Weapon", "Armor", "Back" };

	std::cout << "\033[1;31m";
	std::cout << "\t\t CHOOSE THE ITEM'S CATEGORY" << "\n\n";
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
void Shop::showItemShop(std::function<void(std::vector<T>&, int, int, int)> printItemList, std::vector<T> &mainList, Player& buyer) {
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

		std::cout << "\nPress 'F' to search" << std::endl;
		
		char key = _getch();
		if (key == -32) { 
            key = _getch();
        }
		if (key >= '1' && key <= '9') {
			first = (key - '0' - 1) * ITEMS_PER_PAGE;
			current = first;
		} else if (key == 'F' || key == 'f') {
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
					return utils::startsWithIgnoreCase(w.getName(), search);
				});

				system("cls");
				printItemList(filteredItems, 0, filteredItems.size() < ITEMS_PER_PAGE ? filteredItems.size() : ITEMS_PER_PAGE, 0);
			}
			search = "";

		} else if (key == 'w' || key == 'W' || key == 72) {
			if (current > 0 && current == first) {
				current--; first--;
			} else if (current > 0) {
				current--;
			}
		} else if (key == 's' || key == 'S' || key == 80) {
			if (current < list.size() - 1 && current == first + ITEMS_PER_PAGE - 1) {
				current++; first++;
			} else if (current < list.size() - 1) {
				current++;
			}
		} else if (key == 'a' || key == 'A' || key == 75) {
			int page = std::ceil(((double)current + 1) / ITEMS_PER_PAGE) - 1;
			if (page > 0) { 
				first = page * ITEMS_PER_PAGE - ITEMS_PER_PAGE;
				current = first;
			}
		} else if (key == 'd' || key == 'D' || key == 77) {
			int totalPages = std::ceil(((double)list.size() + 1) / ITEMS_PER_PAGE);
			int page = std::ceil(((double)current + 1) / ITEMS_PER_PAGE); 
			if (page < totalPages) {
				first = page * ITEMS_PER_PAGE;
				current = first;
			}
		} else if (key == 27) {
			if (list.size() != mainList.size()) {
				list = mainList;
				current = _currentItemIndex;
				first = _firstItemIndex;
			}
			else running = false;
		} else if (key == '\r' || key == '\n') {

			T& selected = list[current];
			if (Choice::show(selected.getName()) == true) {
				if (Weapon* w = dynamic_cast<Weapon*>(&selected)) {
					buyer.buyWeapon(*w);
				} else if (Armor* a = dynamic_cast<Armor*>(&selected)) {
					buyer.buyArmor(*a);
				}
			}
		}
	}
	_currentItemIndex = _firstItemIndex = 0;
}

void Shop::printWeaponList(std::vector<Weapon> &list, int firstIndex, int endIndex, int currentIndex) {
	std::cout << "\033[s";  // save cursor position
	std::cout << "\033[19;0H"; 
	if (!list.empty()) {
		int page = std::ceil(((double)currentIndex + 1) / ITEMS_PER_PAGE);
		int totalPage = std::ceil(((double)list.size() + 1) / ITEMS_PER_PAGE);
		if (page > totalPage) totalPage = -1;
		std::cout << std::right << std::setw(List::Weapon::SEPARATOR / 2 - 3) << page << "/" <<  (totalPage != -1 ? std::to_string(totalPage) : "?");
	}
	std::cout << "\033[u";  // restore cursor position
	
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
	bool isExistPage = false;
	for (int i = firstIndex; i < endIndex; i++) {
		if (i == currentIndex) {
			std::cout << "> "; // shows that player are choosing this weapon
			isExistPage = true;
		}
		else {
			std::cout << "  ";
		}
		// Number - 2 -> Number - "  " or "> " (length = 2)
		std::cout << std::left << std::setw(List::Weapon::NUMBER - 2) << i + 1 << " | "
			<< std::setw(List::Weapon::NAME) << list[i].getName() << " | "
			<< std::setw(List::Weapon::CATEGORY) << list[i].getWeaponTypeString() << " | "
			<< std::setw(List::Weapon::ATK) << list[i].getDamage() << " | "
			<< std::setw(List::Weapon::ATKSPD) << list[i].getAtkSpeed() << " | "
			<< std::setw(List::Weapon::COST) << list[i].calculateCost() << std::endl;
	}
	if (!isExistPage) {
		std::cout << std::right << std::setw(List::Weapon::SEPARATOR / 2 + 6) << "This page is empty" << std::endl;
	}
	
	std::cout << std::string(List::Weapon::SEPARATOR, '-') << std::endl;
}

void Shop::printArmorList(std::vector<Armor> &list, int start, int end, int currentIndex) {
	std::cout << "\033[s";  
	std::cout << "\033[19;0H"; 
	if (!list.empty()) {
		int page = std::ceil(((double)currentIndex + 1) / ITEMS_PER_PAGE);
		int totalPage = std::ceil(((double)list.size() + 1) / ITEMS_PER_PAGE);
		if (page > totalPage) totalPage = -1;
		std::cout << std::right << std::setw(List::Armor::SEPARATOR / 2 - 3) << page << "/" <<  (totalPage != -1 ? std::to_string(totalPage) : "?");
	}
	std::cout << "\033[u";  

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
	bool isExistPage = false;
	for (int i = start; i < end; i++) {
		if (i == currentIndex) {
			std::cout << "> "; // shows that player are choosing this armor
			isExistPage = true;
		}
		else {
			std::cout << "  ";
		}

		std::cout << std::left << std::setw(List::Armor::NUMBER - 2) << i + 1 << " | "
			<< std::setw(List::Armor::NAME) << list[i].getName() << " | "
			<< std::setw(List::Armor::CATEGORY) << list[i].getArmorTypeString() << " | "
			<< std::setw(List::Armor::DEF) << list[i].getDefense() << " | "
			<< std::setw(List::Armor::HEALTH) << list[i].getHealth() << " | "
			<< std::setw(List::Armor::WEIGHT) << list[i].getWeight() << " | "
			<< std::setw(List::Armor::COST) << list[i].calculateCost() << std::endl;
	}
	if (!isExistPage) {
		std::cout << std::right << std::setw(List::Armor::SEPARATOR / 2 + 6) << "This page is empty" << std::endl;
	}

	std::cout << std::string(List::Armor::SEPARATOR, '-') << std::endl;
}