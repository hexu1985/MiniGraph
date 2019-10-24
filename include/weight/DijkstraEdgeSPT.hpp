#ifndef MINI_GRAPH_WEIGHT_DIJKSTRA_EDGE_SPT_INC
#define MINI_GRAPH_WEIGHT_DIJKSTRA_EDGE_SPT_INC

#include <vector>
#include "Edge.hpp"
#include "PriorityQueueRef.hpp"

namespace mini_graph {

namespace weight {

template <class Graph> 
class DijkstraEdgeSPT { 
private:
    const Graph &graph_;
    std::vector<double> dist_;  // 源点s到各个顶点的距离
    std::vector<Edge *> tree_;

public:
    DijkstraEdgeSPT(const Graph &graph, int s): 
        graph_(graph), 
        dist_(graph.vertexCount(), Edge::infinity()),
        tree_(graph.vertexCount(), nullptr)
    {
        PriorityQueueRef<double, std::greater<double>> pQ(dist_);   // 距离越小优先级越高
        for (int v = 0; v < graph_.vertexCount(); v++) 
            pQ.push(v);

        dist_[s] = 0.0; 
        pQ.update(s);  

        while (!pQ.isEmpty()) 
        { 
            int v = pQ.pop();       // 获取最小距离的顶点索引
            if (dist_[v] == Edge::infinity())   // 不可达顶点
                return;

            for (auto e: graph_.getAdjIterator(v)) { 
                int w = e->other(v); 
                if ((dist_[v] + e->weight()) < dist_[w]) { 
                    dist_[w] = dist_[v] + e->weight(); 
                    pQ.update(w);       // 更新到各个顶点的距离
                    tree_[w] = e; 
                }
            }
        }
    }

    Edge *tree(int v) const { return tree_[v]; }
    double dist(int v) const { return dist_[v]; }

    std::vector<int> path(int v) const 
    {
        if (dist_[v] == Edge::infinity())    // 顶点不可达或源点
            return std::vector<int>();

        std::vector<int> p;
        Edge *e = tree_[v];
        while (e != nullptr) {
            v = e->other(v);
            p.push_back(v);
            e = tree_[v];
        }

        std::reverse(p.begin(), p.end());

        return p;
    }
};

}	// namespace weight

}	// namespace mini_graph

#endif
