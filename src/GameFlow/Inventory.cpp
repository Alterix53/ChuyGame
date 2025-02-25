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
    
    void show(Player &player) {
        bool inInventory = true;
        std::pair<int, int> inventoryPos = {0, 0};
        int currentPage = 1;

        // get the item list
        std::vector<Weapon> ws = player.getWeaponList();
        std::vector<Armor> as = player.getArmorList();

        // tao mot vector chua tat ca cac item cua player
        std::vector<Item*> items;
        for (auto& w : ws) items.push_back(&w);
        for (auto& a : as) items.push_back(&a);

        // so trang can co cua inventory
        int maxPage = (items.size()) / 16 + 1;
        int start = (currentPage - 1) * 16;                                         // index dau tien cua trang hien tai
        int end = (start + 16 < (int) items.size()) ? start + 16 : items.size();    // index cuoi cung cua trang hien tai

        while (inInventory) {
            system("cls");

            std::cout << "Inventory: " << std::endl;

            // ham display de in ra cac item co index tu start den end
            // displayInventory(player, inventoryPos);

            // sau khi code xong ham display, xoa 3 dong duoi
            for (int i = start; i < end; i++) {
                std::cout << items[i]->getName() << std::endl;
            }

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
                {
                    int pos = (currentPage - 1) * 16 + inventoryPos.first + inventoryPos.second * itemsPerRow;
                    if (pos >= (int) items.size()) {
                        break;
                    }
                    
                    // show the item detail
                    Item& select = *items[pos];
                    bool Equipped = select.checkIsEquipped();
                    if (Choice::showEquip(select.getName(), Equipped) == true) {
                        if (Equipped) {
                            if (Weapon* w = dynamic_cast<Weapon*>(&select)) {
                                // unequipped by slot
                                if (w->getName() == player.getFirstWeapon().getName()) {
                                    w->setEquipped(false);
                                    player.unequipWeapon(1);
                                } else if (w->getName() == player.getSecondWeapon().getName()) {
                                    w->setEquipped(false);
                                    player.unequipWeapon(2);
                                }
                            } else if (Armor* a = dynamic_cast<Armor*>(&select)) {
                                ArmorPart part = a->getPart();
                                player.unequipArmor(part);
                            }
                        } else {
                            // if the item is a weapon, let player choose slot and equip
                            if (Weapon* w = dynamic_cast<Weapon*>(&select)) {
                                // find the empty slot
                                if (player.getFirstWeapon().getName() == "Unknown") {
                                    player.equipWeapon(*w, 1);
                                } else if (player.getSecondWeapon().getName() == "Unknown") {
                                    player.equipWeapon(*w, 2);
                                } else {
                                    // if both slots are occupied, let player choose slot
                                    std::cout << "Both slots are occupied, choose a slot to equip: " << std::endl;
                                    int slot;
                                    std::cout << "Choose slot (1 or 2): ";
                                    std::cin >> slot;
                                    while (slot != 1 && slot != 2) {
                                        std::cout << "Invalid slot, choose again: ";
                                        std::cin >> slot;
                                    }
                                    player.equipWeapon(*w, slot);
                                }
                            } else if (Armor* a = dynamic_cast<Armor*>(&select)) {
                                player.equipArmor(*a);
                            }
                        }
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    void compareWeapon(Player &player, Weapon w1, Weapon w2) {
        system("cls");
        std::cout << "____________________________              ____________________________" << std::endl;
        std::cout << "| Name: " << w1.getName() << std::string(24 - w1.getName().length(), ' ') << "|        \\\\    | Name: " << w2.getName() << std::string(24 - w2.getName().length(), ' ') << "|" << std::endl;
        std::cout << "| Type: " << w1.getWeaponTypeString() << std::string(24 - w1.getWeaponTypeString().length(), ' ');
        std::cout << "|        \\\\    | Type: " << w2.getWeaponTypeString() << std::string(24 - w2.getWeaponTypeString().length(), ' ') << "|" << std::endl;
        std::cout << "| Damage: " << w1.getDamage() << " Atkspd: " << w1.getAtkSpeed() << std::string(24 - std::to_string(w1.getDamage()).length() - std::to_string(w1.getAtkSpeed()).length() - 10, ' ');
        std::cout << "|   ========   | Damage: " << w2.getDamage() << " Atkspd: " << w2.getAtkSpeed() << std::string(24 - std::to_string(w2.getDamage()).length() - std::to_string(w2.getAtkSpeed()).length() - 10, ' ') << "|" << std::endl;
        std::cout << "|                          |         //   |                          |" << std::endl;
        std::cout << "|__________________________|        //    |__________________________|" << std::endl;
    }

    void compareArmor(Player &player, Armor a1, Armor a2) {
        system("cls");
        std::cout << "____________________________              ____________________________" << std::endl;
        std::cout << "| Name: " << a1.getName() << std::string(24 - a1.getName().length(), ' ') << "|        \\\\    | Name: " << a2.getName() << std::string(24 - a2.getName().length(), ' ') << "|" << std::endl;
        std::cout << "| Type: " << a1.getArmorTypeString() << std::string(24 - a1.getArmorTypeString().length(), ' ');
        std::cout << "|        \\\\    | Type: " << a2.getArmorTypeString() << std::string(24 - a2.getArmorTypeString().length(), ' ') << "|" << std::endl;
        std::cout << "| Health: " << a1.getHealth() << " Def: " << a1.getDefense() << std::string(24 - std::to_string(a1.getHealth()).length() - std::to_string(a1.getDefense()).length() - 10, ' ');
        std::cout << "|   ========   | Health: " << a2.getHealth() << " Def: " << a2.getDefense() << std::string(24 - std::to_string(a2.getHealth()).length() - std::to_string(a2.getDefense()).length() - 10, ' ') << "|" << std::endl;
        std::cout << "|                          |         //   |                          |" << std::endl;
        std::cout << "|__________________________|        //    |__________________________|" << std::endl;
    }
    
    // ching add ham ben duoi nhe
    void displayInventory(Player &player, std::pair<int, int> inventoryPos) {}
}