#ifndef MINI_GRAPH_WEIGHT_PRIM_MST3_INC
#define MINI_GRAPH_WEIGHT_PRIM_MST3_INC

#include <vector>
#include <unordered_set>
#include "Edge.hpp"
#include "RefPriorityQueue.hpp"

using namespace std;

namespace MiniGraph {

namespace weight {

// Prim's Algorithm of Minimum Spanning Trees
// Prim算法: 最小生成树
template <class Graph>
class PrimMST3 {
private:
    const Graph &graph_;
    std::vector<double> cost_;  // cost_[w]是从w到MST的最短边的权重
    std::vector<Edge *> from_;  // from_[w]是从w到MST的最短边
    std::vector<Edge *> tree_;  // MST中的边
    std::vector<Edge>   loop_;  // 自环

    void pfs(int s)
    {
        RefPriorityQueue<double> pQ(cost_);
        pQ.insert(s);
        while (!pQ.isEmpty()) {
            int v = pQ.deleteMin();
            tree_[v] = from_[v];
            for (auto e: graph_.getAdjIterator(v)) {
                int w = e->other(v);
                if (from_[w] == nullptr) {
                    cost_[w] = e->weight();
                    pQ.insert(w);
                    from_[w] = e;
                } else if (tree_[w] == nullptr && e->weight() < cost_[w]) {
                    cost_[w] = e->weight();
                    pQ.lower(w);
                    from_[w] = e;
                }
            }
        }
    }

public:
    PrimMST3(const Graph &graph): graph_(graph), 
        cost_(graph.vertexCount(), Edge::infinity()),
        from_(graph.vertexCount(), nullptr),
        tree_(graph.vertexCount(), nullptr)
    {
        for (int v = 0; v < graph_.vertexCount(); v++) {
            if (tree_[v] == nullptr) {
                loop_.push_back(Edge(v, v, 0));
                from_[v] = &loop_[loop_.size()-1];
                pfs(v);
            }
        }
    }

    std::vector<Edge *> getTreeEdges()
    {
        std::vector<Edge *> edges;
        for (auto edge: tree_)
            if (edge && edge->u() != edge->v())
                edges.push_back(edge);
        return std::move(edges);
    }
};

}	// namespace weight

}	// namespace MiniGraph

#endif
