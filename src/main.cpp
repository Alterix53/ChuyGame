#include <iostream>
#include <conio.h>
#include "Shop.hpp"
#include "Player.hpp"
#include "data/Data.hpp"
#include <vector>
#include "GameFlow/Character.hpp"
#include "Utils.hpp"

const int OPTION = 4;

enum class Menu {
    CHARACTER,
    SHOP,
    PLAY,
    EXIT
};

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
            if (option == int(Menu::PLAY)) {
                std::string weaponJson = "{\"weapon\":[" + makeJsonWeapon(player.getWeapon(0)) + "," + makeJsonWeapon(player.getWeapon(1)) +  "],";
                std::string armorJson = "\"armor\":[" + makeJsonArmor(player.getArmor(ArmorPart::HELMET)) + "," + makeJsonArmor(player.getArmor(ArmorPart::LEGGINGS)) + "," + makeJsonArmor(player.getArmor(ArmorPart::BOOTS)) + "," + makeJsonArmor(player.getArmor(ArmorPart::CHESTPLATE)) + "]}";
                
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
                player.printPlayerInventory();
                break;
            }
        }
    }

    std::cout << "\033[?25h";
    return 0;
}