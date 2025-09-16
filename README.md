# Electricity Load Balancer

## Overview
This project simulates an **Electricity Load Balancer System** for power grids. It manages demands, predicts loads, balances across substations and transformers, and logs consumption history. The project demonstrates:
- Priority queues for demand management.
- Linked list for consumption history.
- Binary tree for grid structure (Main Grid → Substations → Transformers).
- Load prediction and balancing.
- CSV logging.

## Project Structure
```
ElectricityLoadBalancer/
├── CMakeLists.txt
├── include/
│   ├── Demand.h
│   ├── PriorityDemandQueue.h
│   ├── LinkedList.h
│   ├── GridNode.h
│   ├── Utils.h
├── src/
│   ├── Demand.cpp
│   ├── PriorityDemandQueue.cpp
│   ├── LinkedList.cpp
│   ├── GridNode.cpp
│   ├── Utils.cpp
│   ├── main.cpp
├── data/
│   └── load_report.csv
├── tests/
│   ├── CMakeLists.txt
│   └── test_load_balancer.cpp
└── README.md
```
## Demo
[PPT](https://www.canva.com/design/DAGjpDMUFz4/v9fCWvOmJe5MvG0S-UXw7w/edit)

## Build Instructions
```bash
mkdir build
cd build
cmake ..
cmake --build .
./bin/ElectricityLoadBalancer
```

## Features
1. **Display Grid** – Shows hierarchical grid structure.
2. **Add Demand** – Adds demand to a node (critical or non-critical).
3. **Balance Load** – Distributes load across nodes and prevents overload.
4. **View Node Load History** – Displays past load records.
5. **Show Max/Min Load Node** – Identifies heavily and lightly loaded nodes.
6. **Simulate Power Loss/Recovery** – Toggles node activity.

## Future Improvements
- Unit testing with GoogleTest.
- Smarter load prediction with machine learning.
- GUI visualization of grid structure.
- Real-time monitoring dashboard.
