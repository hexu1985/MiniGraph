/** \example weight/sample_sparse_multi_graph2.cpp
 * This is an example of how to use the SparseMultiGraph class.
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

    cout << "insert edges\n";
    for (auto &edge: edges)
        graph.insert(&edge);

    // show edges
    cout << graph.edgeCount() << " edges in graph" << endl;

    // show adjLists
    cout << "-----------------show adjLists of Graph--------------------\n";
    GraphPrinter::showAdjLists(graph);
    cout << endl;

    cout << "remove edges\n";
    for (auto edge: mini_graph::weight::edges(graph))
        graph.remove(edge);

    // show edges
    cout << graph.edgeCount() << " edges in graph" << endl;

    // show adjLists
    cout << "-----------------show adjLists of Graph--------------------\n";
    GraphPrinter::showAdjLists(graph);
    cout << endl;

    return 0;
}
