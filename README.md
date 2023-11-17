# CS 421 Project 2
## David Qiu and Carter Williams
Given a file with an adjacency matrix, output a color sequence for vertices where no two adjacent vertices can share the same color. Our project involves three solutions that build off each other:
1. A naive backtracking approach.
2. A backtracking approach that makes greedy choices at each step.
3. A backtracking approach that makes greedy choices at each step, but is exhaustive. It will check all possible solutions until the min possible cost is achieved.
### Problem Definiton
Given a graph G with vertices V and edges E, color each vertex so that adjacent vertices do not share the same color. Given a set of solutions S, output the solution that minimizes the following equation:
``` math
\sum_{i=1}^{k - 1} |c_{i}-c_{i + 1}|
```
Where k is the number of colors and c is the number of vertices with that color. The value ouputted from this equation for any given solution will be the "cost" of the solution.
### Compiling
- If make is installed, use that.
- Check the "Makefile" for a simple way to compile.
- Ensure the "./include" directory is included when compiling.
- In "main.cpp," there is a macro, "ALL," that outputs the solution for each graph with each implementation. To only output the main implementation, remove this definition.
### Running the Program
- Check the various "graph.txt" files in the working directory to see how an input file should be formatted. The file should be made up of:
    1. The number of colors, k, on the first line.
    2. The number of vertices, |V|, on the second line.
    3. An adjacency matrix where a "1" means there is an edge, and a "0" means there is no edge between $V_{i}$ and $V_{j}$.
        - Directed graphs are supported.
        - Ensure both [i][j] and [j][i] have a "1" if the graph is undirected.
- Specify input file(s) by passing the file names as arguments. Example: "./a.out graph1.txt graph2.txt ... graphn.txt"
    - It will ouput solutions for each graph.
## Implementation
This section will be a general overview of the implementations. To see just the main implementation, skip to the last section. General Notes:
- All of the solutions inherit functionality from the naive approach.
- Many classes contain misc. methods that are not mentioned because they do not directly solve the problem. An example of this would be the print_solution() method.
### Graph
A class declared in "graph.h" and defined in "graph.cpp." Represents a graph as a list, adj, of lists. If any vertex, v, shares an edge with another vertex, q, then adj[v] contains q. If undirected, adj[q] contains v. The edges are not ordered in any way because we only iterate over the vertices. Order does not matter in that case. Note: We also use std::vector as adj and the lists inside adj.
### Naive Backtracking
This solution is made implemented in the "GraphColor" class. It is declared in "graph_color.h" and defined in "graph_color.cpp." In this section, we will go over the data members, data structures, and algorithms used.
#### Data Members
- *int k*: Number of colors to color the graph with.
- *Graph graph*: Class representing the graph. Implemented as an adjacency list.
- *Solution solution*: Class representing a solution. We only keep the best solution found.
- *int best_solution*: The minimum possible cost with the number of colors and vertices. For example, 15 verticies with 3 colors would have a value of 0 (15 % 3 = 0). With four colors it would be 1. This allows the algorithm to stop early when it cannot get a lower cost. This value is in {0, 1}
#### Data Structures
- *int v_colors[]*: A direct hash table that holds the color of each vertex. If |V| = n, then |v_colors| = n. Allows for quick access to the color of each vertex. Note: this is implemented using std::vector. A direct hash table is used because each vertex needs exactly one spot and the number of vertices will not change.
#### Algorithms
- *is_safe(int vertex, int color)*: Checks if the vertex shares the color with any of its adjacent vertices.
- *color_vertices(int vertex, int num_vertices)*: Recursive function that colors a vertex then calls itself with the next vertex. Once a solution is found, it updates the solution (if it's cost is lower than the current solution) and backtracks. This function is exhaustive, so it will check every color possibility for every vertex. If the new solution's cost is equal to the best_solution, it stops searching for solutions.
### Greedy Selection
