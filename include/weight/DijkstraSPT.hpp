#ifndef MINI_GRAPH_WEIGHT_DIJKSTRA_SPT_INC
#define MINI_GRAPH_WEIGHT_DIJKSTRA_SPT_INC

#include <vector>
#include "Edge.hpp"
#include "PriorityQueueRef.hpp"

namespace MiniGraph {

namespace weight {

template <class Graph> 
class DijkstraSPT { 
private:
    const Graph &graph_;
    std::vector<double> dist_;
    std::vector<Edge *> tree_;
	int s_;

public:
    DijkstraSPT(const Graph &graph, int s): 
        graph_(graph), 
        dist_(graph.vertexCount(), Edge::infinity()),
        tree_(graph.vertexCount(), nullptr),
		s_(s)
    {
        PriorityQueueRef<double> pQ(dist_);
        for (int v = 0; v < graph_.vertexCount(); v++) 
            pQ.insert(v);

        dist_[s] = 0.0; 
        pQ.decreaseKey(s);  

        while (!pQ.isEmpty()) 
        { 
            int v = pQ.deleteMin();
            if (v != s && tree_[v] == nullptr) 
                return;  

            for (auto e: graph_.getAdjIterator(v)) { 
                int w = e->other(v); 
                if ((dist_[v] + e->weight()) < dist_[w]) { 
                    dist_[w] = dist_[v] + e->weight(); 
                    pQ.decreaseKey(w); 
                    tree_[w] = e; 
                }
            }
        }
    }

    Edge *tree(int v) const { return tree_[v]; }
    double dist(int v) const { return dist_[v]; }

    std::vector<int> path(int v) const 
    {
		if (v == s_)
			return std::vector<int>();

        std::vector<int> p;
        Edge *edge = tree(v);
        p.push_back(edge->other(v));

        while ((v = edge->other(v)) != s_) {
            edge = tree(v);
            p.push_back(edge->other(v)); 
        }

        std::reverse(p.begin(), p.end());

        return p;
    }
};

}	// namespace weight

}	// namespace MiniGraph

#endif
