/** \example sample_dijkstra_spt1.cpp
 * This is an example of how to use the DijkstraSPT class.
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

    for (auto &edge: edges)
        graph.insert(&edge);

    DijkstraSPT<SparseMultiGraph> spt(graph, 0);
    for (int i = 0; i < graph.vertexCount(); i++) {	// output对应:digraph1-spt-a.jpg, digraph1-spt-b.jpg
        cout << i << ", dist: " << spt.dist(i) << ", path: "; 
        print(spt.path(i));
        cout << endl;
    }

    return 0;
}
