make sample_edge_dfs2
./sample_edge_dfs2
sed -i 's/graph/di&/g' sample_edge_dfs2.dot
sed -i 's/\(.*\)--\(.*\);/\1->\2[dir=none];/g' sample_edge_dfs2.dot
dot sample_edge_dfs2.dot -T png -o sample_edge_dfs2.png
