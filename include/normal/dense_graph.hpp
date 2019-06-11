#ifndef MINI_GRAPH_DENSE_GRAPH_INC
#define MINI_GRAPH_DENSE_GRAPH_INC

#include <vector>
#include "edge.hpp"

namespace MiniGraph {

namespace normal {

class DenseGraph { 
private:
	std::vector<std::vector<bool>> adjMatrix_;
	int vCnt_ = 0;
    int eCnt_ = 0; 
	bool directed_ = false;

public:
	DenseGraph(int V, bool directed = false) :
		adjMatrix_(V), vCnt_(V), eCnt_(0), directed_(directed)
	{ 
		for (int i = 0; i < V; i++) 
			adjMatrix_[i].assign(V, false);
	}

	int vertexCount() const { return vCnt_; }
	int edgeCount() const { return eCnt_; }
	bool isDirected() const { return directed_; }

	void insert(Edge e)
	{ 
		int u = e.u, v = e.v;
		if (adjMatrix_[u][v] == false) eCnt_++;
		adjMatrix_[u][v] = true;
		if (!directed_) adjMatrix_[v][u] = true; 
	} 

	void remove(Edge e)
	{ 
		int u = e.u, v = e.v;
		if (adjMatrix_[u][v] == true) eCnt_--;
		adjMatrix_[u][v] = false;
		if (!directed_) adjMatrix_[v][u] = false; 
	} 

	bool hasEdge(int u, int v) const { return adjMatrix_[u][v]; }

    struct AdjIterator {
        const DenseGraph *graph = 0;
        int u = -1;
        int v = -1;

        AdjIterator(const DenseGraph &graph, int u):
            graph(&graph), u(u), v(-1)
        {
            next();
        }

        bool hasNext() const
        {
            return v < graph->vertexCount();
        }

        int next()
        {
            int save = v;
            for ( v++ ; v < graph->vertexCount(); v++)
                if (graph->hasEdge(u, v))
                    break;
            return save;
        }
    };

    AdjIterator getAdjIterator(int u) const { return AdjIterator(*this, u); }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
