#include "graph.h"
#include "dsp.h"
#include <stdio.h>
#include <assert.h>

int main(){
    struct graph g;
    printf("Reading graph from stdin...\n");
    int ret = read_graph(&g);
    assert(!ret);
    printf("Finished reading graph (%zd vertices)\n", g.size);

    printf("Computing DSP...\n");
    int *soln = dsp_solve(&g);

    printf("Finished computing DSP. Solution:\n");
    for(int i = 0; i < g.size; i++){
        if(soln[i]) printf("%d\n", i);
    }
}
