#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL_tree.h"
int DefaultComp1(void *a, void *b);
int main()
{

    struct AVL_Tree *tree = AVL_Tree_init(4,4);

    //tree->SetKeyComp(tree, DefaultComp1);
    printf("Hello world!\n");

    srand(time(NULL));
    clock_t start, finish;
    int a = 300;
    int b = 30;
    double sum = 0.0;


    for(a = 1 ; a <= 10000000 ; a++)
    {
        int x = rand()%10000;
        int y = rand()%1000;
        x = x*1000+y;
        start = clock();
        tree->Insert(tree, &x,&x);
        finish = clock();

        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        //if (tmp == 0)
        //    printf("not found %d\n",a);
    }
    printf("%lf\n",sum);
    for(a = 1 ; a <= 10000000 ; a++)
    {
        int x = rand()%10000;
        int y = rand()%1000;
        x = x*1000+y;
        start = clock();
        tree->Delete(tree, &x);

        //int tmp = tree->IsFound(tree, &x);
        finish = clock();
        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
      //  if (tmp != 0)
      //      printf("???? %d\n",x);
    }
    printf("%lf\n",sum);
    //tree->PrintNodes(tree);
    return 0;
}

int DefaultComp1(void *a, void *b)
{
    int diff = *(int*)a - *(int*)b;
    if (diff < 0)
        return -1;
    if (diff > 0 )
        return 1;
    return 0;
}

