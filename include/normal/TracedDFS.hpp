#ifndef MINI_GRAPH_NORMAL_TRACE_DFS_INC
#define MINI_GRAPH_NORMAL_TRACE_DFS_INC

#include <vector>

namespace MiniGraph {

namespace normal {

template <class Graph> 
class TracedDFS {
protected:
    const Graph &graph_;
    std::vector<bool> visited_;
    std::vector<int> parent_;

    virtual void previsit(int v) {}

    virtual void visit(int v, int p)
    {
        visited_[v] = true; 
        parent_[v] = p;
    }

    virtual void postvisit(int v) {}

    virtual bool isVisited(int v) { return visited_[v]; }

    virtual void explore(int v, int p) // p: parent vertex
    {
        previsit(v);
        visit(v, p);
        for (auto w: graph_.getAdjIterator(v)) {
            if (!isVisited(w))
                explore(w, v);
        }
        postvisit(v);
    }

public:
    TracedDFS(const Graph &graph): graph_(graph), 
        visited_(graph.vertexCount(), false),
        parent_(graph.vertexCount(), -1) 
    {}

    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!isVisited(v))
                explore(v, v);
    }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
