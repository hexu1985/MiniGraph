#ifndef MINI_GRAPH_NORMAL_GRAPHVIZ_WRITER_INC
#define MINI_GRAPH_NORMAL_GRAPHVIZ_WRITER_INC

#include <string>
#include <fstream>
#include <iostream>
#include <functional>

namespace mini_graph {

namespace normal {

class GraphvizWriter {
public:
    typedef std::function<std::string (int)> GenVertexAttr;
    typedef std::function<std::string (Edge)> GenEdgeAttr;

    static const std::string null_string;
    static const GenVertexAttr null_vertex_attr;
    static const GenEdgeAttr null_edge_attr;

    template <class Graph> 
	static void writeDot(std::ostream &out, const Graph &graph, 
            const GenVertexAttr &gen_vertex_attr = null_vertex_attr, const GenEdgeAttr &gen_edge_attr = null_edge_attr);

    template <class Graph> 
	static void writeDot(const Graph &graph,
            const GenVertexAttr &gen_vertex_attr = null_vertex_attr, const GenEdgeAttr &gen_edge_attr = null_edge_attr);

    template <class Graph> 
	static bool writeDotFile(const std::string &path, const Graph &graph,
            const GenVertexAttr &gen_vertex_attr = null_vertex_attr, const GenEdgeAttr &gen_edge_attr = null_edge_attr);
};

const std::string GraphvizWriter::null_string{};
const GraphvizWriter::GenVertexAttr GraphvizWriter::null_vertex_attr = [](int) -> std::string { return GraphvizWriter::null_string;};
const GraphvizWriter::GenEdgeAttr GraphvizWriter::null_edge_attr = [](Edge) -> std::string { return GraphvizWriter::null_string;};

template <class Graph> 
void GraphvizWriter::writeDot(std::ostream &out, const Graph &graph,
        const GenVertexAttr &gen_vertex_attr, const GenEdgeAttr &gen_edge_attr)
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
        out << "\t" << v << gen_vertex_attr(v) << ";\n";
    }

    auto edge_list = edges(graph);
    for (const auto &e: edges(graph)) {
        out << "\t" << e.u << line << e.v << gen_edge_attr(e) << ";\n";
    }

    out << "}\n";
}

template <class Graph> 
bool GraphvizWriter::writeDotFile(const std::string &path, const Graph &graph,
        const GenVertexAttr &gen_vertex_attr, const GenEdgeAttr &gen_edge_attr)
{
    std::ofstream ofile(path);
    if (!ofile) {
        return false;
    }

    writeDot(ofile, graph, gen_vertex_attr, gen_edge_attr);
    return true;
}

template <class Graph> 
void GraphvizWriter::writeDot(const Graph &graph,
        const GenVertexAttr &gen_vertex_attr, const GenEdgeAttr &gen_edge_attr)
{ 
	writeDot(std::cout, graph, gen_vertex_attr, gen_edge_attr);
}

}	// namespace normal

}	// namespace mini_graph

#endif
