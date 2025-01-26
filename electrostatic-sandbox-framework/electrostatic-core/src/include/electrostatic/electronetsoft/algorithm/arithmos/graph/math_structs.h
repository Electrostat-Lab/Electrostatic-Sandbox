#ifndef __MATH_STRUCTS_
#define __MATH_STRUCTS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vertex (vertex);
typedef struct path (path);
typedef struct cellular_matrix (cellular_matrix);

struct vertex {
    void *data;
    int position;
    int is_visited;
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

#ifdef __cplusplus
};
#endif

#endif