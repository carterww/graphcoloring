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
    this->set_adj_order();
}

/* Order vertices by degree so vertices with a larger degree
 * are colored first. This is a heuristic to reduce the branching factor.
 */
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

/* Order the adjacency lists so that vertices with a larger degree are
 * checked for safety first. This heuristic should hopefully detect
 * safety violations earlier because vertices with a larger degree
 * are more likely to have a neighbor with the same color.
 */
void GraphColorComplete::set_adj_order() {
    std::vector<std::tuple<int, int>> degrees(this->graph->n, std::make_tuple(0, 0));
    for (int i = 0; i < this->graph->n; i++) {
        std::get<0>(degrees[i]) = this->graph->adj[i].size();
        std::get<1>(degrees[i]) = i;
    }
    /* Sort the vertices by degree */
    std::sort(degrees.begin(), degrees.end(), std::greater<std::tuple<int, int>>());
    for (int i = 0; i < this->graph->n; i++) {
        std::vector<std::tuple<int, int>> adj_list(this->graph->adj[i].size(), std::make_tuple(0, 0));
        for (int j = 0; j < this->graph->adj[i].size(); j++) {
            std::get<0>(adj_list[j]) = std::get<0>(degrees[this->graph->adj[i][j]]);
            std::get<1>(adj_list[j]) = this->graph->adj[i][j];
        }
        /* Sort the adjacent vertices by degree */
        std::sort(adj_list.begin(), adj_list.end(), std::greater<std::tuple<int, int>>());
        for (int j = 0; j < this->graph->adj[i].size(); j++) {
            this->graph->adj[i][j] = std::get<1>(adj_list[j]);
        }
    }
}

GraphColorComplete::~GraphColorComplete() {
    /* Nothing to do here */
}

/* Backtracking algorithm to color the graph.
 * This version uses heuristics to pick the next vertex and color, but
 * is not greedy.
 */
void GraphColorComplete::color_vertices(int vertex, int num_vertices, int cost) {
    /* If we are on the last vertex, then we have a solution */
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors, cost, this->color_count);
        this->set_solution(s);
        return;
    }
 
    /* Vector of safe colors for the current vertex and their costs */
    std::vector<std::tuple<int, int>> safe_colors_vec;
    for (int c = 1; c <= k; c++) {
        if (this->is_safe(this->v_pick_order[vertex], c)) {
            this->color_count[c]++;
            int cost = Solution::get_cost(k, color_count);
            safe_colors_vec.push_back(std::make_tuple(cost, c));
            this->color_count[c]--;
        }
    }
    /* Construct a binary heap from the safe colors based on their costs.
     * This allows for colors that have lower costs to be picked first.
     */
    std::priority_queue<
        std::tuple<int, int>,
        std::vector<std::tuple<int, int>>,
        std::greater<std::tuple<int, int>>
            > safe_colors(safe_colors_vec.begin(), safe_colors_vec.end());

    /* While the heap is not empty, pick a color and color the vertex.
     * Then, recursively color the next vertex.
     * After the recursive call, backtrack by removing the color from the vertex.
     */
    while (!safe_colors.empty()) {
        /* Extract min */
        int cost = std::get<0>(safe_colors.top());
        int color = std::get<1>(safe_colors.top());
        safe_colors.pop();
        this->v_colors[this->v_pick_order[vertex]] = color;
        this->color_count[color]++;
        /* Color the next vertex */
        this->color_vertices(vertex + 1, num_vertices, cost);
        this->color_count[color]--;
        this->v_colors[this->v_pick_order[vertex]] = 0;
    }
    /* If we are here, then we tried all colors so we can backtrack */
}
