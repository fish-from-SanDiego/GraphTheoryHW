int: E;
int: V;
set of int: EDGES = 1..E;
set of int: NODES = 1..V;
array[EDGES, 1..2] of int: edges;


array[EDGES] of var bool: used;


constraint forall (i in NODES)(
    count(j in EDGES where edges[j,1] == i \/ edges[j,2] == i)(
    used[j]) >= 1
);

solve minimize count(j in EDGES)(used[j]);

output["Minimum(" ++ show(count(i in EDGES)(used[i])) ++ ") edge cover:\n"] ++ 
[show(edges[i,1]) ++ " " ++ show(edges[i,2]) ++ "\n" | i in EDGES where fix(used[i])];