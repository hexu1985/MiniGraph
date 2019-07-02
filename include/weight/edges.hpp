#ifndef MINI_GRAPH_WEIGHT_EDGES_INC
#define MINI_GRAPH_WEIGHT_EDGES_INC

#include <vector>

namespace MiniGraph {

namespace weight {

template <class Graph, class Edge = typename Graph::EdgeType> 
std::vector<Edge *> edges(const Graph &graph)
{ 
    int E = 0;
    std::vector<Edge *> vec;
    for (int v = 0; v < graph.vertexCount(); v++) {
        for (auto e: graph.getAdjIterator(v)) {
            if (e->from(v))
                vec.push_back(e);
        }
    }
    return vec;
}

}   // namespace weight

}	// namespace MiniGraph

#endif
