/** \example normal/dense_graph/sample_graphviz_writer1.cpp
 * This is an example of how to use the GraphvizWriter class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::normal;

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}}; // graph1.jpg

    DenseGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_graphviz_writer1.dot", graph);

    return 0;
}
