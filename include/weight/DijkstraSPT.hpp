#ifndef MINI_GRAPH_WEIGHT_DIJKSTRA_SPT_INC
#define MINI_GRAPH_WEIGHT_DIJKSTRA_SPT_INC

#include <vector>
#include "Edge.hpp"
#include "RefPriorityQueue.hpp"

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
        RefPriorityQueue<double> pQ(dist_);
        for (int v = 0; v < graph_.vertexCount(); v++) 
            pQ.insert(v);

        dist_[s] = 0.0; 
        pQ.lower(s);  

        while (!pQ.isEmpty()) 
        { 
            int v = pQ.deleteMin();
            if (v != s && tree_[v] == nullptr) 
                return;  

            for (auto e: graph_.getAdjIterator(v)) { 
                int w = e->other(v); 
                if ((dist_[v] + e->weight()) < dist_[w]) { 
                    dist_[w] = dist_[v] + e->weight(); 
                    pQ.lower(w); 
                    tree_[w] = e; 
                }
            }
        }
    }

    Edge *tree(int v) const { return tree_[v]; }
    double dist(int v) const { return dist_[v]; }

    std::vector<Edge *> path(int v) const 
    {
		if (v == s_)
			return std::vector<Edge *>();

        std::vector<Edge *> edges;
        Edge *edge = tree(v);
        edges.push_back(edge);

        while ((v = edge->other(v)) != s_) {
            edge = tree(v);
            edges.push_back(edge); 
        }

        std::reverse(edges.begin(), edges.end());

        return edges;
    }
};

}	// namespace weight

}	// namespace MiniGraph

#endif
