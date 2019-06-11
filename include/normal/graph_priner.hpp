#ifndef MINI_GRAPH_NORMAL_GRAPH_PRINTER_INC
#define MINI_GRAPH_NORMAL_GRAPH_PRINTER_INC

#include <iostream>
#include <iomanip>

namespace MiniGraph {

namespace normal {

class GraphPrinter {
public:
    template <class Graph> 
	static void showAdjLists(std::ostream &, const Graph &);

    template <class Graph> 
	static void showAdjLists(const Graph &);

    template <class Graph> 
	static void showAdjMatrix(std::ostream &, const Graph &);

    template <class Graph> 
	static void showAdjMatrix(const Graph &);
};

template <class Graph> 
void GraphPrinter::showAdjLists(std::ostream &out, const Graph &graph)
{ 
	for (int s = 0; s < graph.vertexCount(); s++) {
		out << std::setw(2) << s << ":";
        auto adjIter = graph.getAdjIterator(s);
		while (adjIter.hasNext()) { 
			out << std::setw(2) << adjIter.next() << " "; 
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

}	// namespace MiniGraph

#endif
