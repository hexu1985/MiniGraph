/** \example weight/sample_dijkstra_spt3.cpp
 * This is an example of how to use the DijkstraSPT class.
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

    SparseMultiGraph graph(vertexNumber, false);  // directed false

    for (auto &edge: edges)
        graph.insert(&edge);

    DijkstraSPT<SparseMultiGraph> spt(graph, 0);
    for (int i = 0; i < graph.vertexCount(); i++) {
        cout << i << ", dist: " << spt.dist(i);
        auto path = spt.path(i);
        if (!path.empty()) {
            cout << ", path: "; 
            for (auto v: path)
                cout << v << "->"; 
            cout << i;
        }
        cout << endl;
    }

    return 0;
}
