#include "graph.h"
#include <iostream>

Graph::Graph() {
    this->n = 0;
}

Graph::Graph(int n) {
    this->n = n;
    this->adj.resize(n);
}

/* Adds an edge from src to dest.
 * For undirected graphs, we need to add an edge from dest to src as well.
 */
void Graph::add_edge(int src, int dest) {
    if (src == dest) return;
    /* Graph supports directed edges
     * so we don't need to add the edge twice
     */
    this->adj[src].push_back(dest);
}

/* Copy constructor */
Graph::Graph(const Graph &g) {
    this->n = g.n;
    this->adj = g.adj;
}

void Graph::set_n(int n) {
    this->n = n;
    this->adj.resize(n);
}
