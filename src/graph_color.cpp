#include "graph_color.h"

#include <iostream>

GraphColor::GraphColor(Graph &graph, int k) {
    this->k = k;
    this->graph = &graph;
    this->solution = nullptr;
    this->v_colors.resize(graph.n, 0);
}

GraphColor::~GraphColor() {
    if (this->solution != nullptr)
        delete this->solution;
}

bool GraphColor::is_safe(int vertex, int color) const {
    for (int u : this->graph->adj[vertex])
    {
        if (this->v_colors[u] == color) {
            return false;
        }
    }
 
    return true;
}

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
    if (this->solution->cost == 0) {
        throw "Found most optimal solution early.";
    }
}

void GraphColor::color_vertices(int vertex, int num_vertices) {
    // if all colors are assigned, print the solution
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors);
        this->set_solution(s);
        return;
    }
 
    // try all possible combinations of available colors
    for (int c = 1; c <= k; c++) {
        // if it is safe to assign color `c` to vertex `v`
        if (this->is_safe(vertex, c)) {
            // assign color `c` to vertex `v`
            this->v_colors[vertex] = c;
 
            // recur for the next vertex
            this->color_vertices(vertex + 1, num_vertices);
 
            // backtrack
            this->v_colors[vertex] = 0;
        }
    }
}
