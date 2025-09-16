#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

void LinkedList::addLoad(int load, int criticalFactor) {
    HistoryNode* newNode = new HistoryNode(load, criticalFactor);
    newNode->next = head;
    head = newNode;
}

double LinkedList::averageLoad(int days) {
    HistoryNode* curr = head;
    int sum = 0, count = 0;
    while (curr && count < days) {
        sum += curr->load;
        curr = curr->next;
        count++;
    }
    return count ? (double)sum / count : 0;
}

double LinkedList::averageCriticalFactor(int days) {
    HistoryNode* curr = head;
    int sum = 0, count = 0;
    while (curr && count < days) {
        sum += curr->criticalFactor;
        curr = curr->next;
        count++;
    }
    return count ? (double)sum / count : 0;
}

void LinkedList::displayHistory() {
    HistoryNode* curr = head;
    int day = 1;
    while (curr) {
        cout << "Day " << day++
             << ": Load = " << curr->load
             << " units, Critical Factor = " << curr->criticalFactor
             << "\n";
        curr = curr->next;
    }
}
