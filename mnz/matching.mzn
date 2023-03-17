int: n; 
set of int: EDGES = 1..n;
array[EDGES, 1..2] of int: edges;
array[EDGES] of var bool: used;

constraint sum(i in EDGES)(used[i]) <= n div 2;

constraint forall(i, j in EDGES where i != j) (
 (used[i] /\ used[j]) -> not (edges[i,1] == edges[j,1] \/ edges[i,1] == edges[j,2] \/
   edges[i,2] == edges[j,1] \/ edges[i,2] == edges[j,2])
);


solve maximize sum(i in EDGES)(used[i]);

output["Maximum(" ++ show(sum(i in EDGES)(used[i])) ++ ") matching:\n"] ++
[ show(edges[i,1]) ++ "\t" ++ show(edges[i,2]) ++ "\n" | i in EDGES where fix(used[i])];