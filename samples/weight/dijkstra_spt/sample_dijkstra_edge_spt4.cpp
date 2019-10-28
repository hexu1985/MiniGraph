/** \example weight/sample_dijkstra_edge_spt2.cpp
 * This is an example of how to use the DijkstraEdgeSPT class.
 */
#include <vector>
#include <set>
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
    GraphvizWriter::writeDotFile("sample_dijkstra_edge_spt4.dot", graph, attributes);

    return 0;
}
