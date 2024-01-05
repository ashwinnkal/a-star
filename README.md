# A* Algorithm


## Description:
This repository contains a C++ implementation of the A* Pathfinding Algorithm. The A* algorithm - informed search algorithm 
is widely used in pathfinding and graph traversal, for finding a cost-effective route between start and goal position. 
Unlike other search algorithms, the A* Pathfinding Algorithm uses a heuristic function This function estimates the 
cost to complete the path to the goal, adding this to the current path cost, and thus facilitates decisions to 
pursue the path with the lowest cumulative cost. 

My implementation showcases A* algorithm using c++ for applications 
such as game development, robotics path planning, and GIS mapping.

It's important to note that while the A* algorithm is efficient, it has a drawback in terms of space complexity, 
which is O(b^d), as it retains all generated nodes in memory. Additionally, unlike Dijkstra's algorithm, which 
computes the shortest-path tree from a source to all possible destinations, the A* algorithm specifically finds 
the shortest path between a designated source and a specific goal.


## To Clone my Project,
```bash
git clone https://github.com/ashwinnkal/a-star.git
```


## License
This project is licensed under the MIT License. See the LICENSE file for more details.
