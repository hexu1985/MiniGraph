/**
 * @file normal/GraphPrinter.hpp
 * @brief 输出图的邻接矩阵和邻接表表示
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-07-09
 */
#ifndef MINI_GRAPH_NORMAL_GRAPH_PRINTER_INC
#define MINI_GRAPH_NORMAL_GRAPH_PRINTER_INC

#include <iostream>
#include <iomanip>

namespace mini_graph {

namespace normal {

/**
 * @brief 输出图的邻接矩阵和邻接表表示的工具类
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

    /**
     * @brief 输出图的邻接矩阵表示, 指定ostream
     *
     * @tparam Graph 被输出的图的类型
     * @param out 指定输出到的ostream
     * @param graph 被输出的图
     */
    template <class Graph> 
	static void showAdjMatrix(std::ostream &out, const Graph &graph);

    /**
     * @brief 输出图的邻接矩阵表示到std::cout
     *
     * @tparam Graph 被输出的图的类型
     * @param graph 被输出的图
     */
    template <class Graph> 
	static void showAdjMatrix(const Graph &graph);
};

template <class Graph> 
void GraphPrinter::showAdjLists(std::ostream &out, const Graph &graph)
{ 
	for (int v = 0; v < graph.vertexCount(); v++) {
		out << std::setw(2) << v << ":";
        for (auto u: graph.getAdjIterator(v)) {
            out << std::setw(2) << u << " ";
        }
		out << std::endl;
	}
}

template <class Graph> 
void GraphPrinter::showAdjLists(const Graph &graph)
{ 
	showAdjLists(std::cout, graph);
}

template <class Graph> 
void GraphPrinter::showAdjMatrix(std::ostream &out, const Graph &graph)
{
    out << "  |";
    for (int t = 0; t < graph.vertexCount(); t++) {
        out << std::setw(2) << t << " ";
    }
    out << "\n";

    out << "---";
    for (int t = 0; t < graph.vertexCount(); t++) {
        out << "---";
    }
    out << "\n";

    for (int v = 0; v < graph.vertexCount(); v++) {
        out << std::setw(2) << v << "|";
        for (int w = 0; w < graph.vertexCount(); w++) {
            out << std::setw(2) << static_cast<int>(graph.hasEdge(v,w)) << " ";
        }
        out << "\n";
    }
}

template <class Graph> 
void GraphPrinter::showAdjMatrix(const Graph &G)
{ 
	showAdjMatrix(std::cout, G);
}

}	// namespace normal

}	// namespace mini_graph

#endif
