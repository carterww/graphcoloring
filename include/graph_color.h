#ifndef GRAPH_COLOR_H
#define GRAPH_COLOR_H

#include "graph.h"
#include "solution.h"

#include <vector>

class GraphColor {
public:
    GraphColor(Graph &graph, int k);
    virtual ~GraphColor();

    virtual void color_vertices(int vertex, int num_vertices);
    virtual void print_solution() const;
    /* Sanity check to see if the solution is correct at end */
    bool is_solution_correct() const;
protected:
    int k;
    Graph *graph;
    Solution *solution;
    std::vector<int> v_colors;

    virtual bool is_safe(int vertex, int color) const;
    void set_solution(Solution *solution);
};

#endif
