/**
 * @file normal/Edge.hpp
 * @brief 不带权重的边
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 *
 * @see C++算法: 图算法(第3版): 章节1.1
 */
#ifndef MINI_GRAPH_NORMAL_EDGE_INC
#define MINI_GRAPH_NORMAL_EDGE_INC

namespace mini_graph {

namespace normal {

/**
 * @brief 不带权重的边
 */
struct Edge {
    /**
     * @brief u为from顶点, v为to顶点
     */
	int u, v;

    /**
     * @brief 构造一个边对象
     *
     * @param u u为from顶点
     * @param v v为to顶点
     */
	Edge(int u = -1, int v = -1): u(u), v(v) { }
};

}   // namespace normal

}	// namespace mini_graph

#endif
