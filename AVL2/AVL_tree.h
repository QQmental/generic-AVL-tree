#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED
#include <stdio.h>
#include "AVL_tree_algo.h"
#define AVL_Tree(tree, k_size, d_size)\
    struct AVL_Tree *tree ;\
    AVL_Tree_init(tree, k_size, d_size);
struct AVL_node
{
    struct AVL_node *chd[2];
    int height;
};

struct AVL_Tree
{
    int (*Insert)(struct AVL_Tree *self, void *key, void *data);
    int (*Delete)(struct AVL_Tree *self, void *key);
    int (*IsFound)(struct AVL_Tree *self, void *key);
    int (*KeyComp)(void *key1, void *key2);
    void (*SetKeyComp)(int(*)(void*, void*));
    void (*PrintNodes)(struct AVL_Tree *);
    void *FoundNodeData;
};

struct AVL_Tree* AVL_Tree_init(size_t key_size, size_t data_size);

static int IsFound(struct AVL_Tree *self, void *key);
static int _IsFound(struct AVL_Tree *self, struct AVL_node *node ,void *key);
static int Insert(struct AVL_Tree *self, void *key, void *data);
static struct AVL_Tree *_Insert(struct AVL_Tree *self, struct AVL_node *node ,void *key);
static int DefaultComp(void *a, void *b);
static void traverse(struct AVL_Tree *self);
static void _traverse(struct AVL_node *node);
static struct AVL_node *Rotate(struct AVL_node *node, int dir);
static void SetKeyComp(struct AVL_Tree *self, int(*cmp)(void*, void*));

#endif // AVL_TREE_H_INCLUDED
