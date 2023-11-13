#ifndef COLOR_GRAPH_H
#define COLOR_GRAPH_H

#include "graph.h"
#include "graph_coloring.h"

class ColorGraph {
public:
    ColorGraph(Graph &graph, int k);
    ~ColorGraph();

    void color_vertices(int vertex, int num_vertices);
    void print_solution() const;
    /* Sanity check to see if the solution is correct at end */
    bool is_solution_correct() const;
private:
    int k;
    /* Best possible solution given the number of vertices and colors */
    int best_solution;
    Graph *graph;
    Solution *solution;
    /* Colors of vertices */
    std::vector<int> v_colors;
    /* Number of vertices of each color at each step.
     * Used for calculating the cost of the current solution
     * at each step.
     */
    std::vector<int> color_count;
    std::vector<int> v_pick_order;

    /* Returns true if the vertex can be colored with the given color */
    bool is_safe(int vertex, int color) const;
    /* Sets a new solution if the cost is less than the old one */
    void set_solution(Solution *solution);
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
