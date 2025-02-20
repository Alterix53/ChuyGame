#include <iostream>
#include <conio.h>
#include "Shop.hpp"
#include "Player.hpp"
#include "data/Data.hpp"

const int EQUIP_SLOT = 6;
const int OPTION = 4;
const int SHOP_OPTION = 3;

enum class Menu {
    CHARACTER,
    SHOP,
    PLAY,
    EXIT
};

enum class CharacterPagePosition {
    CHARACTER,
	INVENTORY,
	WEAPON1,
	WEAPON2,

};

enum class SHOP {
    WEAPONS,
    ARMORS,
    RETURN
};

void displayShop(int option) {
	std::string options[] = { "Weapon", "Armor", "Return" };

	std::cout << "\033[1;31m";
	std::cout << "\t\t\t  CHOOSE THE ITEM'S CATEGORY" << "\n\n";
	std::cout << "\033[0m";
	for (int i = 0; i < SHOP_OPTION; i++) {
		if (i == option) {
			std::cout << "\033[1;32m";
			std::cout << "\t\t\t> " << options[i] << " <" << std::endl;
			std::cout << "\033[0m";
		}
		else {
			std::cout << "\t\t\t  " << options[i] << "  " << std::endl;
		}
	}
}

void displayMenu(int option) {
    std::string options[] = {"Character", "Shop", "Play", "Exit"};

    std::cout << "\033[1;31m";
    std::cout << "\t\t\t  CHUYGAME" << "\n\n";
    std::cout << "\033[0m";
    for (int i = 0; i < OPTION; i++) {
        if (i == option) {
            std::cout << "\033[1;32m";
            std::cout << "\t\t\t> " << options[i] << " <" << std::endl;
            std::cout << "\033[0m";
        } else {
            std::cout << "\t\t\t  " << options[i] << "  " << std::endl;
        }
    }
}

int main() {

    // inital data


    std::cout << "\033[?25l"; 
    int option = 0;
    
    bool isHome = true;
    while (isHome) {
        system("cls");
        displayMenu(option);

        char key = getch();        
        
        if (key == 'w' || key == 'W') {
            option = (option > 0) ? option - 1 : OPTION - 1;
        } else if (key == 's' || key == 'S') {
            option = (option < OPTION - 1) ? option + 1 : 0;
        } else if (key == -32) {
            key = getch(); 
            
            if (key == 72) {
                option = (option > 0) ? option - 1 : OPTION - 1;
            } else if (key == 80) { 
                option = (option < OPTION - 1) ? option + 1 : 0;
            }   
        } else if (key == '\n' || key == '\r') {   // choose the current option
            if (option == int(Menu::CHARACTER)) {
                /*
                
                */
            } 
            if (option == int(Menu::SHOP)) {

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
                        else if (key == '\n' || key == '\r') {   // choose the current shop_option
                            if (shop_option == int(SHOP::WEAPONS)) {
                                system("cls");
								// lay du lieu roi luu vao shop
								Shop shop;
								json data = WeaponData::getWeapons();
								for (const auto& item : data) {
									Weapon weapon(item["name"], item["cost"], item["type"], item["damage"], item["atkSpeed"]);
									shop.addWeaponToShop(weapon);
								}
								shop.printAvailableWeapons();
								std::cout << "Press any key to continue...";
								getch();
                            }
                            if (shop_option == int(SHOP::ARMORS)) {}
                            if (shop_option == int(SHOP::RETURN)) {
                                break;
                            }
                        }
                }

            }
            if (option == int(Menu::PLAY)) {
            }
            if (option == int(Menu::EXIT)) {
                json dataW = WeaponData::getWeapons();
                json dataA = ArmorData::getArmors();
                std::cout << dataW[0]["type"] << std::endl;
                std::cout << dataW[0]["name"] << std::endl;
                std::cout << dataW[0]["damage"] << std::endl;
                std::cout << "\n\n";
                for (const auto &item : dataA) {
                    std::cout << item["type"] << std::endl;
                    std::cout << item["part"] << std::endl;
                    std::cout << item["defense"] << std::endl;
                }

                break;
            }
        }
    }

    std::cout << "\033[?25h";
    return 0;
}