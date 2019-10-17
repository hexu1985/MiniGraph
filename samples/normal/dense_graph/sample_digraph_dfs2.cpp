/** \example normal/dense_graph/sample_digraph_dfs2.cpp
 * This is an example of how to use the DigraphDFS class.
 */
#include <iostream>
#include <vector>
#include <sstream>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::normal;

int main()
{
    int vertexNumber = 13;
    vector<Edge> edges = {
        {4,2}, {2,3}, {3,2}, {0,6}, {0,1},
        {2,0}, {11,12}, {12,9}, {9,10}, {9,11},
        {8,9}, {10,12}, {4,11}, {4,3}, {3,5},
        {7,8}, {8,7}, {5,4}, {0,5}, {6,4},
        {6,9}, {7,6}};  // digraph1.jpg

    SparseMultiGraph graph(vertexNumber, true);  // directed true
    for (auto edge: edges)
        graph.insert(edge);

    DigraphDFS<SparseMultiGraph> dfs(graph);
    dfs.search();

    GraphvizWriter::AttributesForLambda attributes;
    attributes.get_vertex_attribute =
        [&](int v) -> std::string {
            std::ostringstream os;
            os << "[label=\"" << v << "("
                << dfs.getPreOrder(v) << ","
                << dfs.getPostOrder(v) << ")\"]";
            return os.str();
        };

    attributes.get_edge_attribute = 
        [&](Edge e) -> std::string {
            std::ostringstream os;
            os << "[label=\"" 
               << dfs.getEdgeType(e.u, e.v) << "\"";
            if (dfs.getEdgeTypeEnum(e.u, e.v) == DigraphDFS<SparseMultiGraph>::tree)
                os << ", color = red";
            os << "]";
            return os.str();
        };

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph, attributes);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_digraph_dfs2.dot", graph, attributes);

    return 0;
}


