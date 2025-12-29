#ifndef __CALLER_GRAPH_API_H_
#define __CALLER_GRAPH_API_H_

#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct caller_graph {
    char *api;
    void *func;
    void *return_value;
    void **params;
    caller_graph *root;
};

#ifdef __cplusplus
};
#endif

#endif