#include "input.h"
#include <iostream>
#include <sstream>
#include <string>

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
