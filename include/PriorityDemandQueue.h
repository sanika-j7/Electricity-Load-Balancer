#pragma once
#include <queue>
#include <vector>
#include <ctime>

struct Demand {
    int units;
    bool isCritical;
    time_t timestamp;

    Demand(int u, bool crit) : units(u), isCritical(crit), timestamp(time(0)) {}

    bool operator<(const Demand& d) const {
        if (isCritical != d.isCritical) return !isCritical;
        return units < d.units;
    }
};

class PriorityDemandQueue {
    std::priority_queue<Demand> pq;

public:
    void enqueue(int demand, bool isCritical);
    int dequeue();
    bool isEmpty();
    int totalDemand();
    std::vector<Demand> getAllDemands();
};
