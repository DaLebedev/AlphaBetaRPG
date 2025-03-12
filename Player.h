/*
 * Author(s): Daniel Lebedev
 * Description: Represents the player character. Has name, health, class, and inventory.
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "PlayerClass.h"
#include "Item.h"
#include <vector>
using namespace std;

class Player {
private:
    // Player member variables
    string name;
    PlayerClass playerClass;
    int currHealth;
    int kills = 0;
    Weapon* equippedWeapon;
public:
    // Inventory is public so weapon can be accessed
    vector<pair<Item*, int>> inventory;

    // Currhealth determined by class' max health
    Player(string name, PlayerClass playerClass):
        name(name), playerClass(playerClass), currHealth(playerClass.maxHp), equippedWeapon(playerClass.weapon) {}

    // Function declarations
    void addItem(Item* item);
    void removeItem(Item* item);
    void useItem(int index);
    void displayInventory(bool inCombat = false);
    void equipWeapon();

    // Getters & Setters
    string getName() { return name; }
    PlayerClass getPlayerClass() { return playerClass; }

    int getCurrHealth() { return currHealth; }
    void setCurrHealth(int currHealth) { this->currHealth = currHealth; }

    int getKills() { return kills; }
    void setKills(int kills) { this->kills = kills; }

    Weapon* getEquippedWeapon() { return equippedWeapon; }
    void setEquippedWeapon(Weapon* equippedWeapon) { this->equippedWeapon = equippedWeapon; }
};

#endif // PLAYER_H
