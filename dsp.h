#include "graph.h"

// computes the minimal dominating set for g (i.e., optimal solution to the
// Dominating Set Problem)
int *dsp_solve(struct graph *g);

// sorts the graph, reordering the vertices in descending order of degree.
// probably makes dsp_solve go faster. Returns an array mapping new indices to
// their old indices
node_t *degree_sort(struct graph *g);
