/** \example normal/dense_graph/sample_digraph_dfs1.cpp
 * This is an example of how to use the DigraphDFS class.
 */
#include <iostream>
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::normal;

int main()
{
    int vertexNumber = 13;
    vector<Edge> edges = {
        {4,2}, {2,3}, {3,2}, {0,6}, {0,1},
        {2,0}, {11,12}, {12,9}, {9,10}, {9,11},
        {8,9}, {10,12}, {4,11}, {4,3}, {3,5},
        {7,8}, {8,7}, {5,4}, {0,5}, {6,4},
        {6,9}, {7,6}};  // digraph1.jpg

    SparseMultiGraph graph(vertexNumber, true);  // directed true
    for (auto edge: edges)
        graph.insert(edge);

    DigraphDFS<SparseMultiGraph> dfs(graph);
    dfs.search();

    // 边类型结果应该和digraph1-trace.jpg一致
    for (auto edge: edges) {
        cout << edge.u << "-" << edge.v << ": " << dfs.getEdgeType(edge.u, edge.v) << '\n';
    }

    cout << endl;
    cout << "vertex| preOrder| postOrder" << endl;
    cout << "---------------------------" << endl;
    for (int v = 0; v < graph.vertexCount(); v++)
        cout << setw(6) << v << "| " 
            << setw(8) << dfs.getPreOrder(v) << "| "
            << setw(9) << dfs.getPostOrder(v) << endl;

    return 0;
}


