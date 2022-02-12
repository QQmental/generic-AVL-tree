#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "AVL_tree.h"
int DefaultComp1(void *a, void *b);
typedef struct dimension dimension;
struct dimension
{
    int x, y, z;
};

typedef struct BOX
{
    dimension vec;
    char *name;
};
int Comp2(void *a, void *b);
void print_node(void *key, void *data);
void my_data_dtor(void *data);

dimension Setdimension(int x, int y, int z)
{
    dimension ret = {.x = x, .y = y, .z = z};
    return ret;
}



int main()
{

    struct AVL_Tree *tree = AVL_Tree_init(sizeof(int),sizeof(int));

    printf("Hello world!\n");

    srand(time(NULL));
    clock_t start, finish;
    int a ;
    int b ;
    double sum = 0.0;

    for(a = 1 ; a <= 10000000 ; a++)
    {
        int x = rand()%100000;
        int y = rand()%10000;
        x = x*10000+y;
        start = clock();
        tree->Insert(tree, &x,&a);
        finish = clock();

        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        if (a%1000000 == 0)
            srand(time(NULL));
    }
    printf("%lf\n",sum);
    for(a = 1 ; a <= 10000000 ; a++)
    {
        int x = rand()%100000;
        int y = rand()%10000;
        x = x*10000+y;
        start = clock();
        tree->Delete(tree, &x);

        //int tmp = tree->IsFound(tree, &x);
        finish = clock();
        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        if (a%1000000 == 0)
            srand(time(NULL));
    }
    printf("%lf\n",sum);

    tree->clean(tree);


    //AVL_Tree_init(key size, data size)
    tree = AVL_Tree_init(sizeof(dimension), sizeof(char*));
    tree->SetKeyComp(tree, Comp2);
    tree->PrintNode = print_node;
    tree->SetDataDestroy(tree, my_data_dtor);

    srand(time(NULL));
    sum =0.0;
    for(a = 1 ; a <= 10 ; a++)
    {
        int x = rand()%3;
        int y = rand()%3;
        int z = rand()%3;
        dimension tmp ={x,y,z};
        printf("insert <%d %d %d>\n",x,y,z);
        char *n = (char*)malloc(4);
        n[0] = 'a' + x;
        n[1] = 'a' + y;
        n[2] = 'a' + z;
        start = clock();
        tree->Insert(tree, &tmp,&n);
        finish = clock();

        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);

    }
    printf("\n\n");
    printf("traverse\n");
    tree->Traverse(tree);
    printf("After deleting somethings\n");
    dimension d1 ;
    d1 = Setdimension(0,1,0);
    tree->Delete(tree, &d1);

    d1 = Setdimension(0,1,1);
    tree->Delete(tree, &d1);

    d1 = Setdimension(1,1,0);
    tree->Delete(tree, &d1);

    d1 = Setdimension(0,0,0);
    tree->Delete(tree, &d1);

    d1 = Setdimension(1,1,1);
    tree->Delete(tree, &d1);

    d1 = Setdimension(0,1,2);
    if (tree->IsFound(tree, &d1))
        printf("we found <0,1,2 %s>\n",*(char**)tree->FoundNodeData);


    printf("\n");
    tree->Traverse(tree);

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

void print_node(void *key, void *data)
{
    printf("%d %d %d %s\n",((dimension*)key)->x, ((dimension*)key)->y, ((dimension*)key)->z, *(char**)data);
}

void my_data_dtor(void *data)
{
    //never call free(data)
    free(*(char**)data);
}

