/*
 * Author(s): Daniel Lebedev, Xavier Bailey
 * Description: Defines Enemies stats and abilities.
 */

#include "Enemy.h"
#include "Item.h"
#include <iostream>

Enemy::Enemy(string n, int h, int d, string w, int x, int y, Item* loot)
    : name(n), health(h), damage(d), weapon(w), x(x), y(y), loot(loot){
}

void Enemy::attack() {
    cout << "\n" << name << " attacks and deals " << damage << " damage with " << weapon << "!" << endl;
}

// SwarmOfBats - Stats
SwarmOfBats::SwarmOfBats(int x, int y, Item* loot)
    : Enemy("Swarm of Bats", 60, 10, "sharp fangs", x, y, loot) {
}

// Goblin - Stats
Goblin::Goblin(int x, int y, Item* loot)
    : Enemy("Goblin", 75, 8, "dagger", x, y, loot) {
}

// Skeleton - Stats
Skeleton::Skeleton(int x, int y, Item* loot)
    : Enemy("Skeleton", 85, 10, "bone sword", x, y, loot) {
}

// DarkMage - Stats
DarkMage::DarkMage(int x, int y, Item* loot)
    : Enemy("Dark Mage", 120, 12, "staff", x, y, loot) {
}

// GhostKnight - Stats
GhostKnight::GhostKnight(int x, int y, Item* loot)
    : Enemy("Ghost Knight", 150, 15, "soul sword", x, y, loot) {
}

// Dragon - Stats
Dragon::Dragon(int x, int y, Item* loot)
    : Enemy("Dragon", 250, 20, "fire breath", x, y, loot) {
}


// Instantiate enemies
SwarmOfBats BATS1(3, 3, &LESSER_HEALTH);
SwarmOfBats BATS2(5, 7, &LESSER_HEALTH);
Goblin GOBLIN1(1, 7, &LESSER_HEALTH);
Goblin GOBLIN2(11, 5, &LESSER_HEALTH);
Skeleton SKELETON1(7,1, &GREATER_HEALTH);
Skeleton SKELETON2(13,7, &GREATER_HEALTH);
DarkMage DARK_MAGE1(15,3, &GREATER_HEALTH);
DarkMage DARK_MAGE2(19,1, &GREATER_HEALTH);
GhostKnight GHOST_KNIGHT1(23,7, &EPIC_HEALTH);
GhostKnight GHOST_KNIGHT2(19,7, &EPIC_HEALTH);
Dragon DRAGON(23,1, &EPIC_HEALTH);



