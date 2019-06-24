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
     * @brief 顶点第一次被访问的处理函数, 默认行为是设置顶点已被访问标志,
     *        并且设置被访问顶点的父顶点索引
     *
     * @param v 顶点索引
     * @param p 父顶点索引
     */
    virtual void visit(int v, int p)
    {
        visited_[v] = true; 
        parent_[v] = p;
    }

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
    virtual bool isVisited(int v) { return visited_[v]; }

    /**
     * @brief 带Trace的深度优先地搜索图
     *
     * @param v 起始顶点
     * @param p 父顶点
     */
    virtual void explore(int v, int p) // p: parent vertex
    {
        previsit(v);
        visit(v, p);
        for (auto w: graph_.getAdjIterator(v)) {
            if (!isVisited(w))
                explore(w, v);
        }
        postvisit(v);
    }

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
     * @brief 深度优先搜索的入口函数
     */
    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!isVisited(v))
                explore(v, v);
    }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
