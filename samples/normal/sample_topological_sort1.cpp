/** \example sample_dense_graph2.cpp
 * This is an example of how to use the DenseGraph class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::normal;

int main()
{
    int vertexNumber = 13;
    vector<Edge> edges = {
        {0,5}, {0,3}, {3,5}, {0,1}, {0,2},
        {2,3}, {3,4}, {0,6}, {6,4}, {7,6},
        {8,7}, {6,9}, {4,9}, {9,10}, {9,11}, 
        {9,12}, {11,12}
    };  // digraph2.jpg

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

    TopologicalSort<DenseGraph> ts(graph);
    auto tsI = ts.getTopologicalOrder();

    cout << "Topological Order of Graph:\n";
    for (auto v: tsI)
        cout << v << ' '; 
    cout << endl;

    return 0;
}
