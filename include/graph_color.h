#ifndef GRAPH_COLOR_H
#define GRAPH_COLOR_H

#include "graph.h"
#include "solution.h"

#include <vector>

/* Base class for graph coloring algorithms */
class GraphColor {
public:
    GraphColor(Graph &graph, int k);
    virtual ~GraphColor();

    /* Backtracking algorithm to color the graph */
    virtual void color_vertices(int vertex, int num_vertices);
    virtual void print_solution() const;
    /* Sanity check to see if the solution is correct at end */
    bool is_solution_correct() const;
protected:
    int k;
    Graph *graph;
    Solution *solution;
    /* Direct hash table to store the colors of each vertex */
    std::vector<int> v_colors;
    /* Best possible solution given the number of vertices and colors */
    int best_solution;

    /* Check if vertex can be colored with color by
     * checking if any of its neighbors have the same color.
     */
    virtual bool is_safe(int vertex, int color) const;
    /* Sets the solution if it is better than the current solution */
    void set_solution(Solution *solution);
};

#endif
