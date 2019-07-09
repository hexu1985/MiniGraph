/**
 * @file edges.hpp
 * @brief 获取图的所有边的列表
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-07-09
 */
#ifndef MINI_GRAPH_WEIGHT_EDGES_INC
#define MINI_GRAPH_WEIGHT_EDGES_INC

#include <vector>
#include "Edge.hpp"

namespace MiniGraph {

namespace weight {

/**
 * @brief 获取指定图的所有边的列表
 *
 * @tparam Graph 图的类型
 * @param graph 图对象
 *
 * @return 边的列表
 */
template <class Graph> 
std::vector<Edge *> edges(const Graph &graph)
{ 
    std::vector<Edge *> vec;
    for (int v = 0; v < graph.vertexCount(); v++) {
        for (auto e: graph.getAdjIterator(v)) {
            if (e->from(v))
                vec.push_back(e);
        }
    }
    return vec;
}

}   // namespace weight

}	// namespace MiniGraph

#endif
