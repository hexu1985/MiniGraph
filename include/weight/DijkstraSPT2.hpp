#ifndef MINI_GRAPH_WEIGHT_DIJKSTRA_SPT2_INC
#define MINI_GRAPH_WEIGHT_DIJKSTRA_SPT2_INC

#include <vector>
#include "Edge.hpp"
#include "RefPriorityQueue.hpp"

namespace MiniGraph {

namespace weight {

template <class Graph> 
class DijkstraSPT2 { 
private:
    const Graph &graph_;
    std::vector<double> dist_;
    std::vector<Edge *> tree_;
    std::vector<Edge> loop_;

public:
    DijkstraSPT2(const Graph &graph, int s): 
        graph_(graph), 
        dist_(graph.vertexCount(), Edge::infinity()),
        tree_(graph.vertexCount(), nullptr)
    {
        RefPriorityQueue<double> pQ(dist_);
        for (int v = 0; v < graph_.vertexCount(); v++) 
            pQ.insert(v);

        dist_[s] = 0.0; 
        loop_.push_back(Edge(s, s, 0.0));
        tree_[s] = &loop_[loop_.size()-1];
        pQ.lower(s);  

        while (!pQ.isEmpty()) 
        { 
            int v = pQ.deleteMin();
            for (auto e: graph_.getAdjIterator(v)) { 
                int w = e->v(); 
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
        std::vector<Edge *> edges;
        Edge *edge = tree(v);

        while (edge->u() != edge->v()) {
            edges.push_back(edge);
            v = edge->other(v);
            edge = tree(v);
        }

        std::reverse(edges.begin(), edges.end());

        return std::move(edges);
    }
};

}	// namespace weight

}	// namespace MiniGraph

#endif
