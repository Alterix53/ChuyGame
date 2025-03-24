#include <iostream>
#include <conio.h>
#include "Shop.hpp"
#include "Player.hpp"
#include "data/Data.hpp"
#include <vector>
#include "GameFlow/Character.hpp"
#include "Utils.hpp"
#include "GameFlow/Setting.hpp"

const int OPTION = 5;

enum class Menu {
    CHARACTER,
    SHOP,
    SETTING,
    PLAY,
    EXIT
};

void displayMenu(int option) {
    std::string options[] = {"Character", "Shop", "Setting", "Play", "Exit"};

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
    std::cout << "\033[?25l"; 
    // inital data
    Shop shop;
    Player player;
    int option = 0;
    bool isHome = true;
    
    while (isHome) {
        system("cls");
        displayMenu(option);

        char key = getch();        
        if (key == -32) { 
            key = _getch();
        }
        if (key == 'w' || key == 'W' || key == 72) {
            option = (option > 0) ? option - 1 : OPTION - 1;
        } else if (key == 's' || key == 'S' || key == 80) {
            option = (option < OPTION - 1) ? option + 1 : 0;
        } else if (key == '\n' || key == '\r') {   // choose the current option
            if (option == int(Menu::CHARACTER)) {
                Character::show(player);
            } 
            if (option == int(Menu::SHOP)) {
                shop.runShop(player);
            }
            if (option == int(Menu::SETTING)) {
                Setting::show(player);
            }
            if (option == int(Menu::PLAY)) {
                std::string weaponJson = "{\"weapon\":[" + utils::makeJsonWeapon(player.getFirstWeapon()) + "," + utils::makeJsonWeapon(player.getSecondWeapon()) +  "],";
                std::string armorJson = "\"armor\":[" + utils::makeJsonArmor(player.getArmor(ArmorPart::HELMET)) + "," + utils::makeJsonArmor(player.getArmor(ArmorPart::LEGGINGS)) + "," + utils::makeJsonArmor(player.getArmor(ArmorPart::BOOTS)) + "," + utils::makeJsonArmor(player.getArmor(ArmorPart::CHESTPLATE)) + "]}";
                
                std::string json = weaponJson + armorJson;
                json.insert(1, "\"name\":\"" + player.getName() + "\",\"id\":\"" + player.getID() + "\",");

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
                getch();
            }
            if (option == int(Menu::EXIT)) {
                system("cls");
                std::cout << "\t\tCam on ban da choi game\n\n";
                std::cout << "\t\tChuygame - MiSide v2 cua chung toi\n";
                break;
            }
        }
    }

    std::cout << "\033[?25h";
    return 0;
}