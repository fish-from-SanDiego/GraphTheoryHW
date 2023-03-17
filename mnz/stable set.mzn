
int: n; 
set of int: NODES = 1..n;
array[NODES, NODES] of int: adj_matrix;


array[NODES] of var bool: used;

var int: set_size = sum(i in NODES) (used[i]);

constraint forall(i, j in NODES where adj_matrix[i, j] = 1) (not(used[i] /\ used[j]));

solve maximize set_size;

output [show(set_size) ++ "\n"] ++  [show(i) ++ " " | i in NODES where fix(used[i]) = 1];