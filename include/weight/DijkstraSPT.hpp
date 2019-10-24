#ifndef MINI_GRAPH_WEIGHT_DIJKSTRA_SPT_INC
#define MINI_GRAPH_WEIGHT_DIJKSTRA_SPT_INC

#include <vector>
#include "Edge.hpp"
#include "PriorityQueueRef.hpp"

namespace mini_graph {

namespace weight {

template <class Graph> 
class DijkstraSPT { 
private:
    const Graph &graph_;
    std::vector<double> dist_;  // 源点s到各个顶点的距离
    std::vector<int> prev_;

public:
    DijkstraSPT(const Graph &graph, int s): 
        graph_(graph), 
        dist_(graph.vertexCount(), Edge::infinity()),
        prev_(graph.vertexCount(), -1)
    {
        PriorityQueueRef<double, std::greater<double>> pQ(dist_);   // 距离越小优先级越高
        for (int v = 0; v < graph_.vertexCount(); v++) 
            pQ.push(v);

        dist_[s] = 0.0; 
        prev_[s] = s;
        pQ.update(s);  

        while (!pQ.isEmpty()) 
        { 
            int v = pQ.pop();   // 获取最小距离的顶点索引
            if (dist_[v] == Edge::infinity())   // 不可达顶点
                return;

            for (auto e: graph_.getAdjIterator(v)) { 
                int w = e->other(v); 
                if ((dist_[v] + e->weight()) < dist_[w]) { 
                    dist_[w] = dist_[v] + e->weight(); 
                    pQ.update(w);   // 更新到各个顶点的距离
                    prev_[w] = v; 
                }
            }
        }
    }

    int prev(int v) const { return prev_[v]; }
    double dist(int v) const { return dist_[v]; }

    std::vector<int> path(int v) const 
    {
        if (dist_[v] == Edge::infinity())    // 顶点不可达
            return std::vector<int>();

        int u = prev(v);
        std::vector<int> p;
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

}	// namespace mini_graph

#endif
