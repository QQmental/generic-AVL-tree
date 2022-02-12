output	:	main.c AVL_tree.o AVL_tree_algo.o
	gcc main.c AVL_tree.o AVL_tree_algo.o -o main

AVL_tree.o:AVL_tree.c AVL_tree.h
	gcc -c AVL_tree.c

AVL_tree_algo.o:AVL_tree_algo.c AVL_tree.h AVL_tree_algo.h
	gcc -c AVL_tree_algo.c

clean:del *.o main

