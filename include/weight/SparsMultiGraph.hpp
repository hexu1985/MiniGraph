#ifndef MINI_GRAPH_WEIGHT_SPARSE_MUTLI_GRAPH_INC
#define MINI_GRAPH_WEIGHT_SPARSE_MUTLI_GRAPH_INC

#include <vector>
#include <forward_list>
#include <algorithm>
#include "Edge.hpp"

namespace MiniGraph {

namespace weight {

class SparseMultiGraph { 
private:
	std::vector<std::forward_list<Edge *>> adjLists_;  // adjacency lists
	int vCnt_ = 0;                                  // number of vertexs
    int eCnt_ = 0;                                  // number of edges
	bool directed_ = false;                         // if directed graph

public:
	SparseMultiGraph(int vCnt, bool directed = false) :
		adjLists_(vCnt), vCnt_(vCnt), eCnt_(0), directed_(directed) 
	{ 
	}

	int vertexCount() const { return vCnt_; }
	int edgeCount() const { return eCnt_; }
	bool isDirected() const { return directed_; }

	void insert(Edge *e)
	{ 
		int u = e->u(), v = e->v();
		adjLists_[u].push_front(e);
		if (!directed_) adjLists_[v].push_front(e);
		eCnt_++;
	} 

	void remove(Edge *e)
	{
		int u = e->u(), v = e->v();
        int n = 0;
        adjLists_[u].remove_if([u, v, &n](Edge *e) { if (e->other(u) == v) {n++; return true;} else return false; });
		eCnt_-=n;

		if (directed_ || n == 0) return; 
        adjLists_[v].remove_if([u, v](Edge *e) { return (e->other(v) == u); });
	} 

	Edge *edge(int u, int v) const
	{
        for (auto e: adjLists_[u]) {
            if (e->other(u) == v)
                return e;
        }
        return nullptr;
	}

    const std::forward_list<Edge *> &getAdjIterator(int v) const { return adjLists_[v]; }
};

}   // namespace weight

}	// namespace MiniGraph

#endif
