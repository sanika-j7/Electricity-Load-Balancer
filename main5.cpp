#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

// ----------------------- Priority Demand Queue -----------------------
struct Demand {
    int units;
    bool isCritical;
    time_t timestamp;

    Demand(int u, bool crit) : units(u), isCritical(crit), timestamp(time(0)) {}

    bool operator<(const Demand& d) const {
        return units < d.units || (!isCritical && d.isCritical);
    }
};

class PriorityDemandQueue {
    priority_queue<Demand> pq;

public:
    void enqueue(int demand, bool isCritical) {
        pq.push(Demand(demand, isCritical));
    }

    int dequeue() {
        if (!pq.empty()) {
            Demand d = pq.top();
            pq.pop();
            return d.units;
        }
        return 0;
    }

    bool isEmpty() {
        return pq.empty();
    }

    int totalDemand() {
        int sum = 0;
        priority_queue<Demand> temp = pq;
        while (!temp.empty()) {
            sum += temp.top().units;
            temp.pop();
        }
        return sum;
    }

    vector<Demand> getAllDemands() {
        vector<Demand> all;
        priority_queue<Demand> temp = pq;
        while (!temp.empty()) {
            all.push_back(temp.top());
            temp.pop();
        }
        return all;
    }
};

// ----------------------- Linked List for Consumption History -----------------------
struct HistoryNode {
    int load;
    HistoryNode* next;
    HistoryNode(int l) : load(l), next(NULL) {}
};

class LinkedList {
    HistoryNode* head;

public:
    LinkedList() : head(NULL) {}

    void addLoad(int load) {
        HistoryNode* newNode = new HistoryNode(load);
        newNode->next = head;
        head = newNode;
    }

    double averageLoad(int days) {
        HistoryNode* curr = head;
        int sum = 0, count = 0;
        while (curr && count < days) {
            sum += curr->load;
            curr = curr->next;
            count++;
        }
        return count ? (double)sum / count : 0;
    }

    void displayHistory() {
        HistoryNode* curr = head;
        int day = 1;
        while (curr) {
            cout << "Day " << day++ << ": " << curr->load << " units\n";
            curr = curr->next;
        }
    }
};

// ----------------------- Grid Node -----------------------
struct GridNode {
    string name;
    string type; // Main Grid, Substation, Transformer
    int id;
    PriorityDemandQueue demandQueue;
    LinkedList consumptionHistory;
    int capacity;
    int healthScore;
    int currentLoad;
    bool isActive;
    GridNode* left;
    GridNode* right;

    GridNode(string n, string t, int i, int cap) : name(n), type(t), id(i), capacity(cap), healthScore(100), currentLoad(0), isActive(true), left(NULL), right(NULL) {}
};

vector<GridNode*> allTransformers;

// ----------------------- Predict Load -----------------------
int predictNextLoad(GridNode* node) {
    return round(node->consumptionHistory.averageLoad(3) * 1.1); // +10% buffer
}

// ----------------------- Tree Display -----------------------
void displayGrid(GridNode* node, string prefix = "", bool isLeft = true) {
    if (!node) return;

    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << node->name << " (" << node->type << ", " << node->currentLoad << "/" << node->capacity << " units, Health: " << node->healthScore << "%)\n";

    displayGrid(node->left, prefix + (isLeft ? "│   " : "    "), true);
    displayGrid(node->right, prefix + (isLeft ? "│   " : "    "), false);
}

// ----------------------- Auto Generate Binary Tree -----------------------
GridNode* generateGrid(int depth, int& id, string type = "Main Grid") {
    if (depth == 0) return nullptr;

    string nodeType;
    if (depth == 3) nodeType = "Main Grid";
    else if (depth == 2) nodeType = "Substation";
    else nodeType = "Transformer";

    GridNode* node = new GridNode(nodeType + " " + to_string(id), nodeType, id, nodeType == "Main Grid" ? 300 : nodeType == "Substation" ? 200 : 100);
    if (nodeType == "Transformer") allTransformers.push_back(node);

    id++;
    node->left = generateGrid(depth - 1, id);
    node->right = generateGrid(depth - 1, id);
    return node;
}

