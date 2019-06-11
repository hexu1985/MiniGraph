#ifndef MINI_GRAPH_DENSE_GRAPH_INC
#define MINI_GRAPH_DENSE_GRAPH_INC

#include <vector>
#include "edge.hpp"

namespace MiniGraph {

namespace normal {

class DenseGraph { 
private:
	std::vector<std::vector<bool>> adjMatrix_;  // adjacency matrix
	int vCnt_ = 0;                              // number of vertexs
    int eCnt_ = 0;                              // number of edges
	bool directed_ = false;                     // if directed graph

public:
	DenseGraph(int vCnt, bool directed = false) :
		adjMatrix_(vCnt), vCnt_(vCnt), eCnt_(0), directed_(directed)
	{ 
		for (int i = 0; i < vCnt_; i++) 
			adjMatrix_[i].assign(vCnt_, false);
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

    struct AdjIterator: public std::iterator<std::forward_iterator_tag, int> {
        const std::vector<bool> *pArray = 0;
        int v = -1;

        AdjIterator(const std::vector<bool> &array):
            pArray(&array)
        {
            next();
        }

        AdjIterator(const std::vector<bool> &array, int v):
            pArray(&array), v(v)
        {
        }

        void next()
        {
            auto &array = *pArray;
            for (v++ ; v < array.size(); v++)
                if (array[v])
                    break;
        }

        int operator *() const
        {
            return v;
        }

        AdjIterator &operator ++()
        {
            next();
            return *this;
        }

        AdjIterator operator ++(int)
        {
            AdjIterator tmp(*this);
            next();
            return tmp;
        }

        bool operator ==(const AdjIterator &rhs) const
        {
            return (this->pArray == rhs.pArray && this->v == rhs.v);
        }

        bool operator !=(const AdjIterator &rhs) const
        {
            return !(*this == rhs);
        }
    };

    AdjIterator getAdjIterator(int v) const { return AdjIterator(adjMatrix_[v], -1); }
};

DenseGraph::AdjIterator begin(const DenseGraph::AdjIterator &adj)
{
    return DenseGraph::AdjIterator(*adj.pArray);
}

DenseGraph::AdjIterator end(const DenseGraph::AdjIterator &adj)
{
    return DenseGraph::AdjIterator(*adj.pArray, adj.pArray->size());
}

}   // namespace normal

}	// namespace MiniGraph

#endif
