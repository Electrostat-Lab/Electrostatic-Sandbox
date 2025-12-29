#include <stdio.h>
#include <electronetsoft/arithmos/graph/dijkstra.h>

static inline void dijkstra_init(dijkstra_structure *d_struct) {

}

static inline void dijkstra_vertex_found(dijkstra_structure *d_struct, path *out) {

}

static inline void dijkstra_processing_lesser_vertices(dijkstra_structure *d_struct, path *out) {

}

static inline void dijkstra_update_processor(dijkstra_structure *d_struct) {

}

int main() {

    const char *vertex_0 = "Vertex 0";
    const char *vertex_1 = "Vertex 1";
    const char *vertex_2 = "Vertex 2";
    const char *vertex_3 = "Vertex 3";
    const char *vertex_4 = "Vertex 4";

    int cell_length = 5;

    dijkstra_processors d_processors = {
         .initializing_vertices_processor = &dijkstra_init,
         .on_lesser_vertex_found = &dijkstra_vertex_found,
         .lesser_vertex_retrieval_processor = &dijkstra_processing_lesser_vertices,
         .update_path_processor = &dijkstra_update_processor
    };

    // allocators
    vertex ***cells = calloc(cell_length, sizeof(vertex *));
    path output = {
        .vertices = calloc(cell_length, sizeof(vertex *)),
        .cell_length = 0
    };

    // data filling for vertex 0
    vertex v00 = {.data = (void *) vertex_0, .position = __INFINITY};
    vertex v01 = {.data = (void *) vertex_0, .position = 100};
    vertex v02 = {.data = (void *) vertex_0, .position = __INFINITY};
    vertex v03 = {.data = (void *) vertex_0, .position = 10};
    vertex v04 = {.data = (void *) vertex_0, .position = __INFINITY};
    cells[0] = calloc(cell_length, sizeof (vertex *));
    cells[0][0] = &v00;
    cells[0][1] = &v01;
    cells[0][2] = &v02;
    cells[0][3] = &v03;
    cells[0][4] = &v04;

    vertex v10 = {.data = (void *) vertex_1, .position = 100};
    vertex v11 = {.data = (void *) vertex_1, .position = __INFINITY};
    vertex v12 = {.data = (void *) vertex_1, .position = 20};
    vertex v13 = {.data = (void *) vertex_1, .position = __INFINITY};
    vertex v14 = {.data = (void *) vertex_1, .position = __INFINITY};
    cells[1] = calloc(cell_length, sizeof (vertex *));
    cells[1][0] = &v10;
    cells[1][1] = &v11;
    cells[1][2] = &v12;
    cells[1][3] = &v13;
    cells[1][4] = &v14;

    vertex v20 = {.data = (void *) vertex_2, .position = __INFINITY};
    vertex v21 = {.data = (void *) vertex_2, .position = 20};
    vertex v22 = {.data = (void *) vertex_2, .position = __INFINITY};
    vertex v23 = {.data = (void *) vertex_2, .position = __INFINITY};
    vertex v24 = {.data = (void *) vertex_2, .position = 50};
    cells[2] = calloc(cell_length, sizeof (vertex *));
    cells[2][0] = &v20;
    cells[2][1] = &v21;
    cells[2][2] = &v22;
    cells[2][3] = &v23;
    cells[2][4] = &v24;

    vertex v30 = {.data = (void *) vertex_3, .position = 10};
    vertex v31 = {.data = (void *) vertex_3, .position = __INFINITY};
    vertex v32 = {.data = (void *) vertex_3, .position = __INFINITY};
    vertex v33 = {.data = (void *) vertex_3, .position = __INFINITY};
    vertex v34 = {.data = (void *) vertex_3, .position = 300};
    cells[3] = calloc(cell_length, sizeof (vertex *));
    cells[3][0] = &v30;
    cells[3][1] = &v31;
    cells[3][2] = &v32;
    cells[3][3] = &v33;
    cells[3][4] = &v34;

    vertex v40 = {.data = (void *) vertex_4, .position = __INFINITY};
    vertex v41 = {.data = (void *) vertex_4, .position = __INFINITY};
    vertex v42 = {.data = (void *) vertex_4, .position = 50};
    vertex v43 = {.data = (void *) vertex_4, .position = 300};
    vertex v44 = {.data = (void *) vertex_4, .position = __INFINITY};
    cells[4] = calloc(cell_length, sizeof (vertex *));
    cells[4][0] = &v40;
    cells[4][1] = &v41;
    cells[4][2] = &v42;
    cells[4][3] = &v43;
    cells[4][4] = &v44;

    cellular_matrix matrix = {
        .cells = cells
    };

    dijkstra_structure d_struct = {
        .matrix = &matrix,
        .processors = &d_processors,
        .cell_length = cell_length
    };

    dijkstra_start(&d_struct, 0, 4, &output);

    for (int i = 0; i < output.cell_length; i++) {
        fprintf(stdout, "%s\n", (const char *) output.vertices[i]->data);
    }

    dijkstra_destroy(&d_struct);

    for (int i = 0; i < cell_length; i++) {
        free(cells[i]);
    }

    free(cells);
    free(output.vertices);

    return 0;
}
