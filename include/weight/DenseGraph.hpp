#ifndef MINI_GRAPH_WEIGHT_DENSE_GRAPH_INC
#define MINI_GRAPH_WEIGHT_DENSE_GRAPH_INC

#include <vector>
#include "Edge.hpp"

namespace MiniGraph {

namespace weight {

class DenseGraph { 
private:
	std::vector<std::vector<Edge *>> adjMatrix_;    // adjacency matrix
	int vCnt_ = 0;                                  // number of vertexs
    int eCnt_ = 0;                                  // number of edges
	bool directed_ = false;                         // if directed graph

public:
	DenseGraph(int vCnt, bool directed = false) :
		adjMatrix_(vCnt), vCnt_(vCnt), eCnt_(0), directed_(directed)
	{ 
		for (int i = 0; i < vCnt_; i++) 
			adjMatrix_[i].assign(vCnt_, nullptr);
	}

	int vertexCount() const { return vCnt_; }
	int edgeCount() const { return eCnt_; }
	bool isDirected() const { return directed_; }

	void insert(Edge *e)
	{ 
		int u = e->u(), v = e->v();
		if (adjMatrix_[u][v] == nullptr) eCnt_++;
		adjMatrix_[u][v] = e;
		if (!directed_) adjMatrix_[v][u] = e; 
	} 

	void remove(Edge *e)
	{ 
		int u = e->u(), v = e->v();
		if (adjMatrix_[u][v]) eCnt_--;
		adjMatrix_[u][v] = nullptr;
		if (!directed_) adjMatrix_[v][u] = nullptr; 
	} 

    Edge *edge(int u, int v) const { return adjMatrix_[u][v]; }

    struct AdjIterator: public std::iterator<std::forward_iterator_tag, int> {
        const std::vector<Edge *> *pArray = 0;
        int v = -1;

        AdjIterator(const std::vector<Edge *> &array):
            pArray(&array)
        {
            next();
        }

        AdjIterator(const std::vector<Edge *> &array, int v):
            pArray(&array), v(v)
        {
        }

        void next()
        {
            auto &array = *pArray;
            for (v++ ; v < (int) array.size(); v++)
                if (array[v])
                    break;
        }

        Edge *operator *() const
        {
            auto &array = *pArray;
            return array[v];
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

}   // namespace weight

}	// namespace MiniGraph

#endif
