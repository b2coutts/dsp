#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
#include <stddef.h>

typedef int node_t;

struct graph {
    size_t size; // number of nodes
    int *adjm; // adjm[i*size + j] is 1 if (i,j) is an edge, 0 otherwise
};

// destroys a graph struct
void destroy_graph(struct graph *g);

// reads a graph from stdin. Line 1 should be an integer n representing the
// number of nodes. The next several lines will be of the form "a b", where a,b
// are integers with 0 <= a,b < n representing an edge in the graph, followed
// by the line "-1 -1"
//
// Returns codes:
//   0 -> success
//   1 -> parse error
//   2 -> unexpected EOF
//   3 -> endpoint of edge out of range
// TODO: maybe take a filename or a filehandle or something
int read_graph(struct graph *g);

#endif
