#include "dsp.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define UNSEEN -1

void dsp_rec(struct graph *g, int *seen, int nseen, int *soln, int soln_size, node_t nd);
int see(struct graph *g, node_t nd, int *seen);
void unsee(struct graph *g, node_t nd, int *seen);

int *best_soln; // static array used by dsp_solve to store the best known soln
int best_size; // size (i.e., # of chosen vertices) of best_size

int *dsp_solve(struct graph *g){
    // 0 for unchosen, 1 for chosen
    int *soln = calloc(g->size, sizeof(int));

    // populate best solution with trivial solution, i.e., all vertices
    best_soln = calloc(g->size, sizeof(int));
    for(int i = 0; i < g->size; i++) best_soln[i] = 1;
    best_size = g->size;

    // -1 for unseen, k for "seen first by vertex k"
    int *seen = calloc(g->size, sizeof(int));
    for(int i = 0; i < g->size; i++) seen[i] = UNSEEN;
    dsp_rec(g, seen, 0, soln, 0, 0);

    free(soln);
    free(seen);

    return best_soln;
}


// recursive helper function for dsp_solve. Searches solutions whose first nd
// vertex choices are given by soln, mutating best_soln and best_size with the
// best such solution if a better one is found.
//
// g:           the input graph
// seen:        seen[i] is -1 if vertex i is unseen, v if it was first seen by vertex v
// nseen:       number of seen (i.e., entries that aren't -1) entries in seen
// soln:        the currently built solution
// soln_size:   the number of vertices selected by soln
// nd:          the vertex being considered (i.e., branched on)
void dsp_rec(struct graph *g, int *seen, int nseen, int *soln, int soln_size, node_t nd){
    assert(nseen <= g->size);

    if(soln_size >= best_size){ // impossible to find a better solution
        return;
    }else if(nseen == g->size){ // feasible solution found; better than best_soln
        printf("better soln found; nseen=%d, soln_size=%d, nd=%d\n", nseen, soln_size, nd);
        for(int i = 0; i < g->size; i++) best_soln[i] = soln[i];
        best_size = soln_size;
    }else if(nd < g->size){
        if(seen[nd] == UNSEEN){
            soln[nd] = 1;
            int new_seen = see(g, nd, seen);

            // branch where vertex nd is selected
            dsp_rec(g, seen, nseen+new_seen, soln, soln_size+1, nd+1);
            unsee(g, nd, seen);
        }

        soln[nd] = 0;

        // branch where vertex nd is not selected
        dsp_rec(g, seen, nseen, soln, soln_size, nd+1);
    }
}

// returns number of new nodes seen
int see(struct graph *g, node_t nd, int *seen){
    int new_seen = 1; // 1 for nd
    seen[nd] = nd;
    for(int i = 0; i < g->size; i++){
        if(g->adjm[nd*g->size + i] && seen[i] == UNSEEN){
            seen[i] = nd;
            new_seen++;
        }
    }

    return new_seen;
}

void unsee(struct graph *g, node_t nd, int *seen){
    for(int i = 0; i < g->size; i++){
        if(seen[i] == nd) seen[i] = UNSEEN;
    }
}


int degree_cmp(const void *u, const void *v, void *degrees){
    return -((int *)degrees)[*(int *)u] + ((int *)degrees)[*(int *)v];
}

node_t *degree_sort(struct graph *g){
    node_t *vtcs = calloc(g->size, sizeof(node_t));
    int *degrees = calloc(g->size, sizeof(int));
    for(int i = 0; i < g->size; i++){
        vtcs[i] = i;
        for(int j = 0; j < g->size; j++){
            if(g->adjm[i*g->size + j]) degrees[i]++;
        }
    }

    qsort_r(vtcs, g->size, sizeof(node_t), degree_cmp, degrees);

    // TODO: figure out how to do this in-place
    int *new_adjm = calloc(g->size * g->size, sizeof(int));
    for(int i = 0; i < g->size; i++){
        for(int j = 0; j < g->size; j++){
            new_adjm[i*g->size + j] = g->adjm[vtcs[i]*g->size + vtcs[j]];
        }
    }
    memcpy(g->adjm, new_adjm, g->size * g->size * sizeof(int));

    free(degrees);
    free(new_adjm);

    return vtcs;
}
