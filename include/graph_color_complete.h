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
    /* Best possible solution given the number of vertices and colors */
    int best_solution;
    /* Number of vertices of each color at each step.
     * Used for calculating the cost of the current solution
     * at each step.
     */
    std::vector<int> color_count;
    std::vector<int> v_pick_order;

    /* Sets the pick order of the vertices */
    void set_pick_order();
    /* Sets the pick order of the vertices in a fast way.
     * This is done by using the degree of each vertex, but
     * it does not update the degree after the largest is picked.
     * This allows us to use quicksort to sort the vertices.
     */
    void set_pick_order_fast();
    /* More accurate than fast version because after a vertex is picked,
     * the degree of the adjacent vertices is updated. It is slower than 
     * the fast version because it uses a priority queue which will have many
     * decrease_key operations.
     */
    void set_pick_order_accurate();
};
#endif
