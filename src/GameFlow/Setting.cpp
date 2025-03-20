#include <iostream>
#include <string>
#include <cctype>
#include <conio.h>
#include <algorithm>
#include "../Player.hpp"

//function to get input with Esc cancellation
std::string getInputWithEsc() {
    std::string input;
    while (true) {
        char ch = _getch(); // Read a character without requiring Enter
        if (ch == 27) {     // Esc key (ASCII 27)
            return "";      // Return empty string to indicate cancellation
        } else if (ch == 13) { // Enter key (ASCII 13)
            return input;      // Return the completed input
        } else if (ch == 8) {  // Backspace (ASCII 8)
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b"; // Erase the last character on screen
            }
        } else if (isprint(ch)) { // Accept only printable characters
            input += ch;
            std::cout << ch;      // Echo the character to the screen
        }
    }
}

namespace Setting {
    void show(Player& player) {
        while (true) {
            system("cls");
            std::cout << "\nPlayer Settings\n";
            std::cout << "---------------\n";
            std::cout << "Current Name: " << player.getName() << "\n";
            std::cout << "Current Discord ID: " << player.getID() << "\n\n";
            std::cout << "1. Change Name\n";
            std::cout << "2. Change Discord ID\n";
            std::cout << "3. Exit\n";
            std::cout << "Choose an option: ";

            char choice = _getch(); // Get immediate key press
            std::cout << choice << "\n"; // Echo the choice

            if (choice == '1') {
                std::cout << "Enter new name (Esc to cancel): ";
                std::string input = getInputWithEsc();
                std::cout << "\n"; // Move to next line after input
                if (input.empty()) {
                    std::cout << "Change canceled.\n";
                } else {
                    player.setName(input);
                    std::cout << "Name updated successfully.\n";
                }
            }
            else if (choice == '2') {
                std::cout << "Enter new Discord ID (18 digits, Esc to cancel): ";
                std::string input = getInputWithEsc();
                std::cout << "\n"; // Move to next line after input
                if (input.empty()) {
                    std::cout << "Change canceled.\n";
                } else if (input.length() == 18 && std::all_of(input.begin(), input.end(), ::isdigit)) {
                    player.setID(input);
                    std::cout << "Discord ID updated successfully.\n";
                } else {
                    std::cout << "Invalid ID. Must be exactly 18 digits.\n";
                }
            }
            else if (choice == '3' || choice == 27) { // Exit on '3' or Esc
                std::cout << "Exiting settings.\n";
                break;
            }
            else {
                std::cout << "Invalid option.\n";
            }
        }
    }
}