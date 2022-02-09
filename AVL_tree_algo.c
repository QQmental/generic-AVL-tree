#include<stdlib.h>
#include<stdio.h>
#include"AVL_tree_algo.h"
#define _SELF ((_AVL_Tree*)self)
#define COPYDATA(node, src)\
    memcpy((void*)(((char*)node)+src##_offset),src, _SELF-> src##_size);


typedef struct AVL_Tree AVL_Tree;
typedef struct _AVL_Tree _AVL_Tree;
typedef struct AVL_node AVL_node;

static inline int GetHeight(AVL_node *node);
static inline int MAX(int a, int b);
static inline int IsImbalanced(AVL_node *node);
static inline void UpDateHeight(AVL_node *node);


static inline AVL_node *Rotate(AVL_node *node, int dir);


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

int AVL_IsFound_algo(AVL_Tree *self, AVL_node *node, void *key)
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
    return AVL_IsFound_algo(self, (node)->chd[cmp > 0], key);
}



AVL_node *AVL_Insert_algo(AVL_Tree *self, AVL_node *node, void *key)
{
    size_t key_offset = sizeof(AVL_node);
    size_t data_offset = key_offset + _SELF->key_size;
    if (node == NULL)
    {
        node = (AVL_node*)malloc(sizeof(AVL_node)+_SELF->key_size+_SELF->data_size);
        node->height = 1;
        node->chd[0] = node->chd[1] = NULL;

        COPYDATA(node, key);
        /*memcpy((void*)(((char*)*node)+key_offset),key, _SELF->key_size);*/
        _SELF->private_cache = (void*)(((char*)node)+data_offset);
        return node ;
    }

    int cmp = self->KeyComp(key, (void*)(((char*)node)+key_offset));

    if (cmp == 0)
    {
        _SELF->private_cache = (void*)(((char*)node)+data_offset);
        return node;
    }
    unsigned char nodeheight = node->height;
    (node)->chd[cmp > 0] = AVL_Insert_algo(self, ((node)->chd[cmp > 0]), key);

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
    }
    else
        UpDateHeight(node);

    if (nodeheight == node->height)
        _SELF->finished = 1;
    return node;
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
AVL_node *AVL_Delete_algo(AVL_Tree *self, AVL_node *node, void *key)
{
    if (node == NULL)
        return NULL;

    size_t key_offset = sizeof(AVL_node);
    size_t data_offset = key_offset + _SELF->key_size;
    int cmp = self->KeyComp(key, (void*)(((char*)node)+key_offset));
    if (cmp == 0)
    {
        if (node->chd[0]  == NULL || node->chd[1] == NULL)
        {
            _SELF->private_cache = node;

            if (node->chd[0])
                return node->chd[0];
            return node->chd[1];
        }
        else
        {

            AVL_node *tmp = node->chd[0];
            while(tmp->chd[1])
                tmp = tmp->chd[1];
            node->chd[0] = AVL_Delete_algo(self, node->chd[0], (void*)(((char*)tmp)+key_offset));

            tmp->chd[0] = node->chd[0];
            tmp->chd[1] = node->chd[1];

            if (IsImbalanced(tmp))
            {
                if (GetHeight(node->chd[!(cmp > 0)]->chd[!(cmp > 0)])
                    < GetHeight(node->chd[!(cmp > 0)]->chd[(cmp > 0)]))
                    tmp->chd[!(cmp > 0)] = Rotate(tmp->chd[!(cmp > 0)], cmp > 0);

                tmp = Rotate(tmp, !(cmp > 0));
            }
            else
                UpDateHeight(tmp);
            _SELF->private_cache = node;
            return tmp;
        }
    }
    unsigned char nodeheight = node->height;
    node->chd[cmp > 0] = AVL_Delete_algo(self, node->chd[cmp > 0], key);
    if (_SELF->finished)
        return node;


    if (IsImbalanced(node))
    {
        if (GetHeight(node->chd[!(cmp > 0)]->chd[!(cmp > 0)])
            < GetHeight(node->chd[!(cmp > 0)]->chd[(cmp > 0)]))
            node->chd[!(cmp > 0)] = Rotate(node->chd[!(cmp > 0)], cmp > 0);

        node = Rotate(node, !(cmp > 0));
    }
    else
        UpDateHeight(node);

    if (nodeheight == node->height)
        _SELF->finished = 1;
    return node;
}

void AVL_traverse_algo(AVL_Tree *self, AVL_node *node)
{
    if (!node)
        return ;
    size_t key_offset = sizeof(AVL_node);
    size_t data_offset = key_offset + _SELF->key_size;
    AVL_traverse_algo(self, node->chd[0]);
    self->PrintNode((void*)((char*)node + key_offset), (void*)((char*)node + data_offset));
    AVL_traverse_algo(self, node->chd[1]);
    return;
}
