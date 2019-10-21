/** \example normal/dfs/sample_edge_dfs1.cpp
 * This is an example of how to use the EdgeDFS class.
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::normal;

template <class Graph>
class MyEdgeDFS: public EdgeDFS<Graph> {
public:
    MyEdgeDFS(const Graph &graph): EdgeDFS<Graph>(graph) {}

    std::string trace_str()
    {
        return os.str();
    }

private:
    ostringstream os;
    int count = 0;

    void previsit(Edge e) override
    {
        count++;
        os << "\t" << e.u << "->" << e.v << "[label=\"(" << count << ")\", color=red];\n";
    }

    void postvisit(Edge e) override
    {
        count++;
        os << "\t" << e.u << "->" << e.v << "[label=\"(" << count << ")\", color=blue, style=dashed, dir=back];\n";
    }

};

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}}; // graph1.jpg

    DenseGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    MyEdgeDFS<DenseGraph> dfs(graph);
    dfs.search();    // output对应:graph1-dfs-a.jpg, graph1-dfs-b.jpg

    GraphvizWriter::AttributesForLambda attributes;
    attributes.get_additional_attributes = 
        [&]() -> std::string {
            return dfs.trace_str();
        };

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph, attributes);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_edge_dfs2.dot", graph, attributes);

    return 0;
}


