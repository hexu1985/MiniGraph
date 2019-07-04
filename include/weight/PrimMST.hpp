#ifndef MINI_GRAPH_WEIGHT_PRIM_MST_INC
#define MINI_GRAPH_WEIGHT_PRIM_MST_INC

#include <vector>
#include "Edge.hpp"

namespace MiniGraph {

namespace weight {

// Prim's Algorithm of Minimum Spanning Trees
// Prim算法: 最小生成树
template <class Graph>
class PrimMST {
private:
    const Graph &graph_;
    std::vector<double> cost_;  // cost_[w]是从w到MST的最短边的权重
    std::vector<Edge *> from_;  // from_[w]是从w到MST的最短边
    std::vector<Edge *> tree_;  // MST中的边

public:
    PrimMST(const Graph &graph): graph_(graph), 
        cost_(graph.vertexCount(), Edge::infinity()),
        from_(graph.vertexCount(), nullptr),
        tree_(graph.vertexCount(), nullptr)
    {
        int min = -1;
        for (int v = 0; min != 0; v = min) {
            min = 0;
            for (int w = 1; w < graph_.vertexCount(); w++) {
                if (tree_[w] == nullptr) {
                    auto e = graph_.edge(v, w);
                    if (e) {    // e != nullptr
                        if (e->weight() < cost_[w]) {
                            cost_[w] = e->weight();
                            from_[w] = e;
                        }
                    }
                    if (cost_[w] < cost_[min])
                        min = w;
                }
            }
            if (min)
                tree_[min] = from_[min];
        }
    }

    std::vector<Edge *> getTreeEdges()
    {
        std::vector<Edge *> edges;
        for (auto edge: tree_)
            if (edge)
                edges.push_back(edge);
        return std::move(edges);
    }
};

}	// namespace weight

}	// namespace MiniGraph

#endif
