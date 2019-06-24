/**
 * @file DFS.hpp
 * @brief 深度优先搜索算法(Depth First Search)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 */
#ifndef MINI_GRAPH_NORMAL_DFS_INC
#define MINI_GRAPH_NORMAL_DFS_INC

#include <vector>

namespace MiniGraph {

namespace normal {

/**
 * @brief 深度优先搜索算法
 *
 * @tparam Graph 被搜索的图类型
 */
template <class Graph> 
class DFS {
protected:
    const Graph &graph_;
    std::vector<bool> visited_;

    /**
     * @brief 顶点第一次被访问的预处理函数
     *
     * @param v 顶点索引
     */
    virtual void previsit(int v) {}

    /**
     * @brief 顶点第一次被访问的处理函数, 默认行为是设置顶点已被访问标志
     *
     * @param v 顶点索引
     */
    virtual void visit(int v) { visited_[v] = true; }

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
     * @brief 构造一个深度优先搜索算法的对象
     *
     * @param graph 被搜索的图的对象
     */
    DFS(const Graph &graph): graph_(graph), visited_(graph.vertexCount(), false) {}

    /**
     * @brief 深度优先搜索的入口函数
     */
    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!isVisited(v))
                explore(v);
    }
};

}   // namespace normal

}	// namespace MiniGraph

#endif
