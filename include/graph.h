#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    std::vector<std::vector<int>> adj;
    int n;
 
    // Constructor
    Graph();
    Graph(int n);

    Graph(const Graph &g);

    void add_edge(int src, int dest);
    void set_n(int n);
};

#endif
