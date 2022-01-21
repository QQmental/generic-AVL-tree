#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "AVL_tree.h"
int DefaultComp1(void *a, void *b);
typedef struct dimension dimension;
typedef struct dimension
{
    int x, y, z;
};

typedef struct BOX
{
    dimension vec;
    char *name;
};
int Comp2(void *a, void *b);
int main()
{
    struct AVL_Tree *tree = AVL_Tree_init(sizeof(int),sizeof(int));

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
        int y = rand()%10000;
        x = x*10000+y;
        start = clock();
        tree->Insert(tree, &x,&x);
        finish = clock();

        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        if (a%1000000 == 0)
            srand(time(NULL));
        //if (tmp == 0)
        //    printf("not found %d\n",a);
    }
    printf("%lf\n",sum);
    for(a = 1 ; a <= 10000000 ; a++)
    {
        int x = rand()%10000;
        int y = rand()%10000;
        x = x*10000+y;
        start = clock();
        tree->Delete(tree, &x);

        //int tmp = tree->IsFound(tree, &x);
        finish = clock();
        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        if (a%1000000 == 0)
            srand(time(NULL));
      //  if (tmp != 0)
      //      printf("???? %d\n",x);
    }
    printf("%lf\n",sum);
    //tree->PrintNodes(tree);

/*
    struct AVL_Tree *tree = AVL_Tree_init(sizeof(dimension), sizeof(char*));
    tree->SetKeyComp(tree, Comp2);
    int a;
    for(a = 1 ; a <= 10 ; a++)
    {
        int x = rand()%10000;
        int y = rand()%10000;
        int z = rand()%10000;
        dimension tmp ={x,y,z};
        char *n;
        start = clock();
        tree->Insert(tree, &dimension,&n);
        finish = clock();

        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        //if (tmp == 0)
        //    printf("not found %d\n",a);
    }



*/
    return 0;
}

int Comp2(void *a, void *b)
{
    dimension *fst = (dimension*)a, *snd = (dimension*)b;
    if (fst->x > snd->x)
        return 1;
    if (fst->x < snd->x)
        return -1;

    if (fst->y > snd->y)
        return 1;
    if (fst->y < snd->y)
        return -1;

    if (fst->z > snd->z)
        return 1;
    if (fst->z < snd->z)
        return -1;
    return 0;
}

