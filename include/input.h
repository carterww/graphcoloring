#ifndef _INPUT_H_
#define _INPUT_H_

#define READ_BUFFER_SIZE 256

#include <stdio.h>
#include <stdlib.h>

/* Graph structure
 * num_colors: number of colors
 * num_vertices: number of vertices
 * adj_matrix: adjacency matrix
 */
typedef struct {
    unsigned int num_colors;
    unsigned int num_vertices;
    char **adj_matrix;
} graph;

/* Read graph from file
 * input_file: input file
 * return: graph
 * See input.txt for file format
 */
graph *read_graph(FILE *input_file);

#endif /* _INPUT_H_ */
