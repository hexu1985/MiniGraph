/** \example normal/digraph_ts/sample_digraph_ts2.cpp
 * This is an example of how to use the DigraphTS class.
 */
#include <vector>
#include <map>
#include <sstream>
#include "mini_graph.hpp"

using namespace std;
using namespace mini_graph::normal;

int main()
{
    int vertexNumber = 13;
    vector<Edge> edges = {
        {0,5}, {0,3}, {3,5}, {0,1}, {0,2},
        {2,3}, {3,4}, {0,6}, {6,4}, {7,6},
        {8,7}, {6,9}, {4,9}, {9,10}, {9,11}, 
        {9,12}, {11,12}
    };  // digraph2.jpg

    DenseGraph graph(vertexNumber, true);  // directed true

    for (auto edge: edges)
        graph.insert(edge);

    DigraphTS<DenseGraph> ts(graph);
    auto tsI = ts.sort();    // 结果可以参考digraph2-topological-order.jpg

    std::map<int, int> v2tsImap;
    int n = tsI.size();
    for (int i = 0; i < n; i++) {
        v2tsImap[tsI[i]] = i+1;
    }

    GraphvizWriter::AttributesForLambda attributes;
    attributes.get_vertex_attribute =
        [&](int v) -> std::string {
            std::ostringstream os;
            os << "[label=\"" << v << "("
                << v2tsImap[v] << ")\"]";
            return os.str();
        };

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph, attributes);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_digraph_ts2.dot", graph, attributes);

    return 0;
}
