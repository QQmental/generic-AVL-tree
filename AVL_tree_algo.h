#ifndef AVL_TREE_ALGO_H_INCLUDED
#define AVL_TREE_ALGO_H_INCLUDED
#include"AVL_tree.h"
#define _SELF ((_AVL_Tree*)self)
#define COPYDATA(node, src)\
    memcpy((void*)(((char*)node)+src##_offset),src, _SELF-> src##_size);
struct AVL_node
{
    struct AVL_node *chd[2];
    int height;
};
/*
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
*/
struct _AVL_Tree
{
    struct AVL_Tree tree;
    size_t key_size, data_size;
    struct AVL_node *root;
    int finished ;
    void *private_cache;
};
typedef struct AVL_Tree AVL_Tree;
typedef struct AVL_node AVL_node;
typedef struct _AVL_Tree _AVL_Tree;


int AVL_IsFound_algo(AVL_Tree *self, AVL_node *node ,void *key);

AVL_node *AVL_Insert_algo(AVL_Tree *self, AVL_node *node ,void *key);

void AVL_traverse_algo(AVL_Tree *self, AVL_node *node);



AVL_node *AVL_Delete_algo(AVL_Tree *self, AVL_node *node, void *key);
#endif // AVL_TREE_ALGO_H_INCLUDED