#ifndef GRAPH_COLOR_COMPLETE_H
#define GRAPH_COLOR_COMPLETE_H

#include "graph.h"
#include "graph_color.h"
#include "solution.h"

class GraphColorComplete : public GraphColor {
public:
    GraphColorComplete(Graph &graph, int k);
    ~GraphColorComplete();

    void color_vertices(int vertex, int num_vertices);
private:
    /* Number of vertices of each color at each step.
     * Used for calculating the cost of the current solution
     * at each step.
     */
    std::vector<int> color_count;
    std::vector<int> v_pick_order;

    /* Sets the pick order of the vertices */
    void set_pick_order();
};
#endif
