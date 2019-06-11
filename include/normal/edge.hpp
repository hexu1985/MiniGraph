#ifndef MINI_GRAPH_NORMAL_EDGE_INC
#define MINI_GRAPH_NORMAL_EDGE_INC

namespace MiniGraph {

namespace normal {

struct Edge {
	int u, v;
	Edge(int u = -1, int v = -1): u(u), v(v) { }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
