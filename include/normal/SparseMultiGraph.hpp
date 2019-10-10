/**
 * @file normal/SparseMultiGraph.hpp
 * @brief 一个稀疏图实现, 基于邻接链表(支持平行边)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 *
 * @see Algorithms in C++, Third Edition, Part 5 Graph Algorithms:
 *      Chapter 17.4
 */
#ifndef MINI_GRAPH_NORMAL_SPARSE_MUTLI_GRAPH_INC
#define MINI_GRAPH_NORMAL_SPARSE_MUTLI_GRAPH_INC

#include <vector>
#include <forward_list>
#include <algorithm>
#include "Edge.hpp"

namespace mini_graph {

namespace normal {

/**
 * @brief 一个稀疏图实现, 基于邻接链表(支持平行边)
 */
class SparseMultiGraph { 
private:
	std::vector<std::forward_list<int>> adjLists_;  // adjacency lists
	int vCnt_ = 0;                                  // number of vertexs
    int eCnt_ = 0;                                  // number of edges
	bool directed_ = false;                         // if directed graph

public:
    /**
     * @brief 构造一个稀疏图对象
     *
     * @param vCnt 图的顶点数
     * @param directed 是否为有向图
     */
	SparseMultiGraph(int vCnt, bool directed = false) :
		adjLists_(vCnt), vCnt_(vCnt), eCnt_(0), directed_(directed) 
	{ 
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
		adjLists_[u].push_front(v);
		if (!directed_) adjLists_[v].push_front(u);
		eCnt_++;
	} 

    /**
     * @brief 从图中删除一条边
     *
     * @param e 要删除的边
     */
	void remove(Edge e)
	{
		int u = e.u, v = e.v;
        int n = 0;
        adjLists_[u].remove_if([v, &n](int w) { if (w == v) {n++; return true;} else return false; });
		eCnt_-=n;

		if (directed_ || n == 0) return; 
        adjLists_[v].remove(u);
	} 

    /**
     * @brief 判断两个顶点之间是否有直连边(两顶点是否邻接)
     *
     * @param u from顶点
     * @param v to顶点
     *
     * @return 如果u和v邻接, 返回true, 否则返回false
     */
	bool hasEdge(int u, int v) const
	{
        for (auto w: adjLists_[u]) {
            if (w == v)
                return true;
        }
        return false;
	}

    /**
     * @brief 获取指定顶点的邻接顶点的列表
     *
     * @param v 指定顶点
     *
     * @return 邻接顶点的迭代器
     */
    const std::forward_list<int> &getAdjIterator(int v) const { return adjLists_[v]; }
};

}   // namespace normal

}	// namespace mini_graph

#endif
