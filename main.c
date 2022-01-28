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
int main()
{
    struct AVL_Tree *tree = AVL_Tree_init(sizeof(dimension), sizeof(char*));
    tree->SetKeyComp(tree, Comp2);
    tree->PrintNode = print_node;
    tree->SetDataDestroy(tree, my_data_dtor);
    srand(time(NULL));
    clock_t start, finish;
    double sum =0.0;
    int a;
    for(a = 1 ; a <= 10 ; a++)
    {
        int x = rand()%3;
        int y = rand()%3;
        int z = rand()%3;
        dimension tmp ={x,y,z};
        printf("%d %d %d\n",x,y,z);
        char *n = (char*)malloc(4);
        n[0] = 'a' + x;
        n[1] = 'a' + y;
        n[2] = 'a' + z;
        start = clock();
        tree->Insert(tree, &tmp,&n);
        finish = clock();

        sum = sum+((finish - start) / (double)CLOCKS_PER_SEC);
        //if (tmp == 0)
        //    printf("not found %d\n",a);
    }
    printf("\n\n");
    tree->Traverse(tree);
    dimension d1 = {0,1,0};
    dimension d2 = {0,1,1};
    dimension d3 = {1,1,0};
    dimension d4 = {0,0,0};
    dimension d5 = {1,1,1};
    tree->Delete(tree, &d1);
    tree->Delete(tree, &d2);
    tree->Delete(tree, &d3);
    tree->Delete(tree, &d4);
    tree->Delete(tree, &d5);
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
    free(*(char**)data);
}
