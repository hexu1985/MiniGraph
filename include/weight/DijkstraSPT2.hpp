#ifndef MINI_GRAPH_WEIGHT_DIJKSTRA_SPT2_INC
#define MINI_GRAPH_WEIGHT_DIJKSTRA_SPT2_INC

#include <vector>
#include "Edge.hpp"
#include "PriorityQueueRef.hpp"

namespace MiniGraph {

namespace weight {

template <class Graph> 
class DijkstraSPT2 { 
private:
    const Graph &graph_;
    std::vector<double> dist_;
    std::vector<int> prev_;

public:
    DijkstraSPT2(const Graph &graph, int s): 
        graph_(graph), 
        dist_(graph.vertexCount(), Edge::infinity()),
        prev_(graph.vertexCount(), -1)
    {
        PriorityQueueRef<double> pQ(dist_);
        for (int v = 0; v < graph_.vertexCount(); v++) 
            pQ.insert(v);

        dist_[s] = 0.0; 
        prev_[s] = s;
        pQ.decreaseKey(s);  

        while (!pQ.isEmpty()) 
        { 
            int v = pQ.deleteMin();
            for (auto e: graph_.getAdjIterator(v)) { 
                int w = e->other(v); 
                if ((dist_[v] + e->weight()) < dist_[w]) { 
                    dist_[w] = dist_[v] + e->weight(); 
                    pQ.decreaseKey(w); 
                    prev_[w] = v; 
                }
            }
        }
    }

    int prev(int v) const { return prev_[v]; }
    double dist(int v) const { return dist_[v]; }

    std::vector<int> path(int v) const 
    {
        std::vector<int> p;
        int u = prev(v);

        while (u != v) {
            p.push_back(u);
            v = u;
            u = prev(v);
        }

        std::reverse(p.begin(), p.end());

        return p;
    }
};

}	// namespace weight

}	// namespace MiniGraph

#endif