// ----------------------- Load Balancer Logic -----------------------
void balanceLoad(GridNode* node) {
    if (!node || !node->isActive) return;

    int totalDemand = node->demandQueue.totalDemand();
    double avgLoad = node->consumptionHistory.averageLoad(3);
    node->currentLoad = min(totalDemand, node->capacity);

    // Log to CSV
    ofstream file("load_report.csv", ios::app);
    vector<Demand> demands = node->demandQueue.getAllDemands();
    for (const auto& d : demands) {
        file << node->name << "," << node->type << "," << node->id << "," << node->capacity << "," << node->currentLoad << "," << avgLoad << "," << node->healthScore << "," << ctime(&d.timestamp);
    }
    file.close();

    cout << "\n[Node: " << node->name << "]\n";
    cout << "Capacity: " << node->capacity << " | Current Load: " << node->currentLoad
         << " | Total Demand: " << totalDemand << " | Avg Load (3 days): " << avgLoad << " | Health: " << node->healthScore << "%\n";

    if (totalDemand > node->capacity) {
        cout << "⚠️  Overload at " << node->name << ". Shifting excess load...\n";
        node->healthScore -= 5;
        int excess = totalDemand - node->capacity;

        // First try children
        if (node->left && node->left->isActive) node->left->demandQueue.enqueue(excess / 2, true);
        if (node->right && node->right->isActive) node->right->demandQueue.enqueue(excess - excess / 2, true);

        // Then try global transformers
        else {
            for (auto t : allTransformers) {
                if (t != node && t->isActive && t->currentLoad + excess <= t->capacity) {
                    cout << "↪️ Redirecting excess to " << t->name << endl;
                    t->demandQueue.enqueue(excess, true);
                    break;
                }
            }
        }
    }

    node->consumptionHistory.addLoad(node->currentLoad);

    balanceLoad(node->left);
    balanceLoad(node->right);
}
// ----------------------- Show Max and Min Load -----------------------
void showMaxMinLoad(GridNode* node, GridNode*& maxNode, GridNode*& minNode) {
    if (!node) return;

    if (node->isActive) {
        if (!maxNode || node->currentLoad > maxNode->currentLoad)
            maxNode = node;
        if (!minNode || node->currentLoad < minNode->currentLoad)
            minNode = node;
    }

    showMaxMinLoad(node->left, maxNode, minNode);
    showMaxMinLoad(node->right, maxNode, minNode);
}

// ----------------------- Simulate Power Loss -----------------------
void toggleNodePower(GridNode* node, int targetId) {
    if (!node) return;

    if (node->id == targetId) {
        node->isActive = !node->isActive;
        cout << "Node " << node->name << " is now " << (node->isActive ? "ACTIVE" : "INACTIVE (Power Loss)") << ".\n";
        return;
    }

    toggleNodePower(node->left, targetId);
    toggleNodePower(node->right, targetId);
}

// ----------------------- Main -----------------------
int main() {
    int id = 1;
    int depth;
    cout << "Enter number of levels in grid (3 = Main → Substation → Transformer): ";
    cin >> depth;
    GridNode* root = generateGrid(depth, id);

    int choice;
    do {
        cout << "\n===== Electricity Load Balancer Menu =====\n";
cout << "1. Display Grid\n";
cout << "2. Add Demand to Node\n";
cout << "3. Balance Load\n";
cout << "4. View Node Load History\n";
cout << "5. Show Max/Min Load Node\n";
cout << "6. Simulate Power Loss/Recovery\n";
cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayGrid(root);
        } else if (choice == 2) {
            int targetId, demand;
            bool isCritical;
            cout << "Enter Node ID: ";
            cin >> targetId;
            cout << "Enter demand (in units): ";
            cin >> demand;
            cout << "Is this critical demand? (1 = Yes, 0 = No): ";
            cin >> isCritical;

            queue<GridNode*> q;
            q.push(root);
            while (!q.empty()) {
                GridNode* curr = q.front(); q.pop();
                if (curr->id == targetId) {
                    curr->demandQueue.enqueue(demand, isCritical);
                    break;
                }
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        } else if (choice == 3) {
            balanceLoad(root);
        } else if (choice == 4) {
            int targetId;
            cout << "Enter Node ID: ";
            cin >> targetId;
            queue<GridNode*> q;
            q.push(root);
            while (!q.empty()) {
                GridNode* curr = q.front(); q.pop();
                if (curr->id == targetId) {
                    curr->consumptionHistory.displayHistory();
                    break;
                }
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        else if (choice == 5) {
            GridNode* maxNode = nullptr;
            GridNode* minNode = nullptr;
            showMaxMinLoad(root, maxNode, minNode);
            if (maxNode && minNode) {
                cout << "🔺 Max Load: " << maxNode->name << " with " << maxNode->currentLoad << " units\n";
                cout << "🔻 Min Load: " << minNode->name << " with " << minNode->currentLoad << " units\n";
            } else {
                cout << "No active nodes found.\n";
            }
        } else if (choice == 6) {
            int targetId;
            cout << "Enter Node ID to toggle power status: ";
            cin >> targetId;
            toggleNodePower(root, targetId);
        }
        
    } while (choice != 7);

    return 0;
}
