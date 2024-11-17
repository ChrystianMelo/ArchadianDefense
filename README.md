# Practical Assignment - Military Logistics in Archadia

## Introduction

Gramis Gana Solidor, the emperor of Archadia, faces the threat of invasion from neighboring countries. To safeguard the empire, a strategic restructuring of states was proposed, focusing on military logistics. This project addresses the update of geopolitical maps, the selection of a strategic capital, the definition of locations for battalions, and the planning of patrol routes.

This repository provides computational solutions to these problems using classic graph theory algorithms to meet the empire's needs.

---

## Modeling

The problem was modeled as a directed graph where:

- **Nodes** represent cities.
- **Edges** represent one-way roads between the cities.

The `Archadian` class encapsulates the graph and provides methods to:

- Identify the capital.
- Establish patrols.
- Define strategic locations for battalions.

### Algorithms Used

1. **Depth-First Search (DFS)**: To explore graph connections.
2. **Kosaraju**: To identify Strongly Connected Components (SCCs).
3. **Dijkstra**: To calculate the shortest paths in weighted graphs.

---

## Solution

- **Selecting the Capital**: Dijkstra's algorithm was chosen for its efficiency in determining the shortest path from one city to all others.
- **Defining Strategic Locations**: Kosaraju's algorithm was used to identify SCCs, ensuring mutual accessibility within the same component.
- **Planning Patrols**: A combination of DFS and Dijkstra facilitates the planning of optimized routes.

---

## Complexity Analysis

### DFS and Kosaraju
- **Time Complexity**: `O(V + E)`
- **Space Complexity**: `O(V + E)`

### Dijkstra
- **Time Complexity**: `O((V + E)⋅log V)`
- **Space Complexity**: `O(V + E)`

### Overall Project Complexity
- `O((1 + p)⋅(V + E)⋅log V)`  
Where `p` is the number of patrols performed.

---

## Memory Usage

Memory usage was optimized by employing:
- **Hash Maps**: For efficient lookups (`O(1)`).
- **Priority Queues (Min-Heap)**: For operations with cost `O(log V)`.

Total memory usage: `O(V + E)`.

---

## Final Considerations

This project offered a valuable opportunity to apply classical graph algorithms to practical problems in logistics and security. The integration of Dijkstra and Kosaraju algorithms was essential to meet the objectives. The efficiency in both time and memory ensures that the solution is scalable for large graphs.

---

## References

1. Jon Kleinberg, Éva Tardos. *Algorithm Design*. Addison-Wesley, 2005.
2. C++ STL and standard libraries documentation.
3. Lecture notes.
