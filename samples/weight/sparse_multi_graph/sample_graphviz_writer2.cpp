/** \example weight/sparse_multi_graph/sample_graphviz_writer2.cpp
 * This is an example of how to use the GraphvizWriter class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::weight;

int main()
{
    int vertexNumber = 6;
    vector<Edge> edges = {
        {0,1, .41},
        {1,2, .51},
        {2,3, .50},
        {4,3, .36},
        {3,5, .38},
        {3,0, .45},
        {0,5, .29},
        {5,4, .21},
        {1,4, .32},
        {4,2, .32},
        {5,1, .29}
    }; // digraph1.jpg

    SparseMultiGraph graph(vertexNumber, true);  // directed true

    for (auto &edge: edges)
        graph.insert(&edge);

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_graphviz_writer2.dot", graph);

    return 0;
}
