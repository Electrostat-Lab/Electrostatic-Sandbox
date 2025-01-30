/**
 * @brief Displays a representation of a graph using edges and edge paths mathematical structures.
 * @author pavl_g
 */
#include <electrostatic/electronetsoft/algorithm/arithmos/graph/math_structs.h>
#include <alloca.h>
#include <stdio.h>

vertex v0 = {
    .data = (void *) "Vertex 0"
};

vertex v1 = {
    .data = (void *) "Vertex 1"
};

vertex v2 = {
    .data = (void *) "Vertex 2"
};

vertex v3 = {
    .data = (void *) "Vertex 3"
};

vertex v4 = {
    .data = (void *) "Vertex 4"
};

// Vertex (0) Relations
edge p_edge01 = {
    .initial = &v0,
    .terminal = &v1,
    .length = 100,
    .metadata = "E(0, 1)"
};

edge p_edge03 = {
    .initial = &v0,
    .terminal = &v3,
    .length = 10,
    .metadata = "E(0, 3)"
};
// .................

// Vertex (1) Relations
edge p_edge12 = {
    .initial = &v1,
    .terminal = &v0,
    .length = 100,
    .metadata = "E(1, 2)"
};
// .................
edge p_edge24 = {
    .initial = &v2,
    .terminal = &v4,
    .length = 50,
    .metadata = "E(2, 4)"
};
// .................
edge p_edge34 = {
    .initial = &v3,
    .terminal = &v4,
    .length = 300,
    .metadata = "E(3, 4)"
};
// .................

int main() {

    // Edges bouncing from Vertex 0
    // marking the unreachable edge paths as NULL
    edge **edges_0 = alloca(5 * sizeof(edge *));
    edges_0[0] = NULL;
    edges_0[1] = &p_edge01;
    edges_0[2] = NULL;
    edges_0[3] = &p_edge03;
    edges_0[4] = NULL;

    // Edges bouncing from Vertex 1
    // marking the unreachable edge paths as NULL
    edge **edges_1 = alloca(5 * sizeof(edge *));
    edges_1[0] = &p_edge01;
    edges_1[1] = NULL;
    edges_1[2] = &p_edge12;
    edges_1[3] = NULL;
    edges_1[4] = NULL;

    // Edges bouncing from Vertex 2
    // marking the unreachable edge paths as NULL
    edge **edges_2 = alloca(5 * sizeof(edge *));
    edges_2[0] = NULL;
    edges_2[1] = &p_edge12;
    edges_2[2] = NULL;
    edges_2[3] = NULL;
    edges_2[4] = &p_edge24;

    // Edges bouncing from Vertex 3
    // marking the unreachable edge paths as NULL
    edge **edges_3 = alloca(5 * sizeof(edge *));
    edges_3[0] = &p_edge03;
    edges_3[1] = NULL;
    edges_3[2] = NULL;
    edges_3[3] = NULL;
    edges_3[4] = &p_edge34;

    // Edges bouncing from Vertex 4
    // marking the unreachable edge paths as NULL
    edge **edges_4 = alloca(5 * sizeof(edge *));
    edges_4[0] = NULL;
    edges_4[1] = NULL;
    edges_4[2] = &p_edge24;
    edges_4[3] = &p_edge34;
    edges_4[4] = NULL;

    edge_matrix matrix = {
        .cells = alloca(5 * 5 * sizeof(edge *))
    };

    matrix.cells[0] = edges_0;
    matrix.cells[1] = edges_1;
    matrix.cells[2] = edges_2;
    matrix.cells[3] = edges_3;
    matrix.cells[4] = edges_4;

    fprintf(stdout, "Printing Graph Edges: \n");

    for (int c = 0; c < 5; c++) {
        edge **m_edge = matrix.cells[c];
        if (m_edge == NULL) {
            continue;
        }
        for (int e = 0; e < 5; e++) {
            if (m_edge[e] == NULL) {
                continue;
            }
            fprintf(stdout, "%s\n", (const char *) m_edge[e]->metadata);
        }
    }

    return 0;
}