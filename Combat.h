/*
 * Author(s): Daniel Lebedev
 * Description: Combat class holds combat functionality.
 */

#ifndef COMBAT_H
#define COMBAT_H
#include <string>
#include <iostream>
#include "Player.h"
#include "Enemy.h"

class Combat
{
public:
    // Combat function definitions
    static void combatDialog(Player& player, Enemy* enemy);
    static void enemyAttack(Player& player, Enemy* enemy);
};

#endif // COMBAT_H
