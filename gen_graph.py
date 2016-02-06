#!/usr/bin/env python2
import networkx as nx
from openopt import DSP

def mkgraph(n, avg_deg):
    G = nx.fast_gnp_random_graph(n, 1.0*avg_deg/n)
    with open(('deg%s_n%s.graph' % (avg_deg, n)),  'w') as f:
        f.write('%s\n' % n)
        for u in G.nodes():
            for v in G[u]:
                f.write('%s %s\n' % (u,v))
        f.write('-1 -1\n')

    p = DSP(G)
    r = p.solve('glpk', iprint=0)
    print(r.ff, r.solution)
    return (G, p, r)
