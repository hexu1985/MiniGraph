#ifndef MINI_GRAPH_NORMAL_SPARSE_MUTLI_GRAPH_INC
#define MINI_GRAPH_NORMAL_SPARSE_MUTLI_GRAPH_INC

#include <vector>
#include <forward_list>
#include <algorithm>
#include "edge.hpp"

namespace MiniGraph {

namespace normal {

class SparseMultiGraph { 
private:
	std::vector<std::forward_list<int>> adjLists_;  // adjacency lists
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

	void insert(Edge e)
	{ 
		int u = e.u, v = e.v;
		adjLists_[u].push_front(v);
		if (!directed_) adjLists_[v].push_front(u);
		eCnt_++;
	} 

	void remove(Edge e)
	{
		int u = e.u, v = e.v;
        int n = 0;
        adjLists_[u].remove_if([v, &n](int w) { if (w == v) {n++; return true;} else return false; });
		eCnt_-=n;

		if (directed_ || n == 0) return; 
        adjLists_[v].remove(u);
	} 

	bool hasEdge(int u, int v) const
	{
        for (auto w: adjLists_[u]) {
            if (w == v)
                return true;
        }
        return false;
	}

    const std::forward_list<int> &getAdjIterator(int v) const { return adjLists_[v]; }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
