#include <electronetsoft/arithmos/graph/dijkstra.h>

static inline int dijkstra_init(dijkstra_structure *d_struct, path *pd_path, int start) {
    if (d_struct == NULL || pd_path == NULL || pd_path->vertices == NULL) {
        return -1;
    }
    fprintf(stdout, "dijkstra_init: Passed Sanity checks!\n");
    fprintf(stdout, "dijkstra_init: First item %p\n", pd_path->vertices + 1);
    for (int i = 0; i < d_struct->cell_length; i++) {
        (*pd_path->vertices)[i].position = __INFINITY;
        (*pd_path->vertices)[i].is_visited = 0;
        (*pd_path->vertices)[i].data = d_struct->matrix->cells[i][0]->data;
        if (d_struct->processors != NULL && d_struct->processors->initializing_vertices_processor != NULL) {
            d_struct->processors->initializing_vertices_processor(d_struct);
        }
        fprintf(stdout, "dijkstra_init: Processing for initialization!\n");
    }
    (*pd_path->vertices)[start].position = 0;

    return 0;
}

static inline int dijkstra_get_lesser(dijkstra_structure *d_struct, path *pd_path, int base_position, path *out) {
    if (d_struct == NULL || d_struct->matrix == NULL || pd_path == NULL || pd_path->vertices == NULL) {
        return -1;
    }
    int lesser_position = base_position;
    int vertex_index = -1;
    fprintf(stdout, "dijkstra_get_lesser: Passed Sanity checks!\n");

    for (int v = 0; v < d_struct->cell_length; v++) {
        if ((*pd_path->vertices)[v].is_visited) {
            continue;
        }
        fprintf(stdout, "dijkstra_get_lesser: Processing: %d\n", (*pd_path->vertices)[v].position);

        if ((*pd_path->vertices)[v].position < lesser_position) {
            lesser_position = (*pd_path->vertices)[v].position;
            vertex_index = v;
            if (d_struct->processors != NULL && d_struct->processors->lesser_vertex_retrieval_processor != NULL) {
                d_struct->processors->lesser_vertex_retrieval_processor(d_struct, out);
            }
        }
        fprintf(stdout, "dijkstra_get_lesser: Processing lesser distance algorithm!\n");
    }
    if (vertex_index != -1) {
        (*pd_path->vertices)[vertex_index].is_visited = 1;
        out->vertices[out->cell_length] = &(*pd_path->vertices)[vertex_index];
        out->cell_length += 1;
        if (d_struct->processors != NULL && d_struct->processors->on_lesser_vertex_found != NULL) {
            d_struct->processors->on_lesser_vertex_found(d_struct, out);
        }
        fprintf(stdout, "dijkstra_get_lesser: Lesser path found!\n");
    }
    return vertex_index;
}

/**
 * Updates a position dependent path from a corresponding cell inside a cellular matrix; such that
 * the new values have a lesser total distance from the current vertex than its predecessor vertices.
 */
static inline uint8_t dijkstra_update_path_from_cell(dijkstra_structure *d_struct, int cell_index, path *pd_path) {
    if (d_struct == NULL || d_struct->matrix == NULL || d_struct->matrix->cells == NULL ||
            pd_path == NULL || pd_path->vertices == NULL) {
        return 0;
    }
    fprintf(stdout, "dijkstra_update_path_from_cell: Passed Sanity checks with %d!\n", cell_index);

    for (int v = 0; v < d_struct->cell_length; v++) {
        if (d_struct->matrix->cells[cell_index][v]->position == __INFINITY
                || (*pd_path->vertices)[v].is_visited) {
            continue;
        }

        // update the distances with the lesser distance from the root node, aka. the one referred to from the "cell_index"
        if (d_struct->matrix->cells[cell_index][v]->position + (*pd_path->vertices)[cell_index].position
                < (*pd_path->vertices)[v].position) {

            (*pd_path->vertices)[v].position =
                    d_struct->matrix->cells[cell_index][v]->position + (*pd_path->vertices)[cell_index].position;

            if (d_struct->processors != NULL && d_struct->processors->update_path_processor != NULL) {
                d_struct->processors->update_path_processor(d_struct);
            }
        }
    }
    return 0;
}


uint8_t dijkstra_start(dijkstra_structure *d_struct, int start, int end, path *out) {
    if (d_struct == NULL || d_struct->matrix == NULL ||
        d_struct->matrix->cells == NULL || out == NULL || out->vertices == NULL) {
        return 1;
    }
    fprintf(stdout, "dijkstra_start: Passed Sanity checks!\n");
    // initialize a position-dependent path
    vertex *vertexes = calloc(d_struct->cell_length, sizeof (vertex));

    path *pd_path = calloc(1, sizeof (path));
    pd_path->vertices = &vertexes;
    pd_path->cell_length = d_struct->cell_length;

    d_struct->pd_path = pd_path;
    fprintf(stdout, "dijkstra_start: Passed Allocation of pd-path!\n");
    if (pd_path->vertices == NULL) {
        perror("Error allocating the position-dependent list!");
        return 1;
    }
    dijkstra_init(d_struct, pd_path, start);
    //     loop as long as the end vertex is not reached and the cell vertices are still available
    //     loop V times, the number of vertices
    for (int v = 0; v < d_struct->cell_length; v++) {
        fprintf(stdout, "dijkstra_start: Processing updates!\n");
        int cell_index = dijkstra_get_lesser(d_struct, pd_path, __INFINITY, out);
        fprintf(stdout, "dijkstra_start: Selected Index %d\n", cell_index);
        if (cell_index == end) {
            fprintf(stdout, "dijkstra_start: Reached the destination!\n");
            break;
        }
        dijkstra_update_path_from_cell(d_struct, cell_index, pd_path);
    }
    return 0;
}

uint8_t dijkstra_destroy(dijkstra_structure *d_struct) {
    if (d_struct == NULL || d_struct->pd_path == NULL || *(d_struct->pd_path->vertices) == NULL) {
        return 1;
    }

    if (d_struct->processors != NULL && d_struct->processors->dijkstra_destroy_processor != NULL) {
        d_struct->processors->dijkstra_destroy_processor(d_struct);
    }

    free(*(d_struct->pd_path->vertices));
    free(d_struct->pd_path);

    return 0;
}