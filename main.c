#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL_tree.h"
int main()
{

    struct AVL_Tree *tree ;
    tree = AVL_Tree_init(sizeof(int), sizeof(int));
    //printf("%d %d %p\n",sizeof(tree->Delete),tree->FoundNodeData,&(tree->FoundNodeData));

    printf("Hello world!\n");


    clock_t start, finish;
    int a = 300;
    int b = 30;
    double sum = 0.0;


    start = clock();
    for(a = 1 ; a <= 10000000 ; a++)
    {
        //start = clock();
        //a = rand()%100000;
        tree->Insert(tree, &a, &b);
        //finish = clock();
        //sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
    }
    finish = clock();
    printf("%lf\n",(finish - start) / (double)CLOCKS_PER_SEC);
    start = clock();
    for(a = 1 ; a <= 10000000 ; a++)
    {
        int tmp = tree->IsFound(tree, &a);
        //if (tmp == 0)
        //    printf("not found %d\n",a);
    }
    finish = clock();
    printf("%lf\n",(finish - start) / (double)CLOCKS_PER_SEC);


    return 0;
}
