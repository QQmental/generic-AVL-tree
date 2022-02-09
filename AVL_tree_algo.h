#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED
#include <stdio.h>
#include <assert.h>
#define AVL_Tree(tree, k_size, d_size)\
    struct AVL_Tree *tree ;\
    AVL_Tree_init(tree, k_size, d_size);

struct AVL_Tree
{
    int (*Insert)(struct AVL_Tree *self, void *key, void *data);
    int (*Delete)(struct AVL_Tree *self, void *key);
    int (*IsFound)(struct AVL_Tree *self, void *key);
    int (*KeyComp)(void *key1, void *key2);
    void (*SetKeyComp)(struct AVL_Tree *self, int(*)(void*, void*));
    void (*PrintNode)(void *, void *);
    void (*Traverse)(struct AVL_Tree *self);
    void *FoundNodeData;
    void (*KeyDestroy)(void *key);
    void (*DataDestroy)(void *data);

    void (*DefaultKeyDtor)(void *key);
    void (*DefaultDataDtor)(void *data);

    void (*SetKeyDestroy)(struct AVL_Tree *self, void(*)(void*));
    void (*SetDataDestroy)(struct AVL_Tree *self, void(*)(void*));

    void (*clean)(struct AVL_Tree *self);
};

struct AVL_Tree* AVL_Tree_init(size_t key_size, size_t data_size);



#endif // AVL_TREE_H_INCLUDED
