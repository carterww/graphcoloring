#include <iostream>
#include "graph_coloring.h"

Solution::Solution(int k, const std::vector<int> &v_colors) {
    this->k = k;
    this->v_colors = std::vector<int>(v_colors);
    this->color_use.resize(k + 1, 0);
    for (int i = 0; i < v_colors.size(); i++) {
        this->color_use[v_colors[i]]++;
    }
    
    this->calculate_cost();
}

void Solution::calculate_cost() {
    this->cost = 0;
    for (int i = 1; i < this->color_use.size() - 1; i++) {
        this->cost += abs(this->color_use[i] - this->color_use[i + 1]);
    }
}

bool Solution::operator<(const Solution &other) const {
    std::cout << "Comparing " << this->cost << " to " << other.cost << std::endl;
    return this->cost < other.cost;
}

void Solution::print_solution() const {
    /* Need to redesign this class for efficiently storing
     * the # of times each color is used along with the
     * verticies grouped by color. Shouldn't be hard I'm just
     * lazy rn.
     */
    std::cout << "(";
    for (int i = 1; i < this->color_use.size() - 1; i++) {
        std::cout << this->color_use[i] << ",";
    }
    std::cout << this->color_use[this->color_use.size() - 1] << ")" << std::endl;
    for (int i = 0; i < this->v_colors.size(); i++) {
        std::cout << i << ": " << this->v_colors[i] << std::endl;
    }
}

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

void GraphColor::print_solution() const {
    if (this->solution == nullptr)
        std::cout << "No solution found." << std::endl;
    else
        this->solution->print_solution();
}

void GraphColor::color_vertices(int vertex, int num_vertices) {
    // if all colors are assigned, print the solution
    if (vertex == num_vertices)
    {
        Solution *s = new Solution(this->k, this->v_colors);
        if (this->solution == nullptr ||
                *s < *this->solution) {
            delete this->solution;
            this->solution = s;
        } else {
            delete s;
        }
        if (this->solution->cost == 0) {
            throw "Found most optimal solution.";
        }
        return;
    }
 
    // try all possible combinations of available colors
    for (int c = 1; c <= k; c++)
    {
        // if it is safe to assign color `c` to vertex `v`
        if (this->is_safe(vertex, c))
        {
            // assign color `c` to vertex `v`
            this->v_colors[vertex] = c;
 
            // recur for the next vertex
            this->color_vertices(vertex + 1, num_vertices);
 
            // backtrack
            this->v_colors[vertex] = 0;
        }
    }
}
