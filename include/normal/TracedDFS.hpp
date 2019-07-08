/**
 * @file TracedDFS.hpp
 * @brief 带Trace的深度优先搜索算法(Depth First Search)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 */
#ifndef MINI_GRAPH_NORMAL_TRACE_DFS_INC
#define MINI_GRAPH_NORMAL_TRACE_DFS_INC

#include <vector>

namespace MiniGraph {

namespace normal {

/**
 * @brief 带Trace的深度优先搜索算法
 *
 * @tparam Graph 被搜索的图类型
 *
 * @note 主体算法几乎和DFS.hpp实现一致, 唯一的区别是增进parent_向量,
 *       parent_[v]记录explore(v)的时候, v的父结点
 */
template <class Graph> 
class TracedDFS {
protected:
    const Graph &graph_;
    std::vector<bool> visited_;
    std::vector<int> parent_;

    /**
     * @brief 顶点第一次被访问的预处理函数
     *
     * @param v 顶点索引
     */
    virtual void previsit(int v) {}

    /**
     * @brief 顶点第一次被访问的后处理函数
     *
     * @param v 顶点索引
     */
    virtual void postvisit(int v) {}

public:
    /**
     * @brief 构造一个带Trace的深度优先搜索算法的对象
     *
     * @param graph 被搜索的图的对象
     */
    TracedDFS(const Graph &graph): graph_(graph), 
        visited_(graph.vertexCount(), false),
        parent_(graph.vertexCount(), -1) 
    {}

    /**
     * @brief 带Trace的深度优先地搜索图
     *
     * @param v 起始顶点
     * @param p 父顶点
     */
    void explore(int v) // p: parent vertex
    {
        visited_[v] = true;
        previsit(v);
        for (auto u: graph_.getAdjIterator(v)) {
            if (!visited_[u]) {
                parent_[u] = v;
                explore(u);
            }
        }
        postvisit(v);
    }

    /**
     * @brief 深度优先搜索的入口函数
     */
    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!visited_[v]) {
                parent_[v] = v;
                explore(v);
            }
    }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
