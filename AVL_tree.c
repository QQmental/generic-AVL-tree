#include <string.h>
#include<stdio.h>
#include"AVL_tree.h"
#include"AVL_tree_algo.h"




typedef struct AVL_Tree AVL_Tree;
typedef struct AVL_node AVL_node;

//typedef int(*Comp)(void*, void*);
AVL_Tree *AVL_Tree_init(size_t key_size, size_t data_size);

static int IsFound(AVL_Tree *self, void *key);


static int Insert(AVL_Tree *self, void *key, void *data);


static int Delete(AVL_Tree *self, void *key);


static void SetKeyComp(AVL_Tree *self, int(*cmp)(void*, void*));
static int DefaultComp(void *a, void *b);

static void traverse(AVL_Tree *self);

static void DefaultKeyDtor(void *key);
static void DefaultDataDtor(void *data);

static void SetKeyDestroy(AVL_Tree *self, void(*)(void*));
static void SetDataDestroy(AVL_Tree *self, void(*)(void*));

static void traverse(AVL_Tree *self)
{
    AVL_traverse_algo(_SELF->root);
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
    assert(self);
    return AVL_IsFound_algo(self, (_SELF->root), key);
}


static int Insert(AVL_Tree *self, void *key, void *data)
{
    assert(self);
    _SELF->root = AVL_Insert_algo(self, _SELF->root, key);

    size_t data_offset = sizeof(AVL_node) + _SELF->key_size;
    self->DataDestroy(_SELF->private_cache);
    memcpy(_SELF->private_cache, data, _SELF->data_size);

    _SELF->private_cache = NULL;

    _SELF->finished = 0;
    return 0;
}


static int Delete(AVL_Tree *self, void *key)
{
    assert(self);
    _SELF->private_cache = NULL;
    _SELF->root = AVL_Delete_algo(self, _SELF->root, key);
    _SELF->finished = 0;
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

static int DefaultComp(void *a, void *b)
{
    int diff = *(int*)a - *(int*)b;
    if (diff < 0)
        return -1;
    if (diff > 0 )
        return 1;
    return 0;
}

static void SetKeyComp(AVL_Tree *self, int(*cmp)(void*, void*)){assert(self);self->KeyComp = cmp;}

static void DefaultKeyDtor(void *key){return ;/* do nothing*/}
static void DefaultDataDtor(void *data){return ;/* do nothing*/}

static void SetKeyDestroy(AVL_Tree *self, void (*k_dtor)(void*)){assert(self);self->SetKeyDestroy = k_dtor;}
static void SetDataDestroy(AVL_Tree *self, void (*d_dtor)(void*)){assert(self);self->SetDataDestroy = d_dtor;}
