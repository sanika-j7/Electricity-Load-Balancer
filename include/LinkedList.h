#pragma once
#include <iostream>

struct HistoryNode {
    int load;
    int criticalFactor;   // added field
    HistoryNode* next;

    HistoryNode(int l, int cf) : load(l), criticalFactor(cf), next(nullptr) {}
};

class LinkedList {
    HistoryNode* head;

public:
    LinkedList();
    void addLoad(int load, int criticalFactor);   // updated
    double averageLoad(int days);
    double averageCriticalFactor(int days);       // new
    void displayHistory();
};
