#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <string>
#include "LinkedList.h"

struct GridNode {
    int id;
    std::string name;
    int currentLoad;
    bool isPowered;   // ON/OFF state
    GridNode* left;
    GridNode* right;
    LinkedList consumptionHistory;

    GridNode(int id, const std::string& name)
        : id(id), name(name), currentLoad(0), isPowered(true),
          left(nullptr), right(nullptr) {}

    void addDemand(int demand, bool isCritical);
};

// Function declarations
GridNode* generateGrid(int depth, int& id);
void displayGrid(GridNode* root);
void balanceLoad(GridNode* root);
void showMaxMinLoad(GridNode* root, GridNode*& maxNode, GridNode*& minNode);
void toggleNodePower(GridNode* root, int id);

#endif // GRIDNODE_H
