#include "graph_color_greedy.h"
#include <iostream>

GraphColorGreedy::GraphColorGreedy(Graph &graph, int k) : GraphColor(graph, k) {
    this->max_cost = 0;
}

GraphColorGreedy::~GraphColorGreedy() {
    /* Nothing to do here */
}

bool GraphColorGreedy::is_safe(int vertex, int color) {
    for (int u : this->graph->adj[vertex])
    {
        if (this->v_colors[u] == color) {
            return false;
        }
    }
    // Temporarily assign color to see the potential cost
    int original_color =  this->v_colors[vertex];
    this->v_colors[vertex] = color;

    // Calculate the potential cost after assigning new color
    int potential_cost = 0;
    std::vector<int> color_count(this->k + 1, 0);
    for (int i = 0; i < this->v_colors.size(); i++) {
        color_count[this->v_colors[i]]++;
    }
    
    // Compare the counts of each color and calculate cost
    for (int i = 1; i < color_count.size() - 1; i++) {
        potential_cost += abs(color_count[i] - color_count[i + 1]);
    }

    // Revert the color back to original
    this->v_colors[vertex] = original_color;

    return potential_cost <= this->max_cost;
}

void GraphColorGreedy::color_vertices(int vertex, int num_vertices) {
    bool found = false;
    while (!found && this->max_cost <= k) {
        try {
            found = this->color_vertices_imp(vertex, num_vertices);
        } catch (const char * c) {
            std::cout << c << std::endl;
            found = true;
        }
        this->max_cost++;
    }
}

bool GraphColorGreedy::color_vertices_imp(int vertex, int num_vertices) {
    // if all colors are assigned, print the solution
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors);
        this->set_solution(s);
        return true;
    }

    bool found = false;
 
    // try all possible combinations of available colors
    for (int c = 1; c <= k; c++) {
        // if it is safe to assign color `c` to vertex `v`
        if (this->is_safe(vertex, c)) {
            // assign color `c` to vertex `v`
            this->v_colors[vertex] = c;
 
            // recur for the next vertex
            found = this->color_vertices_imp(vertex + 1, num_vertices);
 
            // backtrack
            if (!found)
                this->v_colors[vertex] = 0;
        }
    }

    return found;
}
