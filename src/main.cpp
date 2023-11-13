#include "graph_color.h"
#include "graph_color_complete.h"
#include "graph_color_greedy.h"
#include "input.h"
#include <chrono>
#include <fstream>
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;

#define GRAPH_COLOR
#define GRAPH_COLOR_GREEDY

void print_time(TimePoint start, TimePoint end);

int main(int argc, char *argv[]) {
    std::vector<Graph*> graphs;
    std::vector<int> ks;
    if (read_graphs(argc, argv, graphs, ks) != 0) {
        return 1;
    }

    std::cout << "Graph read successfully" << std::endl;

    for (int i = 0; i < graphs.size(); i++) {
        TimePoint start, end;

        #ifdef GRAPH_COLOR
        GraphColor gc = GraphColor(*graphs[i], ks[i]);
        start = Clock::now();
        try {
            gc.color_vertices(0, graphs[i]->n);
        } catch (const char * c) {}
        end = Clock::now();
        gc.print_solution();
        print_time(start, end);
        #endif
        
        #ifdef GRAPH_COLOR_GREEDY
        GraphColorGreedy gcg = GraphColorGreedy(*graphs[i], ks[i]);
        start = Clock::now();
        try {
            gcg.color_vertices(0, graphs[i]->n);
        } catch (const char * c) {}
        end = Clock::now();
        gcg.print_solution();
        print_time(start, end);
        #endif

        GraphColorComplete gcc = GraphColorComplete(*graphs[i], ks[i]);
        start = Clock::now();
        try {
            gcc.color_vertices(0, graphs[i]->n);
        } catch (const char * c) {}
        end = Clock::now();
        gcc.print_solution();
        print_time(start, end);
    }
    return 0;
}

void print_time(TimePoint start, TimePoint end) {
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us" << std::endl;
}
