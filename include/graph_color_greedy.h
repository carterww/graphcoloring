#ifndef GRAPH_COLOR_GREEDY_H
#define GRAPH_COLOR_GREEDY_H

#include "graph.h"
#include "graph_color.h"

class GraphColorGreedy : public GraphColor {
public:
    GraphColorGreedy(Graph &graph, int k);
    virtual ~GraphColorGreedy();

    void color_vertices(int vertex, int num_vertices);
private:
    int max_cost;
    bool is_safe(int vertex, int color);
    bool color_vertices_imp(int vertex, int num_vertices);
};
#endif
