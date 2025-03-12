/*
 * Author(s): Connor Krell, Daniel Lebedev
 * Description: Description: Defines NPC functions.
 */
#include "NPC.h"

// Handles NPC interaction with player
void NPC::NPCDialog(Player& player) {
    string selection;
    cout << dialog << endl;
    while (true) {
        cout << "\nWhat would you like to do?" << endl;
        cout << "1 - View Quest" << endl;
        cout << "2 - Exit Dialog" << endl;

        cin >> selection;
        if (selection == "1") {
            completeQuest(player);
        } else if (selection == "2") {
            break;
        } else {
            cout << "Invalid selection! Try again!" << endl;
        }
    }
}

// Displays quest or tells user they've completed it already
void NPC::showQuest(Player& player) {
    if (questCompleted) {
        cout << "\nYou have already completed this quest." << endl;
    } else {
        cout << "\n" << questDescription << endl;
        cout << "Kill " << requiredKills - player.getKills() << " more enemies to receive: ";

        if (this == &QUEST_GIVER3) {
            cout << "a special weapon!" << endl;
        } else {
            cout << rewardItem->getName() << endl;
        }
    }
}

// Checks if player met quest requirements and rewards player
void NPC::completeQuest(Player& player) {
    if (!questCompleted && player.getKills() >= requiredKills) {
        if (this->getName() == QUEST_GIVER3.getName()) { // Special handling for final quest giver
            Weapon* classWeapon = nullptr;

            // Assign weapon based on player class
            if (player.getPlayerClass().className == "Warrior") {
                classWeapon = &WARHAMMER;
            } else if (player.getPlayerClass().className == "Mage") {
                classWeapon = &SPELL_TOME;
            } else if (player.getPlayerClass().className == "Rogue") {
                classWeapon = &SWORD;
            }

            cout << "Congratulations! You have completed the quest and received: "  << classWeapon->getName() << "!" << endl;
            player.addItem(classWeapon);

        } else {
            // Standard reward for other NPCs
            cout << "Congratulations! You have completed the quest and received: " << rewardItem->getName() << "!" << endl;
            player.addItem(rewardItem);
        }
        questCompleted = true;
    } else {
        showQuest(player);
    }
}

// Instantiate NPCs to be used in game.
NPC QUEST_GIVER1("Rob Quest", "Woah, Hey there! I've been stuck down here for ages! My brothers and I came down here to clear the dungeon\n"
                              "but they both got lost! If you find my brothers and clear the dungeon we can all escape! We have some items\n"
                              "to help you clear the dungeon, but you'll have to help us out a bit first!", "Defeat 3 Enemies", 3, &GREATER_HEALTH, 1, 3);

NPC QUEST_GIVER2("Bob Quest", "Oh hello! I'm glad you found me, help me clear out some enemies and I'll give you a reward!", "Defeat 7 Enemies", 7, &GREATER_HEALTH, 9, 3);

NPC QUEST_GIVER3("John Quest", "Thank god you found me! If you prove to me you can deafeat the last of the enemies, I'll give you a weapon to help you defeat the dragon and we can get out of here!", "Defeat 10 Enemies", 10, &EPIC_HEALTH, 19, 5);

