/** \example normal/sample_graphviz_writer2.cpp
 * This is an example of how to use the GraphvizWriter class.
 */
#include <vector>
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

    cout << "insert edges\n";
    for (auto edge: edges)
        graph.insert(edge);

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_graphviz_writer2.dot", graph);

    return 0;
}
