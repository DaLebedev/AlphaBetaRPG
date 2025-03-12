/*
 * Author(s): Daniel Lebedev
 * Description: Struct defines viable classes and their stats.
 */
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H
#include <string>
#include "Item.h"

using namespace std;

// All classes have name, base HP and a special ability
struct PlayerClass {
    string className;
    int maxHp;
    Weapon* weapon;
};

// Declare viable classes
extern const PlayerClass WARRIOR;
extern const PlayerClass MAGE;
extern const PlayerClass ROGUE;


#endif // PLAYERCLASS_H
