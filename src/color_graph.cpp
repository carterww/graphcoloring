#include "test.h"
#include "graph_coloring.h"
#include "graph.h"
#include <iostream>

ColorGraph::ColorGraph(Graph &graph, int k) {
    this->graph = &graph;
    this->k = k;
    this->solution = nullptr;
    this->v_colors.resize(graph.n, 0);
    this->vertex_choice_order = new int[graph.n];
    this->order_vertices();
    this->v_domain = new char*[graph.n];
    for (int i = 0; i < graph.n; i++) {
        this->v_domain[i] = new char[k + 1];
        this->v_domain[i][0] = 0;
        for (int j = 1; j <= k; j++) {
            this->v_domain[i][j] = 1;
        }
    }
    this->choice_stack.resize(graph.n * k, std::make_tuple(-1, -1));
    this->tmp_stack.resize(graph.n, std::make_tuple(-1, -1));
}

ColorGraph::~ColorGraph() {
    if (this->solution != nullptr)
        delete this->solution;
    delete[] this->vertex_choice_order;
    for (int i = 0; i < this->graph->n; i++) {
        delete[] this->v_domain[i];
    }
    delete[] this->v_domain;
}

/* This can be sorted more efficiently */
void ColorGraph::order_vertices() {
    int *degree = new int[this->graph->n];
    for (int i = 0; i < this->graph->n; i++) {
        degree[i] = this->graph->adj[i].size();
    }

    for (int i = 0; i < this->graph->n; i++) {
        int max_degree = -1;
        int max_degree_vertex = -1;
        for (int j = 0; j < this->graph->n; j++) {
            if (degree[j] > max_degree) {
                max_degree = degree[j];
                max_degree_vertex = j;
            }
        }
        this->vertex_choice_order[i] = max_degree_vertex;
        for (int u : this->graph->adj[max_degree_vertex]) {
            degree[u]--;
        }
        degree[max_degree_vertex] = -1;
    }

    delete[] degree;
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
    if (this->solution->cost == 0) {
        throw "Found most optimal solution early.";
    }
}

bool ColorGraph::is_safe(int vertex, int color) {
    for (int u : this->graph->adj[vertex_choice_order[vertex]]) {
        if (this->v_colors[u] == color) {
            return false;
        }
    }
 
    return true;
}

bool ColorGraph::is_solution_safe() {
    for (int i = 0; i < this->graph->n; i++) {
        for (int j = 0; j < this->graph->adj[i].size(); j++) {
            if (this->solution->v_colors[i] == this->solution->v_colors[graph->adj[i][j]]) {
                return false;
            }
        }
    }

    return true;
}
void ColorGraph::push_choice(int vertex, int color) {
    int num_updates = 0;
    for (int u : this->graph->adj[this->vertex_choice_order[vertex]]) {
        if (this->v_domain[u][color] == 0)
            continue;
        this->v_domain[u][color] = 0;
        this->choice_stack.push_back(std::make_tuple(u, color));
        num_updates++;
    }
    this->tmp_stack.push_back(std::make_tuple(vertex, num_updates));
}

void ColorGraph::pop_choice() {
    auto choice = this->tmp_stack.back();
    this->tmp_stack.pop_back();
    int vertex = std::get<0>(choice);
    int num_updates = std::get<1>(choice);
    for (int i = 0; i < num_updates; i++) {
        auto choice = this->choice_stack.back();
        this->choice_stack.pop_back();
        int u = std::get<0>(choice);
        int color = std::get<1>(choice);
        this->v_domain[u][color] = 1;
    }
}

void ColorGraph::color_vertices(int vertex, int num_vertices) {
    if (vertex == num_vertices) {
        Solution *s = new Solution(this->k, this->v_colors);
        this->set_solution(s);
        return;
    }

    for (int color = 1; color <= this->k; color++) {
        if (this->v_domain[vertex_choice_order[vertex]][color] == 0)
            continue;
        this->v_colors[this->vertex_choice_order[vertex]] = color;
        this->push_choice(vertex, color);
        this->color_vertices(vertex + 1, num_vertices);
        this->v_colors[this->vertex_choice_order[vertex]] = 0;
        this->pop_choice();
    }
}

void ColorGraph::print_solution() const {
    if (this->solution == nullptr) {
        std::cout << "No such a sequence exists." << std::endl;
        return;
    }
    this->solution->print_solution();
}
