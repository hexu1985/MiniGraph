/**
 * @file ConnectedComponents.hpp
 * @brief 计算图的连通分量(Connected Components)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 */
#ifndef MINI_GRAPH_NORNAL_CONNECTED_COMPONENTS_INC
#define MINI_GRAPH_NORNAL_CONNECTED_COMPONENTS_INC

#include <vector>

namespace MiniGraph {

namespace normal {

/**
 * @brief 计算图的连通分量(基于DFS算法)
 *
 * @tparam Graph 被计算的图类型
 */
template <class Graph> 
class ConnectedComponents { 
protected:
    const Graph &graph_;
    int cCnt_ = 0;
    std::vector<int> ccNum_; 

    /**
     * @brief 顶点第一次被访问的预处理函数
     *
     * @param v 顶点索引
     */
    virtual void previsit(int v) {}

    /**
     * @brief 顶点第一次被访问的处理函数, 默认行为是设置顶点的连通分量id
     *
     * @param v 顶点索引
     */
    virtual void visit(int v) { ccNum_[v] = cCnt_; }

    /**
     * @brief 顶点第一次被访问的后处理函数
     *
     * @param v 顶点索引
     */
    virtual void postvisit(int v) {}

    /**
     * @brief 顶点是否被访问
     *
     * @param v 顶点索引
     *
     * @return 如果顶点已被访问, 返回true, 否则返回false
     */
    virtual bool isVisited(int v) { return ccNum_[v] >= 0; }

    /**
     * @brief 深度优先地搜索图
     *
     * @param v 起始顶点
     */
    virtual void explore(int v)
    {
        previsit(v);
        visit(v);
        for (auto w: graph_.getAdjIterator(v)) {
            if (!isVisited(w))
                explore(w);
        }
        postvisit(v);
    }

public:
    /**
     * @brief 构造计算图的连通分量的算法的对象
     *
     * @param graph 被计算的图的对象
     */
    ConnectedComponents(const Graph &graph): graph_(graph), cCnt_(0), ccNum_(graph.vertexCount(), -1) {}

    /**
     * @brief 计算图的连通分量的入口函数(基于DFS)
     */
    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!isVisited(v)) {
                explore(v);
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

}	// namespace MiniGraph

#endif
