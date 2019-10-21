/** \example normal/dfs/sample_edge_dfs1.cpp
 * This is an example of how to use the EdgeDFS class.
 */
#include <iostream>
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::normal;

template <class Graph>
class MyEdgeDFS: public EdgeDFS<Graph> {
public:
    MyEdgeDFS(const Graph &graph): EdgeDFS<Graph>(graph) {}

private:
    void previsit(Edge e) override
    {
        cout << "entry " << e.v << endl;
    }

    void postvisit(Edge e) override
    {
        cout << "leave " << e.v << endl;
    }
};

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}}; // graph1.jpg

    DenseGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    MyEdgeDFS<DenseGraph> dfs(graph);
    dfs.search();    // output对应:graph1-dfs-a.jpg, graph1-dfs-b.jpg

    return 0;
}


