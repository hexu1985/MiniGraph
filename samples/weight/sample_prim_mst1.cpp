/** \example sample_prim_mst1.cpp
 * This is an example of how to use the PrimMST class.
 */
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::weight;

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

    for (auto &edge: edges)
        graph.insert(&edge);

    cout << endl;

    PrimMST<DenseGraph> mst(graph);
    mst.search();

    cout << "Prim's MST edges:\n";
    for (auto edge: mst.getTreeEdges()) {
		if (edge)
			cout << edge->u() << '-' << edge->v() << ": " << edge->weight() << '\n';
    }

    return 0;
}
