/*
 * Author(s): Daniel Lebedev
 * Description: Instantiate the 3 valid player classes and their abilities.
 */
#include "PlayerClass.h"

// Define viable classes
const PlayerClass WARRIOR = {"Warrior", 80, &CLUB};
const PlayerClass MAGE = {"Mage", 100, &STAFF};
const PlayerClass ROGUE = {"Rogue", 120, &DAGGER};
