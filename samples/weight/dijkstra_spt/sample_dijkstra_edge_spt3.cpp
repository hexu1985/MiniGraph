/** \example weight/sample_dijkstra_edge_spt3.cpp
 * This is an example of how to use the DijkstraEdgeSPT class.
 */
#include <vector>
#include <set>
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

    DijkstraEdgeSPT<SparseMultiGraph> spt(graph, 0);
    std::set<std::pair<int, int>> tree_set;
    for (auto e: spt.tree()) {
        if (e) {
            tree_set.emplace(e->u(), e->v());
        }
    }

    GraphvizWriter::AttributesForLambda attributes;
    attributes.get_vertex_attribute =
        [&](int v) -> std::string {
            std::ostringstream os;
            os << "[label=\"" << v << "("
                << spt.dist(v) << ")\"]";
            return os.str();
        };

    attributes.get_edge_attribute = 
        [&](Edge *e) -> std::string {
            std::ostringstream os;
            os << "[label=\"" << e->weight() << "\"";
            if (tree_set.find(std::make_pair(e->u(), e->v())) != tree_set.end())
                os << ", color = red";
            os << "]";
            return os.str();
        };

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph, attributes);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_dijkstra_edge_spt3.dot", graph, attributes);

    return 0;
}
