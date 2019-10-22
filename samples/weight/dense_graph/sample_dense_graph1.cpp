/** \example weight/sample_dense_graph1.cpp
 * This is an example of how to use the DenseGraph class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::weight;

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {
        {0,6, .51}, 
        {0,1, .32}, 
        {0,2, .29}, 
        {4,3, .34}, 
        {5,3, .18}, 
        {7,4, .46},
        {5,4, .40}, 
        {0,5, .60}, 
        {6,4, .51}, 
        {7,0, .31}, 
        {7,6, .25},
        {7,1, .21} 
    }; // graph1.jpg

    DenseGraph graph(vertexNumber, false);  // directed false

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
