/**
 * @file normal/EdgeDFS.hpp
 * @brief 深度优先搜索算法(Depth First Search)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-10-21
 *
 * @see 算法概论中文版: 章节3.2.1~3.2.2
 */
#ifndef MINI_GRAPH_NORMAL_EDGE_DFS_INC
#define MINI_GRAPH_NORMAL_EDGE_DFS_INC

#include "Edge.hpp"
#include <vector>

namespace mini_graph {

namespace normal {

/**
 * @brief 深度优先搜索算法
 *
 * @tparam Graph 被搜索的图类型
 */
template <class Graph> 
class EdgeDFS {
protected:
    const Graph &graph_;
    std::vector<bool> visited_;

    /**
     * @brief 顶点第一次被访问的预处理函数
     *
     * @param e e.v为被访问顶点, e.u为父顶点
     */
    virtual void previsit(Edge e) {}

    /**
     * @brief 顶点第一次被访问的后处理函数
     *
     * @param e e.v为被访问顶点, e.u为父顶点
     */
    virtual void postvisit(Edge e) {}

public:
    /**
     * @brief 构造一个深度优先搜索算法的对象
     *
     * @param graph 被搜索的图的对象
     */
    EdgeDFS(const Graph &graph): graph_(graph), 
        visited_(graph.vertexCount(), false)
    {}

    /**
     * @brief 深度优先地搜索图
     *
     * @param v 起始顶点
     */
    void explore(Edge e)
    {
        visited_[e.v] = true;
        previsit(e);
        for (auto w: graph_.getAdjIterator(e.v)) {
            if (!visited_[w])
                explore(Edge(e.v, w));
        }
        postvisit(e);
    }

    /**
     * @brief 深度优先搜索的入口函数
     */
    void search()
    {
        for (int v = 0; v < graph_.vertexCount(); v++)
            if (!visited_[v])
                explore(Edge(v, v));
    }
};

}   // namespace normal

}	// namespace mini_graph

#endif
