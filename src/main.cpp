#include <iostream>
#include <conio.h>
#include "Shop.hpp"
#include "Player.hpp"
#include "data/Data.hpp"
#include <vector>
#include "GameFlow/Character.hpp"

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
            }
            if (option == int(Menu::EXIT)) {
                player.printPlayerInventory();
                getch();
                break;
            }
        }
    }

    std::cout << "\033[?25h";
    return 0;
}