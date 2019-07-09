#ifndef MINI_GRAPH_NORMAL_DIGRAPH_TS_INC
#define MINI_GRAPH_NORMAL_DIGRAPH_TS_INC

#include <vector>
#include "DFS.hpp"

namespace MiniGraph {

namespace normal {

/**
 * @brief topological sort of digraph
 *
 * @tparam Graph
 */
template <class Graph>
class DigraphTS: public DFS<Graph> {
private:
    int clock_ = 0;
    std::vector<int> post_;     // postvisit clock
    std::vector<int> postI_;    // reverse topological order

    void postvisit(int v) override
    {
        post_[v] = clock_;
        postI_[clock_] = v;
        clock_++;
    }

public:
    DigraphTS(const Graph &graph): DFS<Graph>(graph), 
        post_(graph.vertexCount()),
        postI_(graph.vertexCount())
    {
    }

    std::vector<int> sort()
    {
        if (clock_ == 0)
            this->search();
        return std::vector<int>(postI_.rbegin(), postI_.rend());
    }
};

}   // namespace normal

}	// namespace MiniGraph

#endif

