#ifndef COLOR_GRAPH_H
#define COLOR_GRAPH_H

#include "graph_coloring.h"
#include "graph.h"

#include <iostream>
#include <tuple>

class ColorGraph {
public:
    ColorGraph(Graph &graph, int k);
    virtual ~ColorGraph();

    bool is_solution_safe();
    virtual void color_vertices(int vertex, int num_vertices);
    virtual void print_solution() const;
protected:
    int k;
    Solution *solution;
    Graph *graph;
    std::vector<int> v_colors;

    /* I think this can be same for all coloring techniques */
    bool is_safe(int vertex, int color);


private:
    int *vertex_choice_order;
    char **v_domain;
    std::vector<std::tuple<int, int>> choice_stack;
    std::vector<std::tuple<int, int>> tmp_stack;
    void push_choice(int vertex, int color);
    void pop_choice();
    void order_vertices();
    void set_solution(Solution *solution);
};

#endif
