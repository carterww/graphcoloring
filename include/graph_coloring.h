#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

#include <vector>

#include "graph.h"

class Solution {
public:
    Solution(int k, const std::vector<int> &v_colors);

    void print_solution() const;
    bool operator<(const Solution &other) const;
    int cost;
protected:
    int k;
    std::vector<int> color_use;
    std::vector<int> v_colors;

    virtual void calculate_cost();
};

class GraphColor {
public:
    GraphColor(Graph &graph, int k);
    virtual ~GraphColor();

    virtual void color_vertices(int vertex, int num_vertices);
    virtual void print_solution() const;
protected:
    int k;
    Graph *graph;
    Solution *solution;
    std::vector<int> v_colors;

    /* I think this can be same for all coloring techniques */
    bool is_safe(int vertex, int color) const;
};

#endif
