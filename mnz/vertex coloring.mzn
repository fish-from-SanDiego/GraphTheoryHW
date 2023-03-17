int: n;
set of int: NODES = 1..n;
array[NODES, NODES] of int: adj_matrix;
set of int: COLORS = NODES;
array[NODES] of var COLORS: color;
var NODES: colors_num;

constraint forall (i in NODES, j in NODES) (
    adj_matrix[i,j] = 1 -> color[i] != color[j]
);

constraint forall (i in COLORS) (
    color[i] <= colors_num
);

solve minimize colors_num;

output ["Minimum(" ++show(colors_num) ++ ") vertex coloring:\n"] ++[ show(i) ++ " " ++ show(color[i]) ++ "\n"| i in COLORS];