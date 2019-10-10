/** \example weight/sample_dijkstra_spt2.cpp
 * This is an example of how to use the DijkstraSPT2 class.
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

    for (auto &edge: edges)
        graph.insert(&edge);

    DijkstraSPT2<SparseMultiGraph> spt(graph, 0);
    for (int i = 0; i < graph.vertexCount(); i++) {	// output对应:digraph1-spt-a.jpg, digraph1-spt-b.jpg
        cout << i << ", dist: " << spt.dist(i) << ", path: "; 
        for (auto v: spt.path(i))
            cout << v << "->"; 
        cout << i;
        cout << endl;
    }

    return 0;
}
