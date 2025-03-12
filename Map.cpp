/*
 * Author(s): Daniel Lebedev
 * Description: Defines Map functions.
 */

#include "Map.h"

Map::Map() {
    // Map with everything visible
    fullMap = {
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
        {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL},
        {WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL},
        {WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, ENDPOINT, WALL},
        {WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL},
        {WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, WALL},
        {WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL},
        {WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL},
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
    };

    // Map player sees
    playerMap = vector<vector<char>>(MAP_HEIGHT, vector<char>(MAP_WIDTH, FOG));

    // Initialize player position
    playerX = 1;
    playerY = 1;

    // Place player on map
    fullMap[playerY][playerX] = PLAYER;

    // Add enemies and NPCs to vectors
    enemies.push_back(BATS1);
    enemies.push_back(BATS2);
    enemies.push_back(GOBLIN1);
    enemies.push_back(GOBLIN2);
    enemies.push_back(SKELETON1);
    enemies.push_back(SKELETON2);
    enemies.push_back(DARK_MAGE1);
    enemies.push_back(DARK_MAGE2);
    enemies.push_back(GHOST_KNIGHT1);
    enemies.push_back(GHOST_KNIGHT2);
    enemies.push_back(DRAGON);
    npcs.push_back(QUEST_GIVER1);
    npcs.push_back(QUEST_GIVER2);
    npcs.push_back(QUEST_GIVER3);

    // Add enemies to map
    for (Enemy& enemy : enemies) {
        fullMap[enemy.getY()][enemy.getX()] = ENEMY;
    }

    // Add NPCs to map
    for (NPC& npc : npcs) {
        fullMap[npc.getY()][npc.getX()] = MERCHANT;
    }
}

// Displays player's map
void Map::renderMap() {
    updatePlayerMap();
    cout << "\n";
    for(const auto &row : playerMap) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

// Checks if theres an empty space to move to
bool Map::checkValidDir(char dir) const{
    int x = playerX, y = playerY;
    switch (tolower(dir)) {
        case 'r': x += 1; break;  // Right
        case 'l': x -= 1; break;  // Left
        case 'u': y -= 1; break;  // Up
        case 'd': y += 1; break;  // Down
    }
    // False if out of bounds
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }
    // True if not a wall, false if wall
    return fullMap[y][x] != WALL;
}

// Moves the character on the map
void Map::moveCharacter(char dir, Player& player) {
    int newX = playerX, newY = playerY;
    switch (tolower(dir)) {
        case 'r': newX += 2; break;  // Right
        case 'l': newX -= 2; break;  // Left
        case 'u': newY -= 2; break;  // Up
        case 'd': newY += 2; break;  // Down
    }

    // If the chosen direction is valid, update full map, then update player map
    if (checkValidDir(dir)) {
        // Trigger interaction
        checkInteractions(dir, player);

        // Set original cell to empty
        char currentCell = fullMap[playerY][playerX];
        fullMap[playerY][playerX] = (currentCell == PLAYER) ? EMPTY : currentCell;

        // Only place player if new position is NOT an enemy, NPC, or the endpoint
        if (fullMap[newY][newX] != ENEMY && fullMap[newY][newX] != MERCHANT && fullMap[newY][newX] != ENDPOINT ) {
            fullMap[newY][newX] = PLAYER;
        }

        // Update position
        updatePlayerMap();
        playerX = newX;
        playerY = newY;
        updatePlayerMap();
    }
}

// Copies cells around character from full map to player's map
void Map::updatePlayerMap() {
    playerMap[playerY][playerX] = PLAYER;
    for (int y = max(0, playerY - 2); y <= min(MAP_HEIGHT - 1, playerY + 2); ++y) {
        for (int x = max(0, playerX - 2); x <= min(MAP_WIDTH - 1, playerX + 2); ++x) {
            playerMap[y][x] = fullMap[y][x];
        }
    }
}

// Checks if playyer is on top of NPC or enemy and triggers appropriate function
void Map::checkInteractions(char dir, Player& player) {
    int newX = playerX, newY = playerY;
    switch (tolower(dir)) {
        case 'r': newX += 2; break;  // Right
        case 'l': newX -= 2; break;  // Left
        case 'u': newY -= 2; break;  // Up
        case 'd': newY += 2; break;  // Down
    }

    // If on enemy, start combat
    if (fullMap[newY][newX] == ENEMY) {
        for (Enemy& enemy : enemies) {
            if (enemy.getX() == newX && enemy.getY() == newY) {
                Combat::combatDialog(player, &enemy);
                updateEnemies(&enemy);
            }
        }
    // If on NPC, start NPC dialog
    } else if (fullMap[newY][newX] == MERCHANT) {
        for (NPC& npc : npcs) {
            if (npc.getX() == newX && npc.getY() == newY) {
                npc.NPCDialog(player);
            }
        }
    }
}

// If enemy has no health left remove it from the map
void Map::updateEnemies(Enemy* enemy) {
    if (enemy->getHealth() <= 0) {
        fullMap[enemy->getY()][enemy->getX()] = EMPTY;
    }
}

// Check if player has met all win conditions and return bool
bool Map::checkWin() {
    int questsCompleted = 0;
    int totalHealth = 0;
    for (Enemy& enemy : enemies) {
        totalHealth += enemy.getHealth();
    }
    for (NPC& npc : npcs) {
        if (npc.getQuestCompleted()) {
            questsCompleted += 1;
        }
    }
    if (totalHealth <= 0 && playerX == 3 && playerY == 1 && questsCompleted == 3) {
        return true;
    }
    return false;
}


