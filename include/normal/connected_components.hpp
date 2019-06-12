#ifndef MINI_GRAPH_NORNAL_CONNECTED_COMPONENTS_INC
#define MINI_GRAPH_NORNAL_CONNECTED_COMPONENTS_INC

#include <vector>

namespace MiniGraph {

namespace normal {

template <class Graph> 
class ConnectedComponents { 
protected:
    const Graph &graph_;
    int cCnt_ = 0;
    std::vector<int> ccNum_; 

    virtual void previsit(int v) {}

    virtual void visit(int v) { ccNum_[v] = cCnt_; }

    virtual void postvisit(int v) {}

    virtual bool isVisited(int v) { return ccNum_[v] >= 0; }

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
    ConnectedComponents(const Graph &graph): graph_(graph), cCnt_(0), ccNum_(graph.vertexCount(), -1) {}

    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!isVisited(v)) {
                explore(v);
                cCnt_++;
            }
    }

public:
    int count() const { return cCnt_; }

    int getCCNumber(int v) const { return ccNum_[v]; }

    bool isConnect(int s, int t) const 
    { return ccNum_[s] == ccNum_[t]; }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
