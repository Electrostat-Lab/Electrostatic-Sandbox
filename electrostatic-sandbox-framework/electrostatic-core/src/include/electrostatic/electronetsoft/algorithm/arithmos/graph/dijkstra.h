#ifndef __DIJKSTRA_ALGO__
#define __DIJKSTRA_ALGO__

#include <electrostatic/electronetsoft/algorithm/arithmos/graph/math_structs.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dijkstra_processors (dijkstra_processors);
typedef struct dijkstra_structure (dijkstra_structure);

struct dijkstra_processors {
    void (*initializing_vertices_processor)(dijkstra_structure *);

    void (*on_lesser_vertex_found)(dijkstra_structure *, path *);

    void (*lesser_vertex_retrieval_processor)(dijkstra_structure *, path *);

    void (*update_path_processor)(dijkstra_structure *);

    void (*dijkstra_destroy_processor)(dijkstra_structure *);
};

struct dijkstra_structure {
    cellular_matrix *matrix;
    dijkstra_processors *processors;
    path *pd_path;
    int cell_length;
};

/**
 * Starts the Dijkstra's shortest path finding algorithm between the [start]
 * vertex and the [end] vertex, saving the result in a path mathematical structure.
 *
 * @param d_struct the dijkstra-structure contains the input cellular matrix that is a
 *                 mathematical structure representing a graph
 *                 by storing weights for each vertex with respect to other vertices.
 * @param start the index of the start vertex.
 * @param end the index of the stop vertex.
 * @param out the output shortest path.
 * @return (1) for failure, or (0) otherwise.
 */
uint8_t dijkstra_start(dijkstra_structure *d_struct, int start, int end, path *out);

/**
 * Destroys the dynamically heap-allocated buffers referenced from the d-struct
 * memory addresses.
 *
 * @param d_struct the dijkstra-structure
 * @return (1) for failure, or (0) otherwise.
 */
uint8_t dijkstra_destroy(dijkstra_structure *d_struct);

#ifdef __cplusplus
};
#endif

#endif