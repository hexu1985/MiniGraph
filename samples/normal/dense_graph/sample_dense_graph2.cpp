/** \example normal/dense_graph/sample_dense_graph2.cpp
 * This is an example of how to use the DenseGraph class.
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

    DenseGraph graph(vertexNumber, true);  // directed true

    cout << "insert edges\n";
    for (auto edge: edges)
        graph.insert(edge);

    // show edges
    cout << graph.edgeCount() << " edges in graph" << endl;

    // show adjLists
    cout << "-----------------show adjLists of Graph--------------------\n";
    GraphPrinter::showAdjLists(graph);
    cout << endl;

    // show adjMatrix
    cout << "-----------------show adjMatrix of Graph--------------------\n";
    GraphPrinter::showAdjMatrix(graph);
    cout << endl;

    cout << "remove edges\n";
    for (auto edge: mini_graph::normal::edges(graph))
        graph.remove(edge);

    // show edges
    cout << graph.edgeCount() << " edges in graph" << endl;

    // show adjLists
    cout << "-----------------show adjLists of Graph--------------------\n";
    GraphPrinter::showAdjLists(graph);
    cout << endl;

    // show adjMatrix
    cout << "-----------------show adjMatrix of Graph--------------------\n";
    GraphPrinter::showAdjMatrix(graph);
    cout << endl;

    return 0;
}
