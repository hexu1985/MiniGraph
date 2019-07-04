/** \example sample_dijkstra_spt2.cpp
 * This is an example of how to use the DijkstraSPT2 class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::weight;

void print(const std::vector<Edge *> edges)
{
    for (auto edge: edges)
        cout << edge->u() << "-" << edge->v() << " ";
}

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
        cout << i << ", dist: " << spt.dist(i) << ", path: "; 
        print(spt.path(i));
        cout << endl;
    }

    return 0;
}
