#include "graph.h"
#include <iostream>

Graph::Graph() {
    this->n = 0;
}

Graph::Graph(int n) {
    this->n = n;
    this->adj.resize(n);
}

void Graph::add_edge(int src, int dest) {
    if (src == dest) return;
    /* Searching these is not super necessary but the list is sorted, and
     * I don't wanna chase bugs with duplicate edges
     */
    if (!std::binary_search (adj[src].begin(), adj[src].end(), dest))
        this->adj[src].push_back(dest);
    if (!std::binary_search (adj[dest].begin(), adj[dest].end(), src))
        this->adj[dest].push_back(src);
}

Graph::Graph(const Graph &g) {
    this->n = g.n;
    this->adj = g.adj;
}


void Graph::set_n(int n) {
    this->n = n;
    this->adj.resize(n);
}
