#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

void destroy_graph(struct graph *g){
    if(g->adjm) free(g->adjm);
}

int read_graph(struct graph *g){
    int size;
    scanf("%d", &size);
    g->size = (size_t)size;
    g->adjm = calloc(g->size * g->size, sizeof(node_t));
    unsigned int line = 0;
    while(true){
        line++;
        node_t src, dest;
        int ret = scanf("%d %d", &src, &dest);
        if(!ret && errno){
            fprintf(stderr, "read_graph: error parsing edge %d: %s\n", line, strerror(errno));
            return 1;
        }else if(ret == EOF){
            fprintf(stderr, "read_graph: unexpected EOF occured at line %d\n", line);
            return 2;
        }else if(src == -1 && dest == -1){
            break;
        }else if(src < 0 || src >= g->size){
            fprintf(stderr, "read_graph: src node (%d) out of range [0,%zd)\n", src, g->size);
            return 3;
        }else if(dest < 0 || dest >= g->size){
            fprintf(stderr, "read_graph: dest node (%d) out of range [0,%zd)\n", dest, g->size);
            return 3;
        }else{
            g->adjm[src*size + dest] = 1;
        }
    }

    return 0;
}
