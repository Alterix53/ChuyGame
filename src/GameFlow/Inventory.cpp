#include "Inventory.hpp"

namespace Inventory {
    // std::vector<std::string> items;

    // void addItem(const std::string& item) {
    //     items.push_back(item);
    // }

    // void removeItem(const std::string& item) {
    //     items.erase(std::remove(items.begin(), items.end(), item), items.end());
    // }

    // bool hasItem(const std::string& item) {
    //     return std::find(items.begin(), items.end(), item) != items.end();
    // }
    
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

        int maxPage = items.size() / 16 + 1;
        int start = (currentPage - 1) * 16;
        int end = (start + 16 < (int) items.size()) ? start + 16 : items.size();

        while (inInventory) {
            system("cls");
            displayInventory(items, player, inventoryPos, currentPage);
    
            std::cout << "Press 'esc' to exit inventory, 'e' for next page, 'q' for previous page" << std::endl;
            // std::cout << "vi tri hien tai: " << inventoryPos.first << " " << inventoryPos.second << std::endl;
            char key = _getch();
            switch (key) {
                case 'w':
                case 72: // Up arrow
                    if (inventoryPos.first > 0) {
                        inventoryPos.first--;
                    }
                    break;
                case 's':
                case 80: // Down arrow
                    if (inventoryPos.first < itemsPerCol - 1) {
                        if (currentPage == items.size() / itemsPerPage  + 1 
                            && (inventoryPos.first + 1) * itemsPerRow + inventoryPos.second + 1 > items.size() % itemsPerPage) {
                                break;
                        }
                        inventoryPos.first++;
                    }
                    break;
                case 'a':
                case 75: // Left arrow
                    if (inventoryPos.second > 0) {
                        inventoryPos.second--;
                    }
                    break;
                case 'd':
                case 77: // Right arrow
                    if (inventoryPos.second < itemsPerRow - 1) {
                        if (currentPage == items.size() / itemsPerPage  + 1 
                            && inventoryPos.first * itemsPerRow + inventoryPos.second + 1 >= items.size() % itemsPerPage) {
                                break;
                        }
                        inventoryPos.second++;
                    }
                    break;
                case 'e': // next page
                    if (currentPage < maxPage) {
                        currentPage++;
                    }
                    inventoryPos = {0, 0};
                    break;
                case 'q': // previous page
                    if (currentPage > 1) {
                        currentPage--;
                    }
                    inventoryPos = {0, 0};
                    break;
                case 27: // Escape key
                    inInventory = false;
                    break;
                case 13: // Enter key 
                {
                    int pos = (currentPage - 1) * 16 + inventoryPos.second + inventoryPos.first * itemsPerRow;
                    if (pos >= (int) items.size()) {
                        break;
                    }
                    Item& select = *items[pos];
                    bool Equipped = select.checkIsEquipped();
                    if (Choice::showEquip(select.getName(), Equipped) == true) {
                        if (Equipped) {
                            if (Weapon* w = dynamic_cast<Weapon*>(&select)) {
                                
                                // reset equipped status
                                player.setEquippedWeapon(false, pos); 
                                select.setEquipped(false);
                                w->setEquipped(false);
                                // unequipped by slot
                                if (select.getName() == player.getFirstWeapon().getName()) {
                                    player.unequipWeapon(1);
                                } else if (w->getName() == player.getSecondWeapon().getName()) {
                                    player.unequipWeapon(2);
                                }
                            } else if (Armor* a = dynamic_cast<Armor*>(&select)) {
                                ArmorPart part = a->getPart();
                                player.setEquippedArmor(false, pos - player.getWeaponList().size());
                                a->setEquipped(false);
                                select.setEquipped(false);
                                player.unequipArmor(part);
                            }
                        } else { // unequip case
                            // if the item is a weapon, let player choose slot and equip
                            if (Weapon* w = dynamic_cast<Weapon*>(&select)) {
                                player.setEquippedWeapon(true, pos);
                                w->setEquipped(true);
                                select.setEquipped(true);
                                // let player choose slot
                                std::cout << "Choose a slot to equip: " << std::endl;
                                int slot;
                                std::cout << "Choose slot (1 or 2): ";
                                while (!(std::cin >> slot) || (slot != 1 && slot != 2)) {
                                    std::cin.clear();                   // clear the cin's bug
                                    std::cin.ignore(1000, '\n');        // clear all the \n
                                    std::cout << "Invalid slot, choose again: ";
                                }
                                int lastWeapIndex = 0;
                                // change the first slot weapon
                                if (slot == 1) {
                                    // if there is no weapon before, just equip it
                                    if (player.getFirstWeapon().getName() == "Unknown") {
                                        player.equipWeapon(*w, slot);
                                    }

                                    // if there IS a weapon, change it directly
                                    else {
                                        // find the last weapon in the player's list to update equip status
                                        std::string lastWeapName = player.getFirstWeapon().getName();
                                        for (int i = 0; i < (int) ws.size(); i++) {
                                            if (ws[i].getName() == lastWeapName) {
                                                lastWeapIndex = i;
                                                break;
                                            }
                                        }
                            
                                        // show two weapons for comparison
                                        Inventory::compareWeapon(player, player.getFirstWeapon(), *w); 

                                        // change weapon's status
                                        player.setEquippedWeapon(false, lastWeapIndex);
                                        items[lastWeapIndex]->setEquipped(false);
                                        player.equipWeapon(*w, slot);
                                    }
                                } else { // (slot == 2)
                                    // if there is no weapon before, just equip it
                                    if (player.getSecondWeapon().getName() == "Unknown") {
                                        player.equipWeapon(*w, slot);
                                    }

                                    // if there IS a weapon, change it directly
                                    else {
                                        // find the last weapon in the player's list to update equip status
                                        std::string lastWeapName = player.getSecondWeapon().getName(); 
                                        for (int i = 0; i < (int) ws.size(); i++) {
                                            if (ws[i].getName() == lastWeapName) {
                                                lastWeapIndex = i;
                                                break;
                                            }
                                        }
                                        // show two weapons for comparison
                                        Inventory::compareWeapon(player, player.getSecondWeapon(), *w);
                                        // change the status and equip
                                        player.setEquippedWeapon(false, lastWeapIndex);
                                        items[lastWeapIndex]->setEquipped(false);
                                        player.equipWeapon(*w, slot);
                                    }
                                }
                            // if the chosen item is armor:
                            } else if (Armor* a = dynamic_cast<Armor*>(&select)) {

                                // set equip status for that armor (in both player's inventory and the current list work in inventory)
                                player.setEquippedArmor(true, pos - player.getWeaponList().size());
                                a->setEquipped(true);
                                select.setEquipped(true);

                                // if the current part is equipped by another armor, find and change the status
                                if (player.getArmor(a->getPart()).getName() != "Unknown") {

                                    // find the last armor
                                    Armor lastArmor = player.getArmor(a->getPart()); int lastArmorIndex = 0;
                                    for (int i = 0; i < (int) as.size(); i++) {
                                        if (as[i].getName() == lastArmor.getName()) {
                                            lastArmorIndex = i;
                                            break;
                                        }
                                    }
                                    Inventory::compareArmor(player, player.getArmor(a->getPart()), *a);
                                    // change that armor's status
                                    player.setEquippedArmor(false, lastArmorIndex);
                                    items[lastArmorIndex + ws.size()]->setEquipped(false);
                                }
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
        std::cout << "The weapon will be replaced:" << std::endl;
        std::cout << "__________________________________              __________________________________" << std::endl;
        std::cout << "| Name: " << w1.getName() << std::string(25 - w1.getName().length(), ' ') << "|              | Name: " << w2.getName() << std::string(25 - w2.getName().length(), ' ') << "|" << std::endl;
        std::cout << "| Type: " << w1.getWeaponTypeString() << std::string(25 - w1.getWeaponTypeString().length(), ' ');
        std::cout << "|              | Type: " << w2.getWeaponTypeString() << std::string(25 - w2.getWeaponTypeString().length(), ' ') << "|" << std::endl;
        std::cout << "| Damage: " << w1.getDamage() << "    Atkspd: " << w1.getAtkSpeed() << std::string(25 - std::to_string(w1.getDamage()).length() - std::to_string(w1.getAtkSpeed()).length() - 7, ' ');
        std::cout << "|   ------->   | Damage: " << w2.getDamage() << "    Atkspd: " << w2.getAtkSpeed() << std::string(25 - std::to_string(w2.getDamage()).length() - std::to_string(w2.getAtkSpeed()).length() - 7, ' ') << "|" << std::endl;
        std::cout << "|                                |              |                                |" << std::endl;
        std::cout << "|________________________________|              |________________________________|" << std::endl;
        std::cout << "Press any key to continue. " << std::endl;
        getch();
    }

    void compareArmor(Player &player, Armor a1, Armor a2) {
        system("cls");
        std::cout << "The armor will be replaced:" << std::endl;
        std::cout << "__________________________________              __________________________________" << std::endl;
        std::cout << "| Name: " << a1.getName() << std::string(25 - a1.getName().length(), ' ') << "|              | Name: " << a2.getName() << std::string(25 - a2.getName().length(), ' ') << "|" << std::endl;
        std::cout << "| Type: " << a1.getArmorTypeString() << std::string(25 - a1.getArmorTypeString().length(), ' ');
        std::cout << "|              | Type: " << a2.getArmorTypeString() << std::string(25 - a2.getArmorTypeString().length(), ' ') << "|" << std::endl;
        std::cout << "| Health: " << a1.getHealth() << " Def: " << a1.getDefense() << std::string(25 - std::to_string(a1.getHealth()).length() - std::to_string(a1.getDefense()).length() - 8, ' ');
        std::cout << "|   ------->   | Health: " << a2.getHealth() << " Def: " << a2.getDefense() << std::string(25 - std::to_string(a2.getHealth()).length() - std::to_string(a2.getDefense()).length() - 8, ' ') << "|" << std::endl;
        std::cout << "|                                |              |                                |" << std::endl;
        std::cout << "|________________________________|              |________________________________|" << std::endl;
        std::cout << "Press any key to continue. " << std::endl;
        getch();
    }
    
    // ching add ham ben duoi nhe
    std::vector<std::string> splitLines(const std::string& text) {
        std::vector<std::string> lines;
        std::stringstream ss(text);
        std::string line;
        while (std::getline(ss, line, '\n')) {
            lines.push_back(line);
        }
        return lines;
    }
    
    void drawGrid(const std::vector<Item*>& data, int cols, int rows, int indexMove, int pageNumber) {
        int colWidth = 28;
        int totalWidth = cols * (colWidth + 1) + 1;
        int consoleWidth = 166; // ~ mode con / columns ~ 166 (my computer <("))
        int padding = std::max(0, consoleWidth - totalWidth) - 10; // can chinh qua ben phai man hinh de, lam gi thi khong biet...
    
        int itemsPerPage = rows * cols;
        int startIndex = (pageNumber - 1) * itemsPerPage;
        int index = startIndex;

        char topLeft = 218, topRight = 191, bottomLeft = 192, bottomRight = 217;
        char horizontal = 196, vertical = 179, cross = 197;
        char topMid = 194, bottomMid = 193, leftMid = 195, rightMid = 180;

        std::cout << std::string(padding, ' ');
        for (int j = 0; j < cols; j++) {
            std::cout << (j == 0 ? topLeft : topMid) << std::string(colWidth, horizontal);
        }
        std::cout << topRight << '\n';

        for (int i = 0; i < rows; i++) {
            std::vector<std::vector<std::string>> rowLines(cols);
        
            for (int j = 0; j < cols; j++) {
                if (index < data.size()) {
                    rowLines[j] = splitLines(data[index]->toString());
                    index++;
                }
            }
        
            int maxLines = 4;
        
            for (int lineIndex = 0; lineIndex < maxLines; lineIndex++) {
                std::cout << std::string(padding, ' ');
                for (int j = 0; j < cols; j++) {
                    // std::string text = std::to_string(i * 4 + j);
                    std::string text = (lineIndex < rowLines[j].size()) ? rowLines[j][lineIndex] : "";
                    if (i * 4 + j == indexMove) {
                        text = utils::colorString(text, Color::YELLOW);
                        std::cout << vertical << std::left << std::setw(colWidth + 11) << text;
                    }
                    else std::cout << vertical << std::left << std::setw(colWidth) << text;
                }
                std::cout << vertical << '\n';
            }
        
            if (i < rows - 1) {
                std::cout << std::string(padding, ' ');
                for (int j = 0; j < cols; j++) {
                    std::cout << (j == 0 ? leftMid : cross) << std::string(colWidth, horizontal);
                }
                std::cout << rightMid << '\n';
            }
        }
        
        std::cout << std::string(padding, ' ');
        for (int j = 0; j < cols; j++) {
            std::cout << (j == 0 ? bottomLeft : bottomMid) << std::string(colWidth, horizontal);
        }
        std::cout << bottomRight << '\n';
    }
    
    void displayInventory(std::vector<Item*> &items, Player &player, std::pair<int, int> inventoryPos, int pageNumber) {
        system("cls");
        int index = inventoryPos.first * itemsPerRow + inventoryPos.second;

        drawGrid(items, itemsPerCol, itemsPerRow, index, pageNumber);
    }
    
    int getVisibleLength(const std::string& str) {
        std::regex colorCodeRegex("\033\\[[0-9;]*m");
        return std::regex_replace(str, colorCodeRegex, "").length();
    }
}