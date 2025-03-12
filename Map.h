/*
 * Author(s): Daniel Lebedev
 * Description: Map class represents the world map with a full map and player view.
 */

#ifndef MAP_H
#define MAP_H
#include <vector>
#include <iostream>
#include "NPC.h"
#include "Enemy.h"
#include "Combat.h"

using namespace std;

// Constant vars for map
static const int MAP_WIDTH = 25;
static const int MAP_HEIGHT = 9;
static const char FOG = '-';
static const char WALL = '#';
static const char EMPTY = ' ';
static const char PLAYER = '@';
static const char MERCHANT = '$';
static const char ENEMY = '!';
static const char ENDPOINT = '=';

class Map {
private:
    // Map member variables
    vector<vector<char>> fullMap;
    vector<vector<char>> playerMap;
    vector<NPC> npcs;
    vector<Enemy> enemies;
    int playerX, playerY;

public:
    // Function declarations
    Map();
    void renderMap();
    bool checkValidDir(char dir) const;
    void moveCharacter(char dir, Player& player);
    void updatePlayerMap();
    void checkInteractions(char dir, Player& player);
    void updateEnemies(Enemy* enemy);
    bool checkWin();

    // Getters
    int getPlayerX() { return playerX; }
    int getPlayerY() { return playerY; }
};

#endif // MAP_H
