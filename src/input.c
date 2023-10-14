#include "input.h"  
#include <stdio.h>

graph *read_graph(FILE *input_file) {
    graph *g = malloc(sizeof(graph));
    char buff[READ_BUFFER_SIZE] = { 0 };
    fgets(buff, READ_BUFFER_SIZE, input_file);
    g->num_colors = atoi(buff);
    fgets(buff, READ_BUFFER_SIZE, input_file);
    g->num_vertices = atoi(buff);

    g->adj_matrix = malloc(sizeof(char *) * g->num_vertices);
    for (int i = 0; i < g->num_vertices; i++) {
        g->adj_matrix[i] = malloc(sizeof(char) * g->num_vertices);
        fgets(buff, READ_BUFFER_SIZE, input_file);
        for (int j = 0; j < g->num_vertices; j++) {
            g->adj_matrix[i][j] = buff[j] - '0';
        }
    }
    return g;
}
