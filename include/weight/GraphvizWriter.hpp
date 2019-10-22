#ifndef MINI_GRAPH_WEIGHT_GRAPHVIZ_WRITER_INC
#define MINI_GRAPH_WEIGHT_GRAPHVIZ_WRITER_INC

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>

namespace mini_graph {

namespace weight {

class GraphvizWriter {
public:
    class Attributes {
    public:
        Attributes() {} 
        virtual ~Attributes() {}

        static std::string defaultGraphSymbol(bool is_directed)
        {
            if (is_directed) {
                return "digraph G";
            } else {
                return "graph G";
            }
        }

        static std::string defaultLineSymbol(bool is_directed)
        {
            if (is_directed) {
                return "->";
            } else {
                return "--";
            }
        }

        static std::string defaultVertexAttribute(int v)
        {
            return null_string;
        }

        static std::string defaultEdgeAttribute(Edge *e)
        {
            std::ostringstream os;
            os << "[label=\"" << e->weight() << "\"]";
            return os.str();
        }

        static std::string defaultAdditionalAttributes()
        {
            return null_string;
        }

        virtual std::string getGraphSymbol(bool is_directed) const
        {
            return defaultGraphSymbol(is_directed);
        }

        virtual std::string getLineSymbol(bool is_directed) const
        {
            return defaultLineSymbol(is_directed);
        }

        virtual std::string getVertexAttribute(int v) const
        {
            return defaultVertexAttribute(v);
        }

        virtual std::string getEdgeAttribute(Edge *e) const
        {
            return defaultEdgeAttribute(e);
        }

        virtual std::string getAdditionalAttributes() const
        {
            return defaultAdditionalAttributes();
        }

        static const std::string null_string;
    };

    struct AttributesForLambda: public Attributes {
        std::function<std::string (bool)> get_graph_symbol = [](bool is_directed) -> std::string { return defaultGraphSymbol(is_directed); };
        std::function<std::string (bool)> get_line_symbol = [](bool is_directed) -> std::string { return defaultLineSymbol(is_directed); };
        std::function<std::string (int)> get_vertex_attribute = [](int v) -> std::string { return defaultVertexAttribute(v); };
        std::function<std::string (Edge *)> get_edge_attribute = [](Edge *e) -> std::string { return defaultEdgeAttribute(e); };
        std::function<std::string ()> get_additional_attributes = []() -> std::string { return defaultAdditionalAttributes(); };

        std::string getGraphSymbol(bool is_directed) const override
        {
            return get_graph_symbol(is_directed);
        }

        std::string getLineSymbol(bool is_directed) const override
        {
            return get_line_symbol(is_directed);
        }

        std::string getVertexAttribute(int v) const override
        {
            return get_vertex_attribute(v);
        }

        std::string getEdgeAttribute(Edge *e) const override
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
    bool is_directed = graph.isDirected();
    std::string line = attributes.getLineSymbol(is_directed);
    out << attributes.getGraphSymbol(is_directed) << " {\n";

    for (int v = 0; v < graph.vertexCount(); v++) {
        out << "\t" << v << attributes.getVertexAttribute(v) << ";\n";
    }

    auto edge_list = edges(graph);
    for (const auto &e: edges(graph)) {
        out << "\t" << e->u() << line << e->v() << attributes.getEdgeAttribute(e) << ";\n";
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

}	// namespace weight

}	// namespace mini_graph

#endif
