#include <electrostatic/electronetsoft/algorithm/arithmos/graph/math_structs.h>

uint8_t graph_iterate_edge_matrix(edge_matrix *matrix, graph_processors *processors) {
    if (matrix == NULL || matrix->cells == NULL || processors == NULL) {
        return 1;
    }
    for (int c = 0; c < matrix->cell_length; c++) {
        edge **m_edge = matrix->cells[c];
        if (m_edge == NULL) {
            continue;
        }
        if (processors->graph_cell_traversed != NULL) {
            processors->graph_cell_traversed(matrix, m_edge, c);
        }
        for (int e = 0; e < matrix->cell_length; e++) {
            if (m_edge[e] == NULL) {
                continue;
            }
            if (processors->graph_cellular_edge_traversed != NULL) {
                processors->graph_cellular_edge_traversed(matrix, m_edge[e], e);
            }
        }
    }
    return 0;
}


uint8_t graph_iterate_edge(edge_path *path, graph_processors *processors) {
    if (path == NULL || path->edges == NULL || processors == NULL) {
        return 1;
    }
    for (int e = 0; e < path->count; e++) {
        if (path->edges[e] == NULL) {
            continue;
        }
        if (processors->graph_edge_path_traversed != NULL) {
            processors->graph_edge_path_traversed(path, path->edges[e], e);
        }
    }
    return 0;
}
