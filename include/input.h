#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <string>


#include "graph.h"

/* Add edges and number of vertices to graph obj
 * from file. Returns 0 on success, something else
 * otherwise. Puts number of colors in k.
 */
int read_graph(std::ifstream &filename, Graph &graph, int &k);

#endif
