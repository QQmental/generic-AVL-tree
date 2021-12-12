#include <string.h>
#include<stdio.h>
#include"AVL_tree.h"
//#include"AVL_tree_algo.h"

#define _SELF ((_AVL_Tree*)self)
#define COPYDATA(node, src)\
    memcpy((void*)(((char*)node)+src##_offset),src, _SELF-> src##_size);

struct AVL_node
{
    struct AVL_node *chd[2];
    unsigned char height;
};
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
//typedef int(*Comp)(void*, void*);
AVL_Tree *AVL_Tree_init(size_t key_size, size_t data_size);

static int IsFound(AVL_Tree *self, void *key);
static int _IsFound(AVL_Tree *self, AVL_node *node ,void *key);

static int Insert(AVL_Tree *self, void *key, void *data);
static AVL_Tree *_Insert(AVL_Tree *self, AVL_node *node ,void *key);

static int Delete(AVL_Tree *self, void *key);
static AVL_node *_Delete(AVL_node *root, void *key);

static void SetKeyComp(AVL_Tree *self, int(*cmp)(void*, void*));
static int DefaultComp(void *a, void *b);

static void traverse(AVL_Tree *self);
static void _traverse(AVL_node *node);

static inline AVL_node *Rotate(AVL_node *node, int dir);

static void DefaultKeyDtor(void *key);
static void DefaultDataDtor(void *data);

static void SetKeyDestroy(AVL_Tree *self, void(*)(void*));
static void SetDataDestroy(AVL_Tree *self, void(*)(void*));




static void traverse(AVL_Tree *self)
{
    _traverse(_SELF->root);
}

static void _traverse(AVL_node *node)
{
    if (!node)
        return ;

    _traverse(node->chd[0]);
     printf("%d %d\n",*(int*)(((char*)node)+sizeof(AVL_node)),node->height);
    _traverse(node->chd[1]);
    return;
}



static inline int GetHeight(AVL_node *node)
{
    if (node == NULL)
        return 0 ;
    return node->height;
}
static inline int MAX(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}
static inline int IsImbalanced(AVL_node *node)
{
    int L = GetHeight(node->chd[0]);
    int R = GetHeight(node->chd[1]);
    if (L-R > 1 || L-R < -1)
        return 1;
    return 0;
}

static inline void UpDateHeight(AVL_node *node)
{
    int LeftHeight = GetHeight((node)->chd[0]),
        RightHeight = GetHeight((node)->chd[1]);
    node->height = 1+ MAX(LeftHeight, RightHeight);
}

AVL_Tree *AVL_Tree_init(size_t key_size, size_t data_size)
{
    AVL_Tree *tree  = (AVL_Tree*)malloc(sizeof(_AVL_Tree));

    tree->IsFound = IsFound;
    tree->Insert = Insert;
    tree->Delete = Delete;
    tree->KeyComp = DefaultComp;

    tree->FoundNodeData = NULL;
    tree->PrintNodes = traverse;
    tree->SetKeyComp = SetKeyComp;

    tree->KeyDestroy = DefaultKeyDtor;
    tree->DataDestroy = DefaultDataDtor;

    tree->DefaultKeyDtor = DefaultKeyDtor;
    tree->DefaultDataDtor = DefaultDataDtor;

    tree->SetKeyDestroy = SetKeyDestroy;
    tree->SetDataDestroy = SetDataDestroy;
    ((_AVL_Tree*) tree)->key_size = key_size;
    ((_AVL_Tree*) tree)->data_size = data_size;
    ((_AVL_Tree*) tree)->root = NULL;
    ((_AVL_Tree*) tree)->finished = 0;
    ((_AVL_Tree*) tree)->private_cache = NULL;
    return tree;
};

static int IsFound(AVL_Tree *self, void *key)
{
    return _IsFound(self, (_SELF->root), key);
}
static int _IsFound(AVL_Tree *self, AVL_node *node, void *key)
{
    if (!node)
        return 0;

    size_t key_offset = sizeof(AVL_node);
    size_t data_offset = key_offset + _SELF->key_size;

    int cmp = self->KeyComp(key, (void*)(((char*)node)+key_offset));

    if (cmp == 0)
    {
        self->FoundNodeData = (void*)(((char*)node)+data_offset);
        return 1 ;
    }
    return _IsFound(self, (node)->chd[cmp > 0], key);
}

static int Insert(AVL_Tree *self, void *key, void *data)
{
    _SELF->root = _Insert(self, _SELF->root, key);

    size_t data_offset = sizeof(AVL_node) + _SELF->key_size;
    memcpy(_SELF->private_cache, data, _SELF->data_size);
    _SELF->private_cache = NULL;

    _SELF->finished = 0;
    return 0;
}
static AVL_Tree *_Insert(AVL_Tree *self, AVL_node *node, void *key)
{
    size_t key_offset = sizeof(AVL_node);
    size_t data_offset = key_offset + _SELF->key_size;
    if (node == NULL)
    {
        node = (AVL_node*)malloc(sizeof(AVL_node)+_SELF->key_size+_SELF->data_size);
        node->height = 1;
        node->chd[0] = node->chd[1] = NULL;

        COPYDATA(node, key);

        _SELF->private_cache = (void*)(((char*)node)+data_offset);
        return node ;
    }

    int cmp = self->KeyComp(key, (void*)(((char*)node)+key_offset));

    if (cmp == 0)
    {
        _SELF->private_cache = (void*)(((char*)node)+data_offset);
        return node;
    }

    (node)->chd[cmp > 0] = _Insert(self, ((node)->chd[cmp > 0]), key);

    if (_SELF->finished)
        return node;

    if (IsImbalanced(node))
    {
        //adjust...
        void *ChildKey = (void*)(((char*)node->chd[cmp >0])+key_offset);
        int Childcmp = self->KeyComp(key, ChildKey);
        if (Childcmp != cmp)
            node->chd[cmp > 0] = Rotate(node->chd[cmp > 0], Childcmp > 0);
        node = Rotate(node, cmp > 0);
        _SELF->finished = 1;
    }
    else
        UpDateHeight(node);

    return node;
}

static int Delete(AVL_Tree *self, void *key)
{
    _SELF->root = _Delete(_SELF->root, key);

    if (_SELF->private_cache == NULL)//the key is not found, do nothing
        return 0;
    else//we found it, and then release memory
    {
        size_t key_offset = sizeof(AVL_node);
        size_t data_offset = key_offset + _SELF->key_size;
        self->KeyDestroy((void*)((char*)_SELF->private_cache+key_offset));
        self->DataDestroy((void*)((char*)_SELF->private_cache+data_offset));
        free(_SELF->private_cache);
        _SELF->private_cache = NULL;
        return 1 ;
    }
}


static AVL_node *_Delete(AVL_node *root, void *key)
{

    return NULL;
}



static inline AVL_node *Rotate(AVL_node *node, int dir)
{
    AVL_node *Child = node->chd[dir];
    AVL_node *GrandChild = Child->chd[!dir];

    node->chd[dir] = GrandChild ;
    Child->chd[!dir] = node;

    UpDateHeight(node);
    UpDateHeight(Child);


    return Child;
}
static int DefaultComp(void *a, void *b)
{
    int diff = *(int*)a - *(int*)b;
    if (diff < 0)
        return -1;
    if (diff > 0 )
        return 1;
    return 0;
}
static void SetKeyComp(AVL_Tree *self, int(*cmp)(void*, void*))
{
    self->KeyComp = cmp;
}


static void DefaultKeyDtor(void *key){return ;/* do nothing*/}
static void DefaultDataDtor(void *data){return ;/* do nothing*/}

static void SetKeyDestroy(AVL_Tree *self, void (*k_dtor)(void*)){self->SetKeyDestroy = k_dtor;}
static void SetDataDestroy(AVL_Tree *self, void (*d_dtor)(void*)){self->SetDataDestroy = d_dtor;}


