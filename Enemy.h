/*
 * Author(s): Daniel Lebedev, Xavier Bailey
 * Description: Enemy parent class acts as base for various enemy types.
 */
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "Item.h"

using namespace std;

 // parent enemy class, each enemy will have name, health, damage, weapon, and ability
class Enemy {
protected:
    string name;
    int health;
    int damage;
    string weapon;
    Item* loot;
    int x, y;

public:
    Enemy(string n, int h, int d, string w, int x, int y, Item* loot);

    virtual void attack(); // attack function

    // Getters & Setters
    string getName() const { return name; }

    int getHealth() const { return health; }
    void setHealth(int health) { this->health = health; }

    int getDamage() const { return damage; }

    string getWeapon() const { return weapon; }

    int getX() const { return x; }
    int getY() const { return y; }

    Item* getLoot() const { return loot; }
};

class SwarmOfBats : public Enemy { // SwarmOfBats - A dark and sinister swarm of bats that spreads fear and chaos in the dungeon.
public:
    SwarmOfBats(int x, int y, Item* loot);
};

class Goblin : public Enemy { // Goblin - A mischievous goblin looking to cause trouble and pain.
public:
    Goblin(int x, int y, Item* loot);
};

class Skeleton : public Enemy { // Skeleton - A restless skeleton warrior, forever guarding the treasures of the dungeon.
public:
    Skeleton(int x, int y, Item* loot);
};

class DarkMage : public Enemy { // DarkMage - A malicious mage whose dark magic drains the life force of any who cross its path.
public:
    DarkMage(int x, int y, Item* loot);
};


class GhostKnight : public Enemy { // GhostKnight - An undead knight haunting the dungeon, seeking revenge on those who disturb its eternal rest.
public:
    GhostKnight(int x, int y, Item* loot);
};

class Dragon : public Enemy { // Dragon - A giant drake guarding the exit to the dungeon.
public:
    Dragon(int x, int y, Item* loot);
};


extern SwarmOfBats BATS1;
extern SwarmOfBats BATS2;
extern Goblin GOBLIN1;
extern Goblin GOBLIN2;
extern Skeleton SKELETON1;
extern Skeleton SKELETON2;
extern DarkMage DARK_MAGE1;
extern DarkMage DARK_MAGE2;
extern GhostKnight GHOST_KNIGHT1;
extern GhostKnight GHOST_KNIGHT2;
extern Dragon DRAGON;


#endif
