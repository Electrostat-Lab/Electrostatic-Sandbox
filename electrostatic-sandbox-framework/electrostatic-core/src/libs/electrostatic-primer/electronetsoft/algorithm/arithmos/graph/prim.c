#include <electrostatic/electronetsoft/algorithm/arithmos/graph/prim.h>

static inline int prim_init(prim_structure *p_struct, int start) {
  if (p_struct == NULL || p_struct->matrix == NULL || p_struct->pd_path == NULL ||
          p_struct->pd_path->edges == NULL) {
    fprintf(stdout, "prim_init: Not Passed Sanity checks!\n");
    return -1;
  }
  fprintf(stdout, "prim_init: Passed Sanity checks!\n");
  fprintf(stdout, "prim_init: First item %p\n",
          p_struct->matrix->cells[start][1]);
  for (int i = 0; i < p_struct->cell_length; i++) {
    // deep copy the relations with the first vertex!
    // leave the nullary edges uninitialized!
    if (p_struct->matrix->cells[start][i] != NULL) {
        p_struct->pd_path->edges[i] = p_struct->matrix->cells[start][i];
    }
    if (p_struct->processors != NULL &&
        p_struct->processors->initializing_vertices_processor != NULL) {
      p_struct->processors->initializing_vertices_processor(p_struct);
    }
    fprintf(stdout, "prim_init: Processing for initialization!\n");
  }
  return 0;
}

static inline int prim_get_lesser(prim_structure *p_struct, int base_position, edge_path *out) {
  if (p_struct == NULL || p_struct->matrix == NULL || p_struct->pd_path == NULL ||
          p_struct->pd_path->edges == NULL) {
    return -1;
  }
  int lesser_position = base_position;
  int edge_index = -1;
  fprintf(stdout, "prim_get_lesser: Passed Sanity checks!\n");

  for (int e = 0; e < p_struct->cell_length; e++) {
    // skip the traversed edge
    if (p_struct->pd_path->edges[e] == NULL || p_struct->pd_path->edges[e]->is_traversed) {
      continue;
    }
    fprintf(stdout, "prim_get_lesser: Processing: %s\n",
            (const char *)p_struct->pd_path->edges[e]->metadata);

    if (p_struct->pd_path->edges[e]->length < lesser_position) {
      lesser_position = p_struct->pd_path->edges[e]->length;
      edge_index = e;
      if (p_struct->processors != NULL &&
          p_struct->processors->lesser_vertex_retrieval_processor != NULL) {
        p_struct->processors->lesser_vertex_retrieval_processor(p_struct, out, e);
      }
    }
    fprintf(stdout, "prim_get_lesser: Processing lesser distance algorithm!\n");
  }
  if (edge_index != -1) {
      p_struct->pd_path->edges[edge_index]->is_traversed = 1;
    out->edges[out->count] = p_struct->pd_path->edges[edge_index];
    out->count += 1;
    if (p_struct->processors != NULL &&
        p_struct->processors->on_lesser_vertex_found != NULL) {
      p_struct->processors->on_lesser_vertex_found(p_struct, out);
    }
    fprintf(stdout, "prim_get_lesser: Lesser path found!\n");
  }
  return edge_index;
}

// erroneous
static inline uint8_t prim_update_path_from_edge(prim_structure *p_struct,
                                                 int edge_index) {
  if (p_struct == NULL || p_struct->matrix == NULL ||
      p_struct->matrix->cells == NULL || p_struct->pd_path == NULL ||
      p_struct->pd_path->edges == NULL) {
    return 0;
  }
  fprintf(stdout, "prim_update_path_from_edge: Passed Sanity checks with %d!\n",
          edge_index);

  for (int v = 0; v < p_struct->matrix->cell_length; v++) {
    if (p_struct->matrix->cells[edge_index][v] == NULL) {
      continue;
    }

    // update the position-dependent list if the old edge was not reachable, but
    // now available! OR if it was available, but now available with a lesser
    // distance
    if (p_struct->pd_path->edges[v] == NULL ||
        (!p_struct->pd_path->edges[v]->is_traversed &&
            p_struct->matrix->cells[edge_index][v]->length < p_struct->pd_path->edges[v]->length)) {
        p_struct->pd_path->edges[v] = p_struct->matrix->cells[edge_index][v];
      if (p_struct->processors != NULL &&
          p_struct->processors->update_path_processor != NULL) {
        p_struct->processors->update_path_processor(p_struct);
      }
      fprintf(stdout, "prim_update_path_from_edge: Updated paths!\n");
    }
  }
  return 0;
}

static inline void graph_edge_print(edge_path *path, edge *p_edge, int index) {
    if (p_edge == NULL) {
        return;
    }
    fprintf(stdout, "PD List element = (%d, %s, %d, is_traversed: %d)\n", index,
                (const char *) p_edge->metadata, p_edge->length, p_edge->is_traversed);
}

uint8_t prim_start(prim_structure *p_struct, int start, int end,
                   edge_path *out) {
  if (p_struct == NULL || out == NULL) {
      return 1;
  }
  p_struct->pd_path = calloc(1, sizeof (edge_path));
  p_struct->pd_path->edges = calloc(p_struct->cell_length, sizeof(edge *));
  p_struct->pd_path->count = p_struct->cell_length;

  prim_init(p_struct, start);
  for (int v = 0; v < p_struct->matrix->cell_length; v++) {
    int edge_index = prim_get_lesser(p_struct, __INFINITY, out);
    if (edge_index == end) {
      break;
    }
    prim_update_path_from_edge(p_struct, edge_index);
  }
  return 0;
}

uint8_t prim_destroy(prim_structure *p_struct) {
  if (p_struct == NULL || p_struct->pd_path == NULL) {
    return 1;
  }

  if (p_struct->processors != NULL &&
      p_struct->processors->prim_destroy_processor != NULL) {
    p_struct->processors->prim_destroy_processor(p_struct);
  }

  free(p_struct->pd_path->edges);
  p_struct->pd_path->edges = NULL;

  free(p_struct->pd_path);
  p_struct->pd_path = NULL;
  return 0;
}
