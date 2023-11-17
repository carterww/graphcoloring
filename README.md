# CS 421 Project 2
## David Qiu and Carter Williams
This project iterated on many solutions. Our final solution is described in Heuristical Complete Solution. The others were kept for inheritance and test purposes.
## Overview
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
    3. An adjacency matrix where a "1" means there is an edge, and a "0" means there is no edge between $`V_{i}`$ and $`V_{j}`$.
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
### Naive Backtracking Solution
This solution is made implemented in the "GraphColor" class. It is declared in "graph_color.h" and defined in "graph_color.cpp." This solution was our first iteration over the solution. The next two solutions simply improve on this. In this section, we will go over the data members, data structures, and algorithms used.
#### Data Members
- *int k*: Number of colors to color the graph with.
- *Graph graph*: Class representing the graph. Implemented as an adjacency list.
- *Solution solution*: Class representing a solution. We only keep the best solution found.
- *int best_solution*: The minimum possible cost with the number of colors and vertices. For example, 15 verticies with 3 colors would have a value of 0 (15 % 3 = 0). With four colors it would be 1. This allows the algorithm to stop early when it cannot get a lower cost. This value is in {0, 1}
#### Data Structures
- *int v_colors[]*: A direct hash table that holds the color of each vertex. If |V| = n, then |v_colors| = n. Allows for quick access to the color of each vertex. Note: this is implemented using std::vector. A direct hash table is used because each vertex needs exactly one spot and the number of vertices will not change.
#### Algorithms
- *is_safe()*: Checks if the vertex shares the color with any of its adjacent vertices.
- *color_vertices()*: Recursive function that colors a vertex then calls itself with the next vertex. Once a solution is found, it updates the solution (if it's cost is lower than the current solution) and backtracks. This function is exhaustive, so it will check every color possibility for every vertex. If the new solution's cost is equal to the best_solution, it stops searching for solutions.
### Greedy Selection Solution
This solution is implemented in the "GraphColorGreedy" class. It is declared in "graph_color_greedy.h" and defined in "graph_color_greedy.cpp."
This was our second iteration over the graph coloring solution. It improves on the first solution by greedily choosing the colors at each step based on which minimizes the cost function. If it cannot make a choice that is within a certain cost, it will terminate, increment the cost, and try again. The details of the data members, data structures, and algorithms will be skipped since it is not our final solution.
### Heuristical Complete Solution
This solution is implemented in the "GraphColorComplete" class. It is declared int "graph_color_complete.h" and defined in "graph_color_complete.cpp."
This was our final iteration over the graph coloring solution. It improves on the first solution by implementing heuristcal ways to choose colors and vertices. It also improves on the second solution by ensuring the minimum cost solution is returned.
#### General Overview
This section will provide a high level overview of the algorithms. A more thorough analysis will be followed in a later section.
1. The order the vertices are colored in is changed. The naive solution simply colors the vertices in order. It colors like so: $v_{0}$, $v_{1}$, ..., $v_{n}$. Our solution sorts the vertices on their degree in descending order. This means $v_{0}$ is the vertex with the largest degree.[^1] This does not lower the time complexity, but in some cases it will lead to shorter branches in the coloring decision tree by choosing vertices that affect other vertices the most first.
2. The order of adjacent vertices in the adjacency list are also sorted by degree. When checking if a color is safe, checking vertices with larger degrees first will likely lead to a failure faster.
3. A backtracking algorthm is used to color the vertices. This will be explained further in a later section.
#### Data Structures
All the data mvembers and data structures from the naive backtracking solution are inherited. The following are also defined:
- *int color_count[]*: A direct hash table that stores the current number of colors used during the coloring algorithm. It caches the counts so it does not have to be recalculated from *v_colors* during the coloring algorthm. Is used when calculating the cost of picking a color.
- *int v_pick_order[]*: A direct hash table that stores the order vertices should be colored in. For example, v_pick_order[0] holds the first vertex to be colored.
#### Algorithms
This solution inherits the *is_safe()* method from the naive backtracking solution and uses it. The following algorithms are changed and/or added:
- *set_pick_order()*: Orders the vertices in descending order based on degree.
- *set_adj_order()*: Goes through every vertex's adjacency list and orders the vertices based on degree.
- *color_vertices()*: A recursive function that colors a vertex and calls itself. If it tries all colors at the current iteration, it backtracks. It works in the following steps:
    1. If the current iteration number is the same as the number of vertices, a solution is found.
        - Calculated the cost of the solution. If it is lower than the current solution, update it. If the cost equals *best_solution*, then return from all the recursive calls.
        - Backtracks otherwise.
    2. Iterate through all the colors, k. If the color c can be used (no adjacent vertices have it) add it to an array. Also, calculate the cost of the current colors including c. Make that cost the key.
    3. Heapify that array such that the lowest cost color is at the top.
    4. Extract the min color from the heap and color the current vertex with it.
    5. Color the next vertex.
    6. Once (5) returns, uncolor the vertex and try the next.
    This solution makes the best color choices first by picking the colors that keep the cost the lowest. This, along with the other heuristics described, makes for a faster solution[^2] than the naive approach while still returning the lowest cost solution everytime.
#### Time Complexity Analysis
The time complexities of operations will be grouped into three subcategories: construction, preprocessing, and coloring. They will then be combined in the last subsection for the total time complexity of the solution. The notation from the Problem Definition will be used along with others described as needed.
##### Construction
1. Reading Graph from File: Reading the number of colors and vertices, parsing the adjacency matrix involves O(n^2) operations as each potential edge is processed once for a graph with n vertices.
2. Initializing GraphColorComplete Object: The complexity of resizing the color_count array is O(k), and for the v_pick_order array, it is O(n).
Overall, the complexity of the Construction category is dominated by the graph reading process. The complexity is O(n^2).
##### Preprocessing
1. Setting Adjacency Order (set_adj_order):
   - Complexity to construct degrees vector is O(n)
   - Sorting the degrees vector is O(n^2)
   - Sorting the adjacency list for each vertices is O(n) for the loop over each vertices and O(n^2) for the quicksort of degrees inside the loop. Which results in worst case complexity of O(n^3). Although the average case will be far lower since the degrees will            rarely almost equal the number of vertices.
2. Setting Vertex Pick Order (set_pick_order):
   - Complexity to construct degrees vector is O(n)
   - Sorting the degrees vector is O(n^2)
Overall, the complexity of the Preprocessing category is dominated by the set_adj_order with a worst case complexity of O(n^3).
##### Coloring
The main aspect of the Coloring category is the color_vertices recursive function. Here are the major steps of the function and their complexities.
1. Check for base case: Checking for the base case is O(1)
2. Loop to find safe colors: is_safe is a function to check if the color all neighboring vertices and has a complexity of O(n). is_safe is ran k color times. Resulting in a complexity of O(n*k).
3. Priorty Queue construction: Construction of priorty queue is O(k)
4. Recursive calls: The function is called recursively for each vertex and for each of these it is called recursively again k times. Resulting in k^n recursive calls. For each recursive call steps 1, 2, 3 are ran.
Overall, the final complexity of the coloring category is determined by the amount of recursive calls k^n, times steps 1, 2, 3. This means the final complexity is (k^n) * (1+(n*k)+(k)).
##### Total Complexity
The total complexity is dominated by the coloring category with a simplified complexity of (k^n)*(nk).

[^1]: Quicksort is used. It's worst case O({n^2}), but it's average case is O(nlogn). A worst case O(nlogn) sorting algorithm may be faster, but quicksort is what the STL in C++ uses. It also has O(1) space complexity.
[^2]: Faster here does not mean in terms of time complexity, rather, in terms of benchmarks. The time complexity is the same.
