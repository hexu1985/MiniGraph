#ifndef MINI_GRAPH_WEIGHT_PRIM_MST4_INC
#define MINI_GRAPH_WEIGHT_PRIM_MST4_INC

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
class PrimMST4 {
private:
    const Graph &graph_;
    std::vector<double> weight_;    // weight_[w]是从w到MST的最短边的权重
    std::vector<Edge *> from_;      // from_[w]是从w到MST的最短边
    std::vector<Edge *> tree_;      // MST中的边
    std::vector<bool> inTree_;      // inTree_[w]表示w是否在MST中
    std::vector<bool> isVisited_;   // isVisited_[w]表示w是否被访问

public:
    PrimMST4(const Graph &graph): graph_(graph), 
        weight_(graph.vertexCount(), Edge::infinity()),
        from_(graph.vertexCount(), nullptr),
        tree_(graph.vertexCount(), nullptr),
        inTree_(graph.vertexCount(), false),
        isVisited_(graph.vertexCount(), false)
    {
    }

    void pfs(int s)
    {
        RefPriorityQueue<double> pQ(weight_);
        pQ.insert(s);
        isVisited_[s] = true;
        while (!pQ.isEmpty()) {
            int v = pQ.deleteMin();
            tree_[v] = from_[v];
            inTree_[v] = true;
            for (auto e: graph_.getAdjIterator(v)) {
                int w = e->other(v);
                if (!isVisited_[w]) {
                    weight_[w] = e->weight();
                    pQ.insert(w);
                    from_[w] = e;
                    isVisited_[w] = true;
                } else if (!inTree_[w] && e->weight() < weight_[w]) {
                    weight_[w] = e->weight();
                    pQ.lower(w);
                    from_[w] = e;
                }
            }
        }
    }

    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (tree_[v] == nullptr)
                pfs(v);
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
