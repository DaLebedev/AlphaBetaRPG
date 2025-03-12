/*
 * Author(s): Daniel Lebedev, Ryan Haskins
 * Description: Defines combat functions.
 */

#include <algorithm>
#include "Combat.h"

// Runs when combat starts, handles player portion of combat logic
void Combat::combatDialog(Player& player, Enemy* enemy) {
    string selection;
    // Displays name of enemy and starts loop
    cout << "\nYou Encountered: " << enemy->getName() << " HP: " << enemy->getHealth() << endl;
    while (player.getCurrHealth() > 0 && enemy->getHealth() > 0) {
        cout << "\nWhat would you like to do?" << endl;
        cout << "1 - Attack" << endl;
        cout << "2 - Open Inventory" << endl;
        cin >> selection;

        // Attack enemy using equipped weapon, update enemy health, then display enemy health
        if (selection == "1") {
            int damage = player.getEquippedWeapon()->getDamage();
            enemy->setHealth((max(0, enemy->getHealth() - damage)));
            player.getEquippedWeapon()->use();
            cout << "Enemy Health: " << enemy->getHealth() << endl;
        }

        // Open inventory
        else if (selection == "2") {
            player.displayInventory(true);
            continue;
        }

        // Handle invalid input
        else {
            cout << "\nInvalid selection! Try again!" << endl;
            continue;
        }

        // End fight if player dies
        if (player.getCurrHealth() <= 0) {
            cout << "\nYou lost the fight!" << endl;
            break;
        }

        // If enemy dies, reward player, reset health, & end fight
        if (enemy->getHealth() <= 0) {
            cout << "\nYou won the fight!" << endl;
            cout << "Reward: " << enemy->getLoot()->getName() << endl;
            player.setKills(player.getKills()+1);
            player.addItem(enemy->getLoot());
            player.setCurrHealth(max(0, player.getPlayerClass().maxHp));
            break;
        }

        // Enemy attacks
        enemyAttack(player, enemy);
    }
}

// Runs after player attacks, handles enemy combat logic
void Combat::enemyAttack(Player& player, Enemy* enemy) {
    // Enemy attack with 75% chance to hit
    if (rand() % 4 < 3) {
        enemy->attack();
        player.setCurrHealth(player.getCurrHealth() - enemy->getDamage());
    } else {
        cout << "\n" << enemy->getName() << " tries to attack but misses! " << endl;
    }
    cout << "Your Health: " << player.getCurrHealth() << endl;
}
