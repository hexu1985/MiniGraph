/**
 * @file DenseGraph.hpp
 * @brief 一个稠密图实现, 基于邻接矩阵(不支持平行边)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 */
#ifndef MINI_GRAPH_NORMAL_DENSE_GRAPH_INC
#define MINI_GRAPH_NORMAL_DENSE_GRAPH_INC

#include <vector>
#include "Edge.hpp"

namespace MiniGraph {

namespace normal {

/**
 * @brief 一个稠密图实现, 基于邻接矩阵(不支持平行边)
 */
class DenseGraph { 
private:
	std::vector<std::vector<bool>> adjMatrix_;  // adjacency matrix
	int vCnt_ = 0;                              // number of vertexs
    int eCnt_ = 0;                              // number of edges
	bool directed_ = false;                     // if directed graph

public:
    /**
     * @brief 构造一个稠密图对象
     *
     * @param vCnt 图的顶点数
     * @param directed 是否为有向图
     */
	DenseGraph(int vCnt, bool directed = false) :
		adjMatrix_(vCnt), vCnt_(vCnt), eCnt_(0), directed_(directed)
	{ 
		for (int i = 0; i < vCnt_; i++) 
			adjMatrix_[i].assign(vCnt_, false);
	}

    /**
     * @brief 返回图的顶点数
     *
     * @return 顶点个数
     */
	int vertexCount() const { return vCnt_; }

    /**
     * @brief 返回图的边数
     *
     * @return 边的个数
     */
	int edgeCount() const { return eCnt_; }

    /**
     * @brief 是否为有向图
     *
     * @return 如果为有向图, 返回true, 否则为false
     */
	bool isDirected() const { return directed_; }

    /**
     * @brief 向图中插入一条边
     *
     * @param e 要插入的边
     */
	void insert(Edge e)
	{ 
		int u = e.u, v = e.v;
		if (adjMatrix_[u][v] == false) eCnt_++;
		adjMatrix_[u][v] = true;
		if (!directed_) adjMatrix_[v][u] = true; 
	} 

    /**
     * @brief 从图中删除一条边
     *
     * @param e 要删除的边
     */
	void remove(Edge e)
	{ 
		int u = e.u, v = e.v;
		if (adjMatrix_[u][v] == true) eCnt_--;
		adjMatrix_[u][v] = false;
		if (!directed_) adjMatrix_[v][u] = false; 
	} 

    /**
     * @brief 判断两个顶点之间是否有直连边(两顶点是否邻接)
     *
     * @param u from顶点
     * @param v to顶点
     *
     * @return 如果u和v邻接, 返回true, 否则返回false
     */
	bool hasEdge(int u, int v) const { return adjMatrix_[u][v]; }

    /**
     * @brief 可以遍历指定顶点的所有邻接节点的迭代器
     */
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
            for (v++ ; v < (int) array.size(); v++)
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

    /**
     * @brief 获取指定顶点的邻接顶点的迭代器
     *
     * @param v 指定顶点
     *
     * @return 邻接顶点的迭代器
     */
    AdjIterator getAdjIterator(int v) const { return AdjIterator(adjMatrix_[v], -1); }
};

/**
 * @brief 获取开始迭代器
 *
 * @param adj 邻接顶点的迭代器
 *
 * @return 邻接顶点的迭代器的起始
 *
 * @note 为了支持如下使用方式:
 * for (auto u: graph.getAdjIterator(v)) {
 *      // process u
 * }
 *
 */
DenseGraph::AdjIterator begin(const DenseGraph::AdjIterator &adj)
{
    return DenseGraph::AdjIterator(*adj.pArray);
}

/**
 * @brief 获取结束迭代器
 *
 * @param adj 邻接顶点的迭代器
 *
 * @return 邻接顶点的迭代器的结束
 *
 * @note 为了支持如下使用方式:
 * for (auto u: graph.getAdjIterator(v)) {
 *      // process u
 * }
 *
 */
DenseGraph::AdjIterator end(const DenseGraph::AdjIterator &adj)
{
    return DenseGraph::AdjIterator(*adj.pArray, adj.pArray->size());
}

}   // namespace normal

}	// namespace MiniGraph

#endif
