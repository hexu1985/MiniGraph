/**
 * @file DigrahpDFS.hpp
 * @brief 有向图的深度优先搜索算法
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 *
 * @see 算法概论中文版: 章节3.3.1
 */
#ifndef MINI_GRAPH_NORMAL_DIGRAPH_DFS_INC
#define MINI_GRAPH_NORMAL_DIGRAPH_DFS_INC

#include <limits>
#include <vector>
#include <string>
#include "TracedDFS.hpp"

namespace MiniGraph {

namespace normal {

/**
 * @brief 有向图的深度优先搜索算法
 *
 * @tparam Graph 被搜索的图类型
 *
 * @note 继承自TracedDFS类
 */
template <class Graph> 
class DigraphDFS: public TracedDFS<Graph> {
protected:
    int clock_ = 0;
    std::vector<int> pre_;  // previsit clock
    std::vector<int> post_; // postvisit clock

    /**
     * @brief 顶点第一次被访问的预处理函数, 
     *        更新顶点的pre数组的clock值
     *
     * @param v 顶点索引
     */
    void previsit(int v) override
    {
        pre_[v] = clock_;
        clock_++;
    }

    /**
     * @brief 顶点第一次被访问的后处理函数, 
     *        更新顶点的post数组的clock值
     *
     * @param v 顶点索引
     */
    void postvisit(int v) override
    {
        post_[v] = clock_;
        clock_++;
    }

public:
    /**
     * @brief 构造一个带Trace的深度优先搜索算法的对象
     *
     * @param graph 被搜索的图的对象
     */
    DigraphDFS(const Graph &graph): TracedDFS<Graph>(graph), 
        pre_(graph.vertexCount(), std::numeric_limits<int>::max()),
        post_(graph.vertexCount(), std::numeric_limits<int>::max())
    {}

    /**
     * @brief 获取有向图的深度优先搜索中, 边的类型
     *
     * @param u 边的from顶点
     * @param v 边的to顶点
     *
     * @return 边的类型的字符串
     *
     * @note 边类型主要分为四种: 
     *      tree(树边), 
     *      down(前向边),
     *      back(回边),
     *      cross(横跨边).
     *       
     */
    std::string getEdgeType(int u, int v) const
    {
        // 树边或前向边
        // [   [     ]    ]
        // u   v     v    u
        if (pre_[u] < pre_[v] && post_[v] < post_[u]) {
            if (this->parent_[v] == u) {
                return "tree(树边)";
            } else {
                return "down(前向边)";
            }
        }

        // 回边
        // [   [     ]    ]
        // v   u     u    v
        if (pre_[v] < pre_[u] && post_[u] < post_[v]) {
            return "back(回边)";
        }

        // 横跨边
        // [   ]     [    ]
        // u   u     v    v
        // v   v     u    u
        if (post_[u] < pre_[v] || post_[v] < pre_[u]) {
            return "cross(横跨边)";
        }

        return "impossible(不可能的情况)";
    }

    /**
     * @brief 获取指定顶点的previsit的clock值
     *
     * @param v 顶点索引
     *
     * @return previsit的clock值
     */
    int getPreOrder(int v) { return pre_[v]; }

    /**
     * @brief 获取指定顶点的postvisit的clock值
     *
     * @param v 顶点索引
     *
     * @return postvisit的clock值
     */
    int getPostOrder(int v) { return post_[v]; }
};

}   // namespace normal

}	// namespace MiniGraph

#endif

