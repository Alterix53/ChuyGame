#include <iostream>
#include <conio.h>

const int OPTION = 3;

void displayMenu(int option) {
    std::string options[] = {"Character", "Shop", "Play"};

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
    int option = 0;

    while (true) {
        system("cls");
        displayMenu(option);

        char key = getch();

        if (key == 'w' || key == 'W') {
            if (option > 0) {
                option--;
            } else {
                option = OPTION - 1;
            }
        } else if (key == 's' || key == 'S') {
            if (option < OPTION - 1) {
                option++;
            } else {
                option = 0;
            }
        } else if (key == '\n' || key == '\r') {
            break;
        }

    }

    std::cout << "\033[?25h";
    return 0;
}
