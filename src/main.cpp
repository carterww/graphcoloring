#include "graph_coloring.h"
#include "color_graph.h"
#include "input.h"
#include <chrono>
#include <fstream>
#include <iostream>

#define DEBUG

int main(int argc, char *argv[]) {
    std::ifstream input_file("graph4.txt");
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

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
#ifdef DEBUG
    /*
    GraphColor gc = GraphColor(g, k);
    start = std::chrono::high_resolution_clock::now();
    try {
        gc.color_vertices(0, g.n);
    } catch (const char * c) {
        std::cout << c << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    gc.print_solution();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
    */
    GraphColorGreedy gcg = GraphColorGreedy(g, k);
    start = std::chrono::high_resolution_clock::now();
    try {
        gcg.color_vertices(0, g.n);
    } catch (const char * c) {
        std::cout << c << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    gcg.print_solution();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
#endif
    ColorGraph cg = ColorGraph(g, k);
    start = std::chrono::high_resolution_clock::now();
    try {
        cg.color_vertices(0, g.n);
    } catch (const char * c) {
        std::cout << c << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    cg.print_solution();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
    std::cout << "Solution correct: " << cg.is_solution_correct() << std::endl;
    return 0;
}
