#include <iostream>
#include <conio.h>
#include "Shop.hpp"
#include "Player.hpp"
#include "data/Data.hpp"
#include <vector>
#include "Weapon.hpp"

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
                std::string json = "{\"weapon\":[{\"type\":\"test\",\"name\":\"test\",\"damage\":12, \"atkSpeed\": 1, \"cost\": 1000}],\"armor\":[{\"type\": \"test1\",\"name\":\"test1\", \"part\": \"test\",\"defense\":2,\"health\":141}]}";
                json.insert(1, "\"tenNguoiChoi\":\"Player1\",\"idNguoiChoi\":\"1\",");

                std::string eJson = json;
                size_t position = 0;
                while ((position = eJson.find("\"", position)) != std::string::npos) {
                    eJson.replace(position, 1, "\\\"");
                    position += 2;
                }
                
                std::string command = "node ../api/test.js \"" + eJson + "\"";
                int result = system(command.c_str());
                
                if (result != 0) {
                    std::cerr << "loi khi goi API!" << std::endl;
                }
    
                break;
            }
            if (option == int(Menu::EXIT)) {
                Shop shop;
                break;
            }
        }
    }

    std::cout << "\033[?25h";
    return 0;
}