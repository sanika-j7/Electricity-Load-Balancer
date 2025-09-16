#pragma once
#include <ctime>

class Demand {
public:
    int units;
    bool isCritical;
    std::time_t timestamp; 

    Demand(int u, bool c) : units(u), isCritical(c) {
        timestamp = std::time(nullptr); // current time
    }

    bool operator<(const Demand& other) const {
        if (isCritical != other.isCritical)
            return !isCritical; // critical has higher priority
        return units < other.units;   // larger units = higher priority
    }
};
