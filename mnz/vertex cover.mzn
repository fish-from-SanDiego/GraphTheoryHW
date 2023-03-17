int: E;
int: V;
set of int: EDGES = 1..E;
set of int: NODES = 1..V;
array[EDGES, 1..2] of int: edges;


array[NODES] of var bool: used;

constraint forall (i in EDGES)(
    used[edges[i,1]] \/ used[edges[i,2]]
);

solve minimize count(i in NODES)(used[i]);

output["Minimum(" ++ show(count(i in NODES)(used[i])) ++ ") vertex cover:\n"] ++ 
[show(i) ++ " " | i in NODES where fix(used[i])];