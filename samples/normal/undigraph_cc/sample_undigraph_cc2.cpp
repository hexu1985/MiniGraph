/** \example normal/undigraph_cc/sample_undigraph_cc2.cpp
 * This is an example of how to use the UndigraphCC class.
 */
#include <iostream>
#include <iomanip>
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
        {10,6}, {10,7}, {10,2}, {7,2}, {2,12}, {6,12}, {3,12}, {5,12}, 
        {11,8}, 
        {9,0}, {9,1}, {0,1}, {1,4}}; // graph2.jpg

    SparseMultiGraph graph(vertexNumber, false);  // directed false
    for (auto edge: edges)
        graph.insert(edge);

    UndigraphCC<SparseMultiGraph> cc(graph);
    cc.search();

    // 将属于同一连通分量的顶点索引放在一起
    std::map<int, std::vector<int>> cc2v_map;
    for (int v = 0; v < graph.vertexCount(); v++)
        cc2v_map[cc.getCCNumber(v)].push_back(v);

    // 将一个连通分量作为一个subgraph
    GraphvizWriter::AttributesForLambda attributes;
    attributes.get_additional_attributes = 
        [&]() -> std::string {
            std::ostringstream os;
            for (auto &item: cc2v_map) {
                os << "\t"
                    << "subgraph cluster" << item.first << " {\n";
                for (int v: item.second) {
                    os << "\t\t" << v << ";\n";
                }
                os << "\t}\n";
            }
            return os.str();
        };

    // show dot
    cout << "-----------------show dot of Graph--------------------\n";
    GraphvizWriter::writeDot(graph, attributes);
    cout << endl;
    GraphvizWriter::writeDotFile("sample_undigraph_cc2.dot", graph, attributes);

    return 0;
}

