#include <iostream>
#include <iomanip>
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::normal;

int main()
{
    int vertexNumber = 13;
    vector<Edge> edges = {
        {10,6}, {10,7}, {10,2}, {7,2}, {2,12}, {6,12}, {3,12}, {5,12}, 
        {11,8}, 
        {9,0}, {9,1}, {0,1}, {1,4}}; // graph2.jpg

    SparseMultiGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    ConnectedComponents<SparseMultiGraph> cc(graph);
    cc.search();

    cout << "there are " << graph.edgeCount() << " edges. " << endl;
    cout << "there are " << cc.count() << " connected components. " << endl;
    cout << endl;
    cout << "vertex| ccNum" << endl;
    cout << "-------------" << endl;
    for (int v = 0; v < graph.vertexCount(); v++)
        cout << setw(6) << v << "| " << setw(5) << cc.getCCNumber(v) << endl;

    cout << endl;

    return 0;
}



