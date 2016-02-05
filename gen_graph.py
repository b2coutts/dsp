#!/usr/bin/env python2
import networkx as nx

avg_deg = 7.0
n = 50

G = nx.fast_gnp_random_graph(n, 1.0*avg_deg/n)
with open(('deg%s_n%s.graph' % (avg_deg, n)), 'w') as f:
    f.write('%s\n' % n)
    for u in G.nodes():
        for v in G[u]:
            f.write('%s %s\n' % (u,v))
    f.write('-1 -1\n')
