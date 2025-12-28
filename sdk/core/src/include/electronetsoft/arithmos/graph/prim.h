#ifndef __PRIMS_ALGORITHM__
#define __PRIMS_ALGORITHM__

#include <electronetsoft/arithmos/graph/math_structs.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct prim_processors (prim_processors);
typedef struct prim_structure (prim_structure);

struct prim_processors {
    void (*initializing_vertices_processor)(prim_structure *);
    void (*on_lesser_vertex_found)(prim_structure *, edge_path *);
    void (*lesser_vertex_retrieval_processor)(prim_structure *, edge_path *, int);
    void (*update_path_processor)(prim_structure *);
    void (*prim_destroy_processor)(prim_structure *);
};

struct prim_structure {
    edge_matrix *matrix;
    prim_processors *processors;
    edge_path *pd_path;
    int cell_length;
};

uint8_t prim_start(prim_structure *p_struct, int start, int end, edge_path *out);
uint8_t prim_destroy(prim_structure *p_struct);

#ifdef __cplusplus
};
#endif

#endif