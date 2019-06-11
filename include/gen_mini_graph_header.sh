#!/usr/bin/env bash

cat <<EOF > mini_graph.hpp
#ifndef MINI_GRAPH_INC
#define MINI_GRAPH_INC
EOF

find . -name "*.hpp" | grep -v 'mini_graph.hpp' | sed 's!^\./!!g' | \
while read line
do
    echo "#include \"$line\""
done >> mini_graph.hpp

cat <<EOF >> mini_graph.hpp
#endif
EOF
