#include "input.h"
#include <iostream>
#include <sstream>
#include <string>

/* Reads the graph from the input file.
 * The first line contains the number of colors.
 * The second line contains the number of vertices.
 * The next n lines contain the adjacency matrix.
 */
int read_graph(std::ifstream &filename, Graph &g, int &k) {
    std::string line;

    /* Get number of colors */
    std::getline(filename, line);
    k = std::stoi(line);

    /* Get number of vertices */
    std::getline(filename, line);
    g.set_n(std::stoi(line));

    /* Iterate through n lines to get all edges */
    for (int src = 0; src < g.n; src++) {
        std::getline(filename, line);
        int dest = 0;
        for (char &c : line) {
            if (c == ' ')
                continue;
            else if (c == '1')
                g.add_edge(src, dest++);
            else if (c == '0')
                dest++;
            if (dest >= g.n)
                break;
        }
    }

    filename.close();
    return 0;
}

/* Reads multiple graphs from multiple input files. 
 * Allows for easy testing of multiple graphs at once.
 */
int read_graphs(int argc, char **argv, std::vector<Graph*> &graphs, std::vector<int> &ks) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input file> [<input file> ...]" << std::endl;
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        std::ifstream input_file(argv[i]);
        if (!input_file.is_open()) {
            std::cout << "Error opening file " << argv[i] << std::endl;
            return 1;
        }
        Graph *g = new Graph();
        int k;
        if (read_graph(input_file, *g, k) != 0) {
            std::cout << "Error reading graph" << std::endl;
            return 1;
        }
        graphs.push_back(g);
        ks.push_back(k);
    }
    return 0;
}
