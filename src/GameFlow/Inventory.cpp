#include "Inventory.hpp"

namespace Inventory {
    std::vector<std::string> items;

    void addItem(const std::string& item) {
        items.push_back(item);
    }

    void removeItem(const std::string& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    bool hasItem(const std::string& item) {
        return std::find(items.begin(), items.end(), item) != items.end();
    }

    void listItems() {
        for (size_t i = 0; i < items.size(); i += itemsPerPage) {
            /*
                Duy oi, dinh nghia boxHeight nam o dau vay
                                        |
                                        v
            */
            // for (int row = 0; row < boxHeight; ++row) {
            //     for (size_t j = i; j < i + itemsPerPage && j < items.size(); ++j) {
            //         std::cout << "+------------------+ ";
            //     }
            //     std::cout << std::endl;

            //     for (size_t j = i; j < i + itemsPerPage && j < items.size(); ++j) {
            //         std::cout << "| " << std::setw(boxWidth - 3) << std::left;
            //         if (row == 0) {
            //             std::cout << items[j].substr(0, boxWidth - 3);
            //         } else if (row == 1) {
            //             std::cout << "Type: " << "Weapon/Armor"; // Replace with actual type
            //         } else if (row == 2) {
            //             std::cout << "Attribute: " << "AttributeValue"; // Replace with actual attribute
            //         }
            //         std::cout << " | ";
            //     }
            //     std::cout << std::endl;
            // }

            for (size_t j = i; j < i + itemsPerPage && j < items.size(); ++j) {
                std::cout << "+------------------+ ";
            }
            std::cout << std::endl;
        }
    }

    void show(Player &player) {
        bool inInventory = true;
        std::pair<int, int> inventoryPos = {0, 0};
        int currentPage = 1;

        // get the item list
        std::vector<Weapon> ws = player.getWeaponList();
        std::vector<Armor> as = player.getArmorList();
        std::vector<Item*> items;
    
        for (auto& w : ws) items.push_back(&w);
        for (auto& a : as) items.push_back(&a);
        int maxPage = items.size() / 16;

        int start = (currentPage - 1) * 16;
        int end = std::min(start + 16, (int) items.size());

        while (inInventory) {
            system("cls");

            std::cout << "Inventory: " << std::endl;
            // displayInventory(inventoryPos);
            std::cout << "Press 'esc' to exit inventory, 'e' for next page, 'q' for previous page" << std::endl;
            
            char key = _getch();
            switch (key) {
                case 'w':
                case 72: // Up arrow
                    if (inventoryPos.second > 0) {
                        inventoryPos.second--;
                    }
                    break;
                case 's':
                case 80: // Down arrow
                    if (inventoryPos.second < itemsPerCol - 1) {
                        inventoryPos.second++;
                    }
                    break;
                case 'a':
                case 75: // Left arrow
                    if (inventoryPos.first > 0) {
                        inventoryPos.first--;
                    }
                    break;
                case 'd':
                case 77: // Right arrow
                    if (inventoryPos.first < itemsPerRow - 1) {
                        inventoryPos.first++;
                    }
                    break;
                case 'e': // next page
                    if (currentPage < maxPage) {
                        currentPage++;
                    }
                    break;
                case 'q': // previous page
                    if (currentPage > 0) {
                        currentPage--;
                    }
                    break;
                case 27: // Escape key
                    inInventory = false;
                    break;
                case 13: // Enter key
                    int index = (currentPage - 1) * 16 + inventoryPos.first + inventoryPos.second * itemsPerRow;
                    Item& selected = *items[index];
                    bool isEquipped = selected.checkIsEquipped();
                    if (Choice::showEquip(selected.getName(), isEquipped) == true) {
                        if (isEquipped) {
                            // if (Weapon* w = dynamic_cast<Weapon*>(&selected)) {
                            //     player.unequipWeapon(*w);
                            // } else if (Armor* a = dynamic_cast<Armor*>(&selected)) {
                            //     player.unequipArmor(*a);
                            // }
                        } else {
                            if (Weapon* w = dynamic_cast<Weapon*>(&selected)) {
                                player.equipWeapon(*w);
                            } else if (Armor* a = dynamic_cast<Armor*>(&selected)) {
                                player.equipArmor(*a);
                            }
                    }
                    
                    break;
                default:
                    break;
            }
        }
    }
    void displayInventory(Player &player) {}
}
