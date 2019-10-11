#ifndef MINI_GRAPH_NORMAL_GRAPHVIZ_WRITER_INC
#define MINI_GRAPH_NORMAL_GRAPHVIZ_WRITER_INC

#include <string>
#include <fstream>
#include <iostream>

namespace mini_graph {

namespace normal {

class GraphvizWriter {
public:
    template <class Graph> 
	static void writeDot(std::ostream &out, const Graph &graph);

    template <class Graph> 
	static void writeDot(const Graph &graph);

    template <class Graph> 
	static bool writeDotFile(const std::string &path, const Graph &graph);
};

template <class Graph> 
void GraphvizWriter::writeDot(std::ostream &out, const Graph &graph)
{ 
    std::string line;
    if (graph.isDirected()) {
        out << "digraph G {\n";
        line = "->";
    } else {
        out << "graph G {\n";
        line = "--";
    }

    for (int v = 0; v < graph.vertexCount(); v++) {
        out << "\t" << v << ";\n";
    }

    auto edge_list = edges(graph);
    for (const auto &e: edges(graph)) {
        out << "\t" << e.u << line << e.v << ";\n";
    }

    out << "}\n";
}

template <class Graph> 
bool GraphvizWriter::writeDotFile(const std::string &path, const Graph &graph)
{
    std::ofstream ofile(path);
    if (!ofile) {
        return false;
    }

    writeDot(ofile, graph);
    return true;
}

template <class Graph> 
void GraphvizWriter::writeDot(const Graph &graph)
{ 
	writeDot(std::cout, graph);
}

}	// namespace normal

}	// namespace mini_graph

#endif
