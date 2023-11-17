#include "graph_color.h"

#include <iostream>

GraphColor::GraphColor(Graph &graph, int k) {
    this->k = k;
    this->graph = &graph;
    this->solution = nullptr;
    this->v_colors.resize(graph.n, 0);
    this->best_solution = (graph.n % k == 0) ? 0 : 1;
}

GraphColor::~GraphColor() {
    if (this->solution != nullptr)
        delete this->solution;
}

/* Check if vertex can be colored with color by
 * checking if any of its neighbors have the same color.
 */
bool GraphColor::is_safe(int vertex, int color) const {
    for (int u : this->graph->adj[vertex])
    {
        if (this->v_colors[u] == color) {
            return false;
        }
    }
 
    return true;
}

/* Sanity check to see if the solution is correct at end */
bool GraphColor::is_solution_correct() const {
    if (this->solution == nullptr)
        return false;
    for (int i = 0; i < this->graph->n; i++) {
        if (!this->is_safe(i, this->solution->v_colors[i])) {
            return false;
        }
    }
    return true;
}

void GraphColor::print_solution() const {
    if (this->solution == nullptr)
        std::cout << "No such a sequence exists." << std::endl;
    else
        this->solution->print_solution();
}

void GraphColor::set_solution(Solution *solution) {
    if (this->solution == nullptr)
        this->solution = solution;
    else if (*solution < *this->solution) {
        delete this->solution;
        this->solution = solution;
    } else {
        delete solution;
    }
    /* If no better solution is possible given |V| and k,
     * then we can stop early.
     */
    if (this->solution->cost == this->best_solution) {
        throw "Found most optimal solution early.";
    }
}

void GraphColor::color_vertices(int vertex, int num_vertices) {
    /* If all vertices are colored, then we have a solution */
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors);
        this->set_solution(s);
        return; /* Backtrack */
    }
 
    /* Try all possible colors for vertex */
    for (int c = 1; c <= k; c++) {
        if (this->is_safe(vertex, c)) {
            this->v_colors[vertex] = c;
            /* Recursively color the rest of the vertices */
            this->color_vertices(vertex + 1, num_vertices);
            this->v_colors[vertex] = 0;
        }
    }
    /* If we end up here, then we tried all colors, so
     * we can backtrack.
     */
}
