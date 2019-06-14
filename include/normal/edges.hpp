#ifndef MINI_GRAPH_NORMAL_EDGES_INC
#define MINI_GRAPH_NORMAL_EDGES_INC

#include <vector>
#include "edge.hpp"

namespace MiniGraph {

namespace normal {

template <class Graph>
std::vector<Edge> edges(Graph &graph)
{
    std::vector<Edge> vec;
    for (int v = 0; v < graph.vertexCount(); v++) {
        for (auto w: graph.getAdjIterator(v)) {
            if (graph.isDirected() || v < w) {
                vec.push_back(Edge(v, w));
            }
        }
    }

    return std::move(vec);
}

}   // namespace normal

}	// namespace MiniGraph

#endif
