/**
 * @file weight/GraphPrinter.hpp
 * @brief 输出图的邻接表表示
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-07-09
 */
#ifndef MINI_GRAPH_WEIGHT_GRAPH_PRINTER_INC
#define MINI_GRAPH_WEIGHT_GRAPH_PRINTER_INC

#include <iostream>
#include <iomanip>

namespace MiniGraph {

namespace weight {

/**
 * @brief 输出图的邻接表表示的工具类
 */
class GraphPrinter {
public:
    /**
     * @brief 输出图的邻接表表示, 指定ostream
     *
     * @tparam Graph 被输出的图的类型
     * @param out 指定输出到的ostream
     * @param graph 被输出的图
     */
    template <class Graph>
	static void showAdjLists(std::ostream &out, const Graph &graph);

    /**
     * @brief 输出图的邻接表表示到std::cout
     *
     * @tparam Graph 被输出的图的类型
     * @param graph 被输出的图
     */
    template <class Graph>
	static void showAdjLists(const Graph &graph);
};

template <class Graph>
void GraphPrinter::showAdjLists(std::ostream &out, const Graph &graph)
{ 
	for (int v = 0; v < graph.vertexCount(); v++) {
		out << std::setw(2) << v << ":";
        for (auto e: graph.getAdjIterator(v)) {
            out << std::setw(2) << e->other(v) << "(" << e->weight() << ") ";
        }
		out << std::endl;
	}
}

template <class Graph>
void GraphPrinter::showAdjLists(const Graph &graph)
{ 
	showAdjLists(std::cout, graph);
}

}	// namespace weight

}	// namespace MiniGraph

#endif
