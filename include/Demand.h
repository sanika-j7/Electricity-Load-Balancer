#pragma once

class Demand {
public:
    int units;
    bool isCritical;

    Demand(int u, bool c) : units(u), isCritical(c) {}

    // Custom comparison: critical demands have higher priority,
    // and if both have same critical status, higher units come first
    bool operator<(const Demand& other) const {
        if (isCritical != other.isCritical)
            return !isCritical; // critical = true has higher priority
        return units < other.units;   // larger units = higher priority
    }
};
