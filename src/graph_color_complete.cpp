#include "graph_color_complete.h"

#include <algorithm>
#include <functional>
#include <math.h>
#include <iostream>
#include <queue>
#include <tuple>

GraphColorComplete::GraphColorComplete(Graph &graph, int k) : GraphColor(graph, k) {
    this->color_count.resize(k + 1, 0);
    this->v_pick_order.resize(graph.n, 0);
    this->set_pick_order();
}

void GraphColorComplete::set_pick_order() {
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

GraphColorComplete::~GraphColorComplete() {
    /* Nothing to do here */
}

void GraphColorComplete::color_vertices(int vertex, int num_vertices) {
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors);
        this->set_solution(s);
        return;
    }
 
    std::vector<std::tuple<int, int>> safe_colors_vec;
    for (int c = 1; c <= k; c++) {
        if (this->is_safe(this->v_pick_order[vertex], c)) {
            this->color_count[c]++;
            int cost = Solution::get_cost(k, color_count);
            safe_colors_vec.push_back(std::make_tuple(cost, c));
            this->color_count[c]--;
        }
    }
    /* Construct after to stay O(n) instead of O(nlogn) */
    std::priority_queue<
        std::tuple<int, int>,
        std::vector<std::tuple<int, int>>,
        std::greater<std::tuple<int, int>>
            > safe_colors(safe_colors_vec.begin(), safe_colors_vec.end());

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
