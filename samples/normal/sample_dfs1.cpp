#include <iostream>
#include <vector>
#include "mini_graph.hpp"

using namespace std;
using namespace MiniGraph::normal;

template <class Graph>
class MyDFS: public DFS<Graph> {
public:
    MyDFS(const Graph &graph): DFS<Graph>(graph) {}

private:
    void previsit(int v) override
    {
        cout << "entry " << v << endl;
    }

    void postvisit(int v) override
    {
        cout << "leave " << v << endl;
    }
};

int main()
{
    int vertexNumber = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}}; // graph1.jpg

    DenseGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    MyDFS<DenseGraph> dfs(graph);
    dfs.search();    // output对应:graph1-dfs-a.jpg, graph1-dfs-b.jpg

    return 0;
}


