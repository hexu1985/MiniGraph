#ifndef MINI_GRAPH_WEIGHT_GRAPH_PRINTER_INC
#define MINI_GRAPH_WEIGHT_GRAPH_PRINTER_INC

#include <iostream>
#include <iomanip>

namespace MiniGraph {

namespace weight {

class GraphPrinter {
public:
    template <class Graph, class Edge = typename Graph::EdgeType>
	static void showAdjLists(std::ostream &, const Graph &);

    template <class Graph, class Edge = typename Graph::EdgeType>
	static void showAdjLists(const Graph &);
};

template <class Graph, class Edge = typename Graph::EdgeType>
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

template <class Graph, class Edge = typename Graph::EdgeType>
void GraphPrinter::showAdjLists(const Graph &graph)
{ 
	showAdjLists<Graph, Edge>(std::cout, graph);
}

}	// namespace weight

}	// namespace MiniGraph

#endif
