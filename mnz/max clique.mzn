int: n;
set of int: NODES = 1..n;
array[NODES, NODES] of int: adj_matrix;
array[NODES] of var bool: clique;


constraint forall(i in NODES, j in NODES where i != j)  (
  (clique[i] /\ clique[j]) -> adj_matrix[i,j] = 1
);

solve maximize sum(i in NODES)(clique[i]);

output["Maximum(" ++ show(sum(i in NODES)(clique[i])) ++ ") clique:\n"] ++ [ show(i) ++ " " | i in NODES where fix(clique[i])];