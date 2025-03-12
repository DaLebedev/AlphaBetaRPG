/*
 * Author(s): Daniel Lebedev
 * Description: Defines Player class functions.
 */
#include "Player.h"

// Add item to player's inventory
void Player::addItem(Item* item) {
    // Loop through inventory, if item exists, increase quantity
    for (auto& pair : inventory) {
        if (pair.first == item) {
            pair.second += 1;
            return;
        }
    }

    // If item not in inventory already, add new Item to inventory
    inventory.push_back(make_pair(item, 1));
}

// Remove item from player's inventory
void Player::removeItem(Item* item) {
    // Loop through inventory and create iterator to handle removal
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->first == item) {
            // If more than one item, update quantity
            if (it->second > 1) {
                it->second -= 1;
            // If only one item, remove from inventory completely
            } else {
                inventory.erase(it);
            }
            return;
        }
    }
}

// Use item in player's inventory
void Player::useItem(int index) {
    // If valid selection, use item
    if (index >= 0 && index < inventory.size()) {
        Item* item = inventory[index].first;
        if (typeid(*item) != typeid(Weapon)) {
            Consumable* consumable = dynamic_cast<Consumable*>(item);
            item->use();
            currHealth = min(playerClass.maxHp, currHealth + consumable->getHealAmt());
            cout << "Health: " << currHealth;
            removeItem(item);
        } else {
            cout << "\nNot a Consumable!" << endl;
        }
    }
}

// Display inventory with index
void Player::displayInventory(bool inCombat) {
    string selection;
    int index;
    // Print inventory
    cout << "\nInventory:" << endl;
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i << ": " << inventory[i].first->getName() << " (x" << inventory[i].second << ")" << endl;
    }

    while (true) {
        cout << "\nWhat would you like to do?" << endl;
        // If not in combat prompt to equip weapon
        if (!inCombat) {
            cout << "1 - Equip Weapon" << endl;
            // If in combat prompt to use consumable
        } else {
            cout << "1 - Use Consumable" << endl;
        }
        cout << "2 - Close Inventory" << endl;
        cin >> selection;

        // If not in combat equip weapon
        if (selection == "1" && !inCombat) {
            equipWeapon();
            // If in combat, prompt for consumable index
        } else if (selection == "1" && inCombat) {
            cout << "\nItem index: ";
            cin >> index;
            // If valid input use consumable
            if (index < inventory.size()) {
                useItem(index);
                // Handle invalid input
            } else {
                cout << "\nInvalid index. No items used." << endl;
            }
            // Close inventory
        } else if (selection == "2") {
            break;
            // Handle invalid input
        }else {
            cout << "\nInvalid selection! Try again!" << endl;
        }
    }
}

// Equips selected weapon
void Player::equipWeapon() {
    int index;
    while (true) {
        // Prompt user to select weapon
        cout << "\nEnter the index of the weapon." << endl;
        cin >> index;

        if (index < inventory.size()) {
            Item* item = inventory[index].first;
            Weapon* weapon = dynamic_cast<Weapon*>(item);
            // If valid weapon selected equip weapon
            if (weapon) {
                setEquippedWeapon(weapon);
                cout << "\nEquipped " << getEquippedWeapon()->getName() << endl;
                break;
            // If consumable selected print message
            } else {
                cout << "\nNot a weapon." << endl;
                break;
            }
        // Handle invalid input
        } else {
            cout << "\nInvalid index." << endl;
            break;
        }
    }
}

