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
    class Attributes {
    public:
        Attributes() {} 
        virtual ~Attributes() {}

        virtual std::string getVertexAttribute(int v) const
        {
            return null_string;
        }

        virtual std::string getEdgeAttribute(Edge e) const
        {
            return null_string;
        }

        virtual std::string getAdditionalAttributes() const
        {
            return null_string;
        }

        static const std::string null_string;
    };

    struct AttributesForLambda: public Attributes {
        std::function<std::string (int)> get_vertex_attribute = [](int v) -> std::string { return Attributes::null_string; };
        std::function<std::string (Edge)> get_edge_attribute = [](Edge e) -> std::string { return Attributes::null_string; };
        std::function<std::string ()> get_additional_attributes = []() -> std::string { return Attributes::null_string; };

        std::string getVertexAttribute(int v) const override
        {
            return get_vertex_attribute(v);
        }

        std::string getEdgeAttribute(Edge e) const override
        {
            return get_edge_attribute(e);
        }

        std::string getAdditionalAttributes() const override
        {
            return get_additional_attributes();
        }
    }; 

public:
    template <class Graph> 
	static void writeDot(std::ostream &out, const Graph &graph, const Attributes &attributes = Attributes()); 

    template <class Graph> 
	static void writeDot(const Graph &graph, const Attributes &attributes = Attributes()); 

    template <class Graph> 
	static bool writeDotFile(const std::string &path, const Graph &graph, const Attributes &attributes = Attributes()); 
};

const std::string GraphvizWriter::Attributes::null_string{};

template <class Graph> 
void GraphvizWriter::writeDot(std::ostream &out, const Graph &graph, const Attributes &attributes)
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
        out << "\t" << v << attributes.getVertexAttribute(v) << ";\n";
    }

    auto edge_list = edges(graph);
    for (const auto &e: edges(graph)) {
        out << "\t" << e.u << line << e.v << attributes.getEdgeAttribute(e) << ";\n";
    }

    out << attributes.getAdditionalAttributes();

    out << "}\n";
}

template <class Graph> 
bool GraphvizWriter::writeDotFile(const std::string &path, const Graph &graph, const Attributes &attributes)
{
    std::ofstream ofile(path);
    if (!ofile) {
        return false;
    }

    writeDot(ofile, graph, attributes);
    return true;
}

template <class Graph> 
void GraphvizWriter::writeDot(const Graph &graph, const Attributes &attributes)
{ 
	writeDot(std::cout, graph, attributes);
}

}	// namespace normal

}	// namespace mini_graph

#endif
