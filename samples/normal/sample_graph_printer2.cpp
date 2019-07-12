/** \example normal/sample_graph_printer2.cpp
 * This is an example of how to use the GraphPrinter class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::normal;

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}}; // graph1.jpg

    SparseMultiGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

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
