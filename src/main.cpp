#include <iostream>
#include <queue>
#include "GridNode.h"
#include "PriorityDemandQueue.h"
#include "LinkedList.h"
#include "Utils.h"
using namespace std;

int main() {
    int id = 1, depth;
    cout << "Enter grid levels (3 = Main→Substation→Transformer): ";
    cin >> depth;

    GridNode* root = generateGrid(depth, id);
    int choice;
    do {
        cout << "\n===== Electricity Load Balancer Menu =====\n"
             << "1. Display Grid\n2. Add Demand\n3. Balance Load\n"
             << "4. View Node History\n5. Show Max/Min Load\n"
             << "6. Toggle Power\n7. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) displayGrid(root);
        else if (choice == 2) {
            int targetId, demand; bool isCritical;
            cout << "Node ID: "; cin >> targetId;
            cout << "Demand units: "; cin >> demand;
            cout << "Critical? (1=Yes,0=No): "; cin >> isCritical;

            queue<GridNode*> q; q.push(root);
            while (!q.empty()) {
                GridNode* curr = q.front(); q.pop();
                if (curr->id == targetId) { curr->addDemand(demand, isCritical); break; }
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        else if (choice == 3) balanceLoad(root);
        else if (choice == 4) {
            int targetId; cout << "Node ID: "; cin >> targetId;
            queue<GridNode*> q; q.push(root);
            while (!q.empty()) {
                GridNode* curr = q.front(); q.pop();
                if (curr->id == targetId) { curr->consumptionHistory.displayHistory(); break; }
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        else if (choice == 5) {
            GridNode* maxNode = nullptr; GridNode* minNode = nullptr;
            showMaxMinLoad(root, maxNode, minNode);
            if (maxNode && minNode) {
                cout << "Max Load: " << maxNode->name << " (" << maxNode->currentLoad << " units)\n";
                cout << "Min Load: " << minNode->name << " (" << minNode->currentLoad << " units)\n";
            }
        }
        else if (choice == 6) {
            int targetId; cout << "Node ID: "; cin >> targetId;
            toggleNodePower(root, targetId);
        }
    } while (choice != 7);

    return 0;
}
