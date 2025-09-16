#include "GridNode.h"
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

void GridNode::addDemand(int demand, bool isCritical) {
    currentLoad += demand;
    consumptionHistory.addLoad(demand, isCritical);
}

// Generate grid recursively
GridNode* generateGrid(int depth, int& id) {
    if (depth == 0) return nullptr;

    GridNode* node = new GridNode(id, "Node_" + to_string(id));
    id++;
    node->left = generateGrid(depth - 1, id);
    node->right = generateGrid(depth - 1, id);
    return node;
}

// Display grid in tree-like format
void displayGridHelper(GridNode* node, string prefix, bool isLeft) {
    if (!node) return;

    cout << prefix << (isLeft ? "├──" : "└──");
    cout << "[ID " << setw(2) << node->id << "] "
         << node->name << " | Load: " << node->currentLoad
         << " | Power: " << (node->isPowered ? "ON" : "OFF") << "\n";

    string newPrefix = prefix + (isLeft ? "│   " : "    ");
    if (node->left)  displayGridHelper(node->left, newPrefix, true);
    if (node->right) displayGridHelper(node->right, newPrefix, false);
}

void displayGrid(GridNode* root) {
    if (!root) {
        cout << "Grid is empty!\n";
        return;
    }
    cout << "\n--- Electricity Grid Layout ---\n";
    displayGridHelper(root, "", false);
    cout << "-------------------------------\n";
}

// Balance loads across powered nodes
void balanceLoad(GridNode* root) {
    if (!root) return;
    int sum = 0, count = 0;
    queue<GridNode*> q; q.push(root);
    while (!q.empty()) {
        GridNode* curr = q.front(); q.pop();
        if (curr->isPowered) { sum += curr->currentLoad; count++; }
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    if (count == 0) return;
    int avg = sum / count;

    q.push(root);
    while (!q.empty()) {
        GridNode* curr = q.front(); q.pop();
        if (curr->isPowered) curr->currentLoad = avg;
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Find max and min load
void showMaxMinLoad(GridNode* root, GridNode*& maxNode, GridNode*& minNode) {
    if (!root) return;
    maxNode = nullptr;
    minNode = nullptr;
    int maxLoad = -1e9, minLoad = 1e9;

    queue<GridNode*> q; q.push(root);
    while (!q.empty()) {
        GridNode* curr = q.front(); q.pop();
        if (curr->isPowered) {
            if (curr->currentLoad > maxLoad) { maxLoad = curr->currentLoad; maxNode = curr; }
            if (curr->currentLoad < minLoad) { minLoad = curr->currentLoad; minNode = curr; }
        }
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Toggle ON/OFF
void toggleNodePower(GridNode* root, int id) {
    if (!root) return;
    queue<GridNode*> q; q.push(root);
    while (!q.empty()) {
        GridNode* curr = q.front(); q.pop();
        if (curr->id == id) {
            curr->isPowered = !curr->isPowered;
            cout << "Node " << curr->name << " is now "
                 << (curr->isPowered ? "ON" : "OFF") << endl;
            return;
        }
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    cout << "Node ID " << id << " not found!\n";
}
