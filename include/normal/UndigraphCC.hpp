/**
 * @file normal/UndigraphCC.hpp
 * @brief 计算无向图图的连通分量(Connected Components)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 *
 * @see 算法概论中文版: 章节3.2.3
 */
#ifndef MINI_GRAPH_NORNAL_UNDIGRAPH_CC_INC
#define MINI_GRAPH_NORNAL_UNDIGRAPH_CC_INC

#include <vector>
#include "DFS.hpp"

namespace mini_graph {

namespace normal {

/**
 * @brief 计算图的连通分量(基于DFS算法)
 *
 * @tparam Graph 被计算的图类型
 */
template <class Graph> 
class UndigraphCC: public DFS<Graph> { 
protected:
    const Graph &graph_;
    int cCnt_ = 0;
    std::vector<int> ccNum_; 

    /**
     * @brief 顶点第一次被访问的预处理函数,
     *        更新顶点的ccNum数组的连通分量ID
     *
     * @param v 顶点索引
     */
    virtual void previsit(int v) 
    {
        ccNum_[v] = cCnt_;
    }

public:
    /**
     * @brief 构造计算图的连通分量的算法的对象
     *
     * @param graph 被计算的图的对象
     */
    UndigraphCC(const Graph &graph): DFS<Graph>(graph), graph_(graph), cCnt_(0), ccNum_(graph.vertexCount(), -1) {}

    /**
     * @brief 计算图的连通分量的入口函数(基于DFS)
     */
    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!this->visited_[v]) {
                this->explore(v);
                cCnt_++;
            }
    }

public:
    /**
     * @brief 获取图的连通分量个数
     *
     * @return 连通分量数
     */
    int count() const { return cCnt_; }

    /**
     * @brief 获取指定顶点所在连通分量的id
     *
     * @param v 顶点索引
     *
     * @return 连通分量id
     */
    int getCCNumber(int v) const { return ccNum_[v]; }

    /**
     * @brief 判断指定顶点是否相连(有路径可达)
     *
     * @param s from顶点
     * @param t to顶点
     *
     * @return 如果有路径可达, 返回true, 否则返沪false
     */
    bool isConnected(int s, int t) const 
    { return ccNum_[s] == ccNum_[t]; }
};

}   // namespace normal

}	// namespace mini_graph

#endif
