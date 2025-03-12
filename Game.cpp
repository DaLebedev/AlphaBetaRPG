/*
 * Author(s): Daniel Lebedev
 * Description: Handles game logic.
 */

#include <iostream>
#include <string>
#include "Player.h"
#include "NPC.h"
#include "Map.h"

using namespace std;

class Game {
public:

    // Runs on start, loops until player wins, handles basic decision logic for game
    void gameLoop(Player& player, Map& map) {
        string selection;

        while (!map.checkWin()) {
            cout << "\nWhat would you like to do next:" << endl;
            cout << "1 - Open Map" << endl;
            cout << "2 - Open Inventory" << endl;
            cout << "3 - Move rooms" << endl;

            cin >> selection;
            // Display map
            if (selection == "1") {
                map.renderMap();
            // Display inventory
            } else if (selection == "2") {
                player.displayInventory();
            // Move player
            } else if (selection == "3") {
                playerMvmt(map, player);
            // Handle invalid input
            } else {
                cout << "\nInvalid selection! Try again!" << endl;
            }
        }
        // Win messsage
        cout << "\nCongratulations " << player.getName() << "! You've cleared the dungeon and helped the Quest brothers escape!" << endl;
    }


    // Runs when game starts, creates player with entered info
    Player startGame() {
        string name, classSelection;
        PlayerClass playerClass;

        cout << "Welcome! Please enter your desired name: " << endl;
        cin >> name;

        // Loop until valid input
        while (true) {
            cout << "\nPlease select your desired class: " << endl;
            cout << "1 - Warrior" << endl;
            cout << "2 - Mage" << endl;
            cout << "3 - Rogue" << endl;
            cin >> classSelection;

            // Set class to warrior and give player club
            if (classSelection == "1") {
                playerClass = WARRIOR;
                break;
            // Set class to mage and give player staff
            } else if (classSelection == "2") {
                playerClass = MAGE;
                break;
            // Set class to rogue and give player dagger
            } else if (classSelection == "3") {
                playerClass = ROGUE;
                break;
            // Handle invalid input
            } else {
                cout << "\nInvalid selection! Try again!" << endl;
            }
        }
        Player player(name, playerClass);
        player.addItem(player.getEquippedWeapon());
        return player;
    }

    // Runs when player chooses to move, handles player input for moving character
    void playerMvmt(Map& map, Player& player) {
        string selection;
        bool canMoveRight = map.checkValidDir('r');
        bool canMoveLeft = map.checkValidDir('l');
        bool canMoveUp = map.checkValidDir('u');
        bool canMoveDown = map.checkValidDir('d');

        while (true) {

            cout << "\nWhich Direction?" << endl;
            if (canMoveRight) {
                cout << "1 - Move Right" << endl;
            }
            if (canMoveLeft) {
                cout << "2 - Move Left" << endl;
            }
            if (canMoveUp) {
                cout << "3 - Move Up" << endl;
            }
            if (canMoveDown) {
                cout << "4 - Move Down" << endl;
            }

            cin >> selection;
            if (selection == "1" && canMoveRight) {
                cout << "\nMoving Right..." << endl;
                map.moveCharacter('r', player);
                break;
            } else if (selection == "2" && canMoveLeft) {
                cout << "\nMoving Left..." << endl;
                map.moveCharacter('l', player);
                break;
            } else if (selection == "3" && canMoveUp) {
                cout << "\nMoving Up..." << endl;
                map.moveCharacter('u', player);
                break;
            } else if (selection == "4" && canMoveDown) {
                cout << "\nMoving Down..." << endl;
                map.moveCharacter('d', player);
                break;
            } else {
                cout << "\nInvalid selection! Try again!" << endl;
            }
        }
    }
};
