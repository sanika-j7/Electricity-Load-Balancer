#include "PriorityDemandQueue.h"

void PriorityDemandQueue::enqueue(int demand, bool isCritical) {
    pq.push(Demand(demand, isCritical));
}

int PriorityDemandQueue::dequeue() {
    if (!pq.empty()) {
        Demand d = pq.top();
        pq.pop();
        return d.units;
    }
    return 0;
}

bool PriorityDemandQueue::isEmpty() {
    return pq.empty();
}

int PriorityDemandQueue::totalDemand() {
    int sum = 0;
    std::priority_queue<Demand> temp = pq;
    while (!temp.empty()) {
        sum += temp.top().units;
        temp.pop();
    }
    return sum;
}

std::vector<Demand> PriorityDemandQueue::getAllDemands() {
    std::vector<Demand> all;
    std::priority_queue<Demand> temp = pq;
    while (!temp.empty()) {
        all.push_back(temp.top());
        temp.pop();
    }
    return all;
}
