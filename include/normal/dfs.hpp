#ifndef MINI_GRAPH_NORMAL_DFS_INC
#define MINI_GRAPH_NORMAL_DFS_INC

#include <vector>

namespace MiniGraph {

namespace normal {

template <class Graph> 
class DFS {
protected:
    const Graph &graph_;
    std::vector<bool> visited_;

    virtual void previsit(int v) {}

    virtual void visit(int v) { visited_[v] = true; }

    virtual void postvisit(int v) {}

    virtual bool isVisited(int v) { return visited_[v]; }

    virtual void explore(int v)
    {
        previsit(v);
        visit(v);
        for (auto w: graph_.getAdjIterator(v)) {
            if (!isVisited(w))
                explore(w);
        }
        postvisit(v);
    }

public:
    DFS(const Graph &graph): graph_(graph), visited_(graph.vertexCount(), false) {}

    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!isVisited(v))
                explore(v);
    }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
