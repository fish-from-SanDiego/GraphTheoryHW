int: n;
set of int: NODES = 1..n;
array[NODES, NODES] of int: adj_matrix;
set of int: COLORS = 0..((n-1)*n div 2);
array[NODES, NODES] of var COLORS: color;
var COLORS: colors_num;

constraint forall (i in NODES, j in NODES) (
    color[i,j] = color[j,i]
);

constraint forall (i in NODES, j in NODES) (
    adj_matrix[i,j] = 0 <-> color[i,j]=0
);

constraint forall (i in NODES, j in NODES) (
    color[i, j] <= colors_num
);

constraint forall (i in NODES, j in NODES, k in NODES) (
    (adj_matrix[i,j] != 0 /\ adj_matrix[i,k] != 0 /\ j != k) -> (color[i,j] != color[i,k])
);

solve minimize colors_num;

output ["Minimum(" ++show(colors_num) ++") vertex coloring:\nbeg\tend\tcolor\n"] ++[ show(i) ++ "\t" ++ show(j) 
++ "\t" ++ show(color[i, j]) ++ "\n"| i in NODES, j in NODES where j > i /\ fix(color[i,j]) != 0];