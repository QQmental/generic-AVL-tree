# generic-AVL-tree
generic AVL tree implented in c  
default key comparator is for int  
you can use 'SetKeyComp' to set up your own comparator,
int Comp(a, b): return -1 if a < b, 0 if a == b, 1 if a > b  
use IsFound to search for data with a given key  
FoundNodeData : not NULL if the key exists in your map. it's a pointer to the data
