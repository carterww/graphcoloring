#include <iostream>
#include "graph_coloring.h"
#include "colors.h"

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
    std::vector<std::string> color_uses(this->k + 1, "");
    for (int i = 1; i < color_uses.size(); i++) {
        color_uses[i] += COLORS[i];
        int str_len = color_uses[i].length();
        for (int j = 0; j < 10 - str_len; j++) {
            color_uses[i] += " ";
        }
        color_uses[i] += ": ";
    }
    int *has_added = new int[this->k + 1] {0};
    for (int i = 0; i < this->v_colors.size(); i++) {
        if (has_added[this->v_colors[i]] == 0) {
            color_uses[this->v_colors[i]] += std::to_string(i);
            has_added[this->v_colors[i]] = 1;
        } else {
            color_uses[this->v_colors[i]] += ", ";
            color_uses[this->v_colors[i]] += std::to_string(i);
        }
    }
    delete[] has_added;
    for (int i = 1; i < color_uses.size(); i++) {
        std::cout << color_uses[i] << std::endl;
    }
}

GraphColor::GraphColor(Graph &graph, int k) {
    this->k = k;
    this->graph = &graph;
    this->solution = nullptr;
    this->v_colors.resize(graph.n, 0);
}

GraphColorGreedy::GraphColorGreedy(Graph &graph, int k) : GraphColor(graph, k) {
    this->max_cost = 0;
}

GraphColor::~GraphColor() {
    if (this->solution != nullptr)
        delete this->solution;
}

GraphColorGreedy::~GraphColorGreedy() {
    /* Nothing to do here */
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
