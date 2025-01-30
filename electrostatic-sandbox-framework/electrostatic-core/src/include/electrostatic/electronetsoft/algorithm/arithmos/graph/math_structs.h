#ifndef __MATH_STRUCTS_
#define __MATH_STRUCTS_

#include <stddef.h>
#include <inttypes.h>

#define __INFINITY INT_MAX

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vertex (vertex);
typedef struct path (path);
typedef struct cellular_matrix (cellular_matrix);

// for edge-based implementation
typedef struct edge_matrix (edge_matrix);
typedef struct edge (edge);
typedef struct edge_path (edge_path);

typedef struct graph_processors (graph_processors);

struct graph_processors {
    void (*graph_vertices_cell_traversed)(cellular_matrix *, vertex **, int);
    void (*graph_cellular_vertex_traversed)(cellular_matrix *, vertex *, int);
    void (*graph_cell_traversed)(edge_matrix *, edge **, int);
    void (*graph_cellular_edge_traversed)(edge_matrix *, edge *, int);
    void (*graph_edge_path_traversed)(edge_path *path, edge *, int);
};

struct vertex {
    void *data;
    int position;
    int is_visited;
};

struct edge {
    vertex *initial;
    vertex *terminal;
    void *metadata;
    int length;
    int is_traversed;
    int position; /* represents the position of the edge from the start vertex */
                  /* ZERO if both are coincident; in this case the start vertex = the initial vertex */
};

struct edge_path {
    edge **edges;
    int count;
};

/**
 * @brief A mathematical structure representing a way to keep track of
 * the total distance (d) from a reference vertex (ρ).
 *
 * @note
 * <p>
 * The distance is stored in an integer block "position" on each vertex.
 * <p>
 * The "position" integer block indicates the distance from a reference vertex (ρ).
 */
struct path {
    vertex **vertices;
    void (*update)();
    int cell_length;
};

struct cellular_matrix {
    vertex ***cells;
};

struct edge_matrix {
    edge ***cells;
    int cell_length;
};

uint8_t graph_iterate_edge_matrix(edge_matrix *matrix, graph_processors *processors);
uint8_t graph_iterate_edge(edge_path *path, graph_processors *processors);
uint8_t graph_iterate_cellular_matrix(cellular_matrix *matrix, graph_processors *processors);
uint8_t graph_iterate_vertices(path *path, graph_processors *processors);

#ifdef __cplusplus
};
#endif

#endif