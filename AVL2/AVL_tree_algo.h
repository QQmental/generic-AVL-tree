#ifndef AVL_TREE_ALGO_H_INCLUDED
#define AVL_TREE_ALGO_H_INCLUDED

struct AVL_node
{
    struct AVL_node *chd[2];
    int height;
};

static int _IsFound(AVL_Tree *self, AVL_node *node ,void *key);

static AVL_Tree *_Insert(AVL_Tree *self, AVL_node *node ,void *key);

static int DefaultComp(void *a, void *b);

static void _traverse(AVL_node *node);
static AVL_node *Rotate(AVL_node *node, int dir);


#endif // AVL_TREE_ALGO_H_INCLUDED
