/*
 * Author(s): Daniel Lebedev
 * Description: Puts everything together.
 */

#include "Player.h"
#include "Map.h"
#include "Game.cpp"
#include <QCoreApplication>

// Current working product, user can create player, start game, and test some functionality
int main()
{
    // Create Game object
    Game game;

    // Create player object with user's input
    Player player = game.startGame();

    // Create map object
    Map map;

    // Starts game loop
    game.gameLoop(player, map);

}

