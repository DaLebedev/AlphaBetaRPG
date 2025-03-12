/*
 * Author(s): Connor Krell, Daniel Lebedev
 * Description: NPC class represents characters the player can interact with to complete quests.
 */

#ifndef NPC_H
#define NPC_H
#include <string>
#include "Item.h"
#include "Player.h"
using namespace std;

class NPC {
private:
    // NPC member variables
    string name;
    string dialog;
    string questDescription;
    int requiredKills;
    Item* rewardItem;
    bool questCompleted = false;
    int x, y;


public:
    // Function declarations
    NPC(string name, string dialog, string questDescription, int requiredKills, Item* rewardItem, int x, int y):
        name(name), dialog(dialog), questDescription(questDescription), requiredKills(requiredKills), rewardItem(rewardItem), x(x), y(y) {}
    void showQuest(Player& player);
    void completeQuest(Player& player);
    void NPCDialog(Player& player);

    // Getters & Setters
    string getName() { return name; }
    void setName(string name) { this->name = name; }

    string getDialog() { return dialog; }
    void setDialog(string dialog) { this->dialog = dialog; }

    string getDescription() { return questDescription; }
    void setDescription(string questDescription) { this->questDescription = questDescription; }

    int getRequiredKills() { return requiredKills; }
    void setRequiredKills(int requiredKills) { this->requiredKills = requiredKills; }

    bool getQuestCompleted() { return questCompleted; }
    void setQuestCompleted(bool questCompleted) { this->questCompleted = questCompleted; }

    int getX() { return x; }
    int getY() { return y; }
};

// Define NPCs
extern NPC QUEST_GIVER1;
extern NPC QUEST_GIVER2;
extern NPC QUEST_GIVER3;

#endif // NPC_H
