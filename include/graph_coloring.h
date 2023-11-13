#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

#include <vector>
#include <tuple>

#include "graph.h"

class Solution {
public:
    Solution(int k, const std::vector<int> &v_colors);

    static int get_cost(int k, const std::vector<int> &color_count);
    void print_solution() const;
    bool operator<(const Solution &other) const;
    std::vector<int> v_colors;
    int cost;
protected:
    int k;
    std::vector<int> color_use;

    virtual void calculate_cost();
};

class GraphColor {
public:
    GraphColor(Graph &graph, int k);
    virtual ~GraphColor();

    virtual void color_vertices(int vertex, int num_vertices);
    virtual void print_solution() const;
protected:
    int k;
    Graph *graph;
    Solution *solution;
    std::vector<int> v_colors;

    /* I think this can be same for all coloring techniques */
    bool is_safe(int vertex, int color) const;
    void set_solution(Solution *solution);
};

class GraphColorGreedy : public GraphColor {
public:
    GraphColorGreedy(Graph &graph, int k);
    virtual ~GraphColorGreedy();

    virtual void color_vertices(int vertex, int num_vertices);
protected:
    int max_cost;

    virtual bool is_safe(int vertex, int color);
private:
    bool color_vertices_imp(int vertex, int num_vertices);
};

#endif
