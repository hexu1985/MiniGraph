/**
 * @file normal/DigraphTS.hpp
 * @brief 有向图的拓扑排序算法(Topological Sort)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-07-09
 *
 * @see C++算法: 图算法(第3版): 章节3.6
 */
#ifndef MINI_GRAPH_NORMAL_DIGRAPH_TS_INC
#define MINI_GRAPH_NORMAL_DIGRAPH_TS_INC

#include <vector>
#include "DFS.hpp"

namespace mini_graph {

namespace normal {

/**
 * @brief 有向图的拓扑排序
 *
 * @tparam Graph 被搜索的图类型
 */
template <class Graph>
class DigraphTS: public DFS<Graph> {
private:
    int clock_ = 0;
    std::vector<int> post_;     // postvisit clock
    std::vector<int> postI_;    // reverse topological order

    /**
     * @brief 顶点第一次被访问的后处理函数, 
     *        更新顶点的post数组的clock值, 以及clock对应结点索引的postI数组
     *
     * @param v 顶点索引
     */
    void postvisit(int v) override
    {
        post_[v] = clock_;
        postI_[clock_] = v;
        clock_++;
    }

public:
    /**
     * @brief 构造一个有向图的拓扑排序算法的对象
     *
     * @param graph 被搜索的图的对象
     */
    DigraphTS(const Graph &graph): DFS<Graph>(graph), 
        post_(graph.vertexCount()),
        postI_(graph.vertexCount())
    {
    }

    /**
     * @brief 拓扑排序
     *
     * @return 返回拓扑排序后结点的顺序 
     */
    std::vector<int> sort()
    {
        if (clock_ == 0)
            this->search();
        return std::vector<int>(postI_.rbegin(), postI_.rend());
    }
};

}   // namespace normal

}	// namespace mini_graph

#endif

