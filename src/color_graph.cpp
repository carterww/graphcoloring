#include "color_graph.h"

#include <algorithm>
#include <functional>
#include <math.h>
#include <iostream>
#include <queue>
#include <tuple>

ColorGraph::ColorGraph(Graph &graph, int k) {
    this->k = k;
    this->graph = &graph;
    this->solution = nullptr;
    this->v_colors.resize(graph.n, 0);
    this->color_count.resize(k + 1, 0);
    this->best_solution = (graph.n % k == 0) ? 0 : 1;
    this->v_pick_order.resize(graph.n, 0);
    this->set_pick_order();
}

void ColorGraph::set_pick_order() {
    if (this->graph->n >= 128) {
        this->set_pick_order_fast();
    } else {
        this->set_pick_order_accurate();
    }
}

void ColorGraph::set_pick_order_fast() {
    std::vector<std::tuple<int, int>> degrees(this->graph->n, std::make_tuple(0, 0));
    for (int i = 0; i < this->graph->n; i++) {
        std::get<0>(degrees[i]) = this->graph->adj[i].size();
        std::get<1>(degrees[i]) = i;
    }
    /* Sort the vertices by degree */
    std::sort(degrees.begin(), degrees.end(), std::greater<std::tuple<int, int>>());
    for (int i = 0; i < this->graph->n; i++) {
        this->v_pick_order[i] = std::get<1>(degrees[i]);
    }
}

void ColorGraph::set_pick_order_accurate() {
    std::vector<std::tuple<int, int>> degrees(this->graph->n, std::make_tuple(0, 0));
    for (int i = 0; i < this->graph->n; i++) {
        std::get<0>(degrees[i]) = this->graph->adj[i].size();
        std::get<1>(degrees[i]) = i;
    }
    /* Sort the vertices by degree */
    std::make_heap(degrees.begin(), degrees.end(), std::greater<std::tuple<int, int>>());
    for (int i = 0; i < this->graph->n; i++) {
        std::pop_heap(degrees.begin(), degrees.end());
        this->v_pick_order[i] = std::get<1>(degrees.back());
        degrees.pop_back();
        for (int u : this->graph->adj[this->v_pick_order[i]]) {
            for (int j = 0; j < degrees.size(); j++) {
                if (std::get<1>(degrees[j]) == u) {
                    std::get<0>(degrees[j])--;
                    std::push_heap(degrees.begin(), degrees.end());
                    break;
                }
            }
        }
    }
}

ColorGraph::~ColorGraph() {
    if (this->solution != nullptr)
        delete this->solution;
}

bool ColorGraph::is_safe(int vertex, int color) const {
    for (int u : this->graph->adj[vertex])
    {
        if (this->v_colors[u] == color) {
            return false;
        }
    }
 
    return true;
}


bool ColorGraph::is_solution_correct() const {
    if (this->solution == nullptr)
        return false;
    for (int i = 0; i < this->graph->n; i++) {
        for (int j : this->graph->adj[i]) {
            if (this->solution->v_colors[i] == this->solution->v_colors[j]) {
                return false;
            }
        }
    }
    return true;
}

void ColorGraph::print_solution() const {
    if (this->solution == nullptr)
        std::cout << "No such a sequence exists." << std::endl;
    else
        this->solution->print_solution();
}

void ColorGraph::set_solution(Solution *solution) {
    if (this->solution == nullptr)
        this->solution = solution;
    else if (*solution < *this->solution) {
        delete this->solution;
        this->solution = solution;
    } else {
        delete solution;
    }
    if (this->solution->cost == this->best_solution) {
        throw "Found most optimal solution early.";
    }
}

void ColorGraph::color_vertices(int vertex, int num_vertices) {
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors);
        this->set_solution(s);
        return;
    }
 
    std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, std::greater<std::tuple<int, int>>> safe_colors;
    for (int c = 1; c <= k; c++) {
        if (this->is_safe(this->v_pick_order[vertex], c)) {
            this->color_count[c]++;
            int cost = Solution::get_cost(k, color_count);
            safe_colors.push(std::make_tuple(cost, c));
            this->color_count[c]--;
        }
    }
    while (!safe_colors.empty()) {
        int cost = std::get<0>(safe_colors.top());
        int color = std::get<1>(safe_colors.top());
        safe_colors.pop();
        this->v_colors[this->v_pick_order[vertex]] = color;
        this->color_count[color]++;
        this->color_vertices(vertex + 1, num_vertices);
        this->color_count[color]--;
        this->v_colors[this->v_pick_order[vertex]] = 0;
    }
}
