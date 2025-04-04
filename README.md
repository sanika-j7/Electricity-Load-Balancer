# ⚡ Electricity Load Balancer

## 🧠 Project Overview
This C++ project simulates a smart electricity load balancer using key data structures: binary trees (for the grid hierarchy), priority queues (for demand), and linked lists (for consumption history). It mimics a real-world electricity distribution network with automatic load prediction, overload redirection, and fault recovery features.

---

## 🏗️ Architecture

### 🔌 Grid Hierarchy
A binary tree structure represents the grid.

Nodes are classified as:
- **Main Grid**
- **Substation**
- **Transformer**

Each node has:
- Unique ID and name
- Capacity
- Health score
- Load consumption history
- Demand queue (with critical demand prioritization)

---

## 🗂️ Data Structures Used
- 🔼 **Priority Queue** → Handles demand requests, prioritizing critical ones.
- 🔁 **Linked List** → Stores and displays daily load history for each node.
- 🌲 **Binary Tree** → Represents the grid hierarchy.

---

## 🔧 Core Functionalities

### 1. ⚙️ Load Balancing (`balanceLoad`)
- Predicts the next load using average of last 3 days + 10% buffer.
- Sets the current load based on capacity and demand.
- If overload occurs:
  - Redirects excess to child nodes or other transformers.
  - Reduces health score of overloaded node.
  - Logs to CSV (with timestamp) for reporting.

### 2. 🧾 Demand Queueing
- Users can enqueue demands to a specific node (with a critical flag).
- Critical demands are handled first via operator overloading in the `Demand` struct.

### 3. 📊 Load History Tracking
- Daily load updates are stored in a linked list per node.
- Users can view historical loads of any node interactively.

### 4. 🌲 Tree Display (`displayGrid`)
Displays grid structure in an indented tree format:
```bash
├── Main Grid 1
│   ├── Substation 2
│   │   ├── Transformer 4
│   │   └── Transformer 5
│   └── Substation 3
│       ├── Transformer 6
│       └── Transformer 7
```

### 5. ⚖️ Show Max/Min Load Nodes
- Scans the tree for max and min current load across active nodes.
- Useful for visualizing uneven load distribution.

### 6. 💡 Simulate Power Loss / Recovery
- Toggles a node's power status (active/inactive).
- Inactive nodes are ignored during load balancing.
- Demonstrates fault tolerance in the grid.

---

## 📁 Logging & Reporting
`load_report.csv` contains:
- Node name, ID, type
- Capacity, current load
- Health score
- Timestamp of each demand

---

## 🧪 How to Use
1. Enter grid depth (3 → Main → Substation → Transformer)
2. Use the menu to:
   - Display grid
   - Add demand
   - Balance load
   - View load history
   - Show max/min load nodes
   - Simulate power loss or recovery

---

## 🌟 Unique Features
- Uses real-time timestamps for demand logs.
- Tracks node health and adjusts based on performance.
- Visually appealing and realistic grid representation.
- Includes overload redirection and predictive load planning.
