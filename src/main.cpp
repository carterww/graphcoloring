#include "graph_coloring.h"
#include "input.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    std::ifstream input_file("graph.txt");
    if (!input_file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    Graph g = Graph();
    int k;
    if (read_graph(input_file, g, k) != 0) {
        std::cout << "Error reading graph" << std::endl;
        return 1;
    }
    std::cout << "Graph read successfully" << std::endl;

    GraphColor gc = GraphColor(g, k);
    try {
        gc.color_vertices(0, g.n);
    } catch (const char * c) {
        std::cout << c << std::endl;
    }
    gc.print_solution();

    return 0;
}
