#ifndef MINI_GRAPH_NORMAL_DIGRAPH_DFS_INC
#define MINI_GRAPH_NORMAL_DIGRAPH_DFS_INC

#include <limits>
#include <vector>
#include <string>
#include "dfs.hpp"

namespace MiniGraph {

namespace normal {

template <class Graph> 
class DigraphDFS: public DFS<Graph> {
protected:
    int clock_ = 0;
    std::vector<int> pre_;  // previsit clock
    std::vector<int> post_; // postvisit clock

    void previsit(int v) override
    {
        pre_[v] = clock_;
        clock_++;
    }

    void postvisit(int v) override
    {
        post_[v] = clock_;
        clock_++;
    }

public:
    DigraphDFS(const Graph &graph): DFS<Graph>(graph), 
        pre_(graph.vertexCount(), std::numeric_limits<int>::max()),
        post_(graph.vertexCount(), std::numeric_limits<int>::max())
    {}

    std::string getEdgeType(int u, int v) const
    {
        // 树边或前向边
        // [   [     ]    ]
        // u   v     v    u
        if (pre_[u] < pre_[v] && post_[v] < post_[u]) {
            return "tree|down(树边|前向边)";
        }

        // 回边
        // [   [     ]    ]
        // v   u     u    v
        if (pre_[v] < pre_[u] && post_[u] < post_[v]) {
            return "back(回边)";
        }

        // 横跨边
        // [   ]     [    ]
        // u   u     v    v
        // v   v     u    u
        if (post_[u] < pre_[v] || post_[v] < pre_[u]) {
            return "cross(横跨边)";
        }

        return "impossible(不可能的情况)";
    }

    int getPreOrder(int v) { return pre_[v]; }
    int getPostOrder(int v) { return post_[v]; }
};

}   // namespace normal

}	// namespace MiniGraph

#endif

