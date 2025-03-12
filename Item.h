/*
 * Author(s): Daniel Lebedev
 * Description: Item class represents items which can be either weapon or consumable.
 */
#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;

// Abstract Item class
class Item {
protected:
    // All items have a name
    string name;
public:
    // Base constructor & function
    Item(string name): name(name) {}
    virtual void use() = 0;

    // Getters
    string getName() { return name; }
};

// Weapon inherits and overrides Item class
class Weapon : virtual public Item {
protected:
    // Weapons have dmg and dmg type
    int damage;
    string dmgType;
public:
    // Weapon constructor calls Item constructor
    Weapon(string name, int damage) : Item(name), damage(damage) {}

    // Override virtual use function
    virtual void use() {
        cout << "\nYou attack with " << name << " for " << damage << " dmg." << endl;
    }

    // Getter
    int getDamage() { return damage; }
};

// Consumable inherits and overrides Item class
class Consumable : virtual public Item {
protected:
    // Consumables have heal amt
    int healAmt;
public:
    // Consumable constructor calls Item constructor
    Consumable(string name, int healAmt) : Item(name), healAmt(healAmt) {}

    // Override virtual use function
    virtual void use() {
        cout << "\nHealing w/ " << name << " for "  << healAmt << " hp." << endl;
    }

    // Getter
    int getHealAmt() { return healAmt; }
};

// Define weapons
extern Weapon CLUB;
extern Weapon STAFF;
extern Weapon DAGGER;
extern Weapon WARHAMMER;
extern Weapon SPELL_TOME;
extern Weapon SWORD;

// Define consumables
extern Consumable LESSER_HEALTH;
extern Consumable GREATER_HEALTH;
extern Consumable EPIC_HEALTH;

#endif // ITEM_H
