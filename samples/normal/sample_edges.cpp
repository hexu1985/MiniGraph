#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::normal;

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}}; // graph1.jpg

    DenseGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    // show edges
    cout << graph.edgeCount() << " edges in graph" << endl;
    cout << "there are:\n";

    for (auto &edge: MiniGraph::normal::edges(graph))
        cout << edge.u << "-" << edge.v << '\n';

    return 0;
}

