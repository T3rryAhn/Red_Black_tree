#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

static node_t NIL_NODE = {RBTREE_BLACK, -1, NULL, NULL, NULL};
static node_t *NIL = &NIL_NODE;
typedef enum
{
    LEFT,
    RIGHT
} position;

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    if (!p)
    {
        return NULL;
    }

    // 모든 트리는 같은 NIL 노드를 공유.
    p->nil = NIL;
    p->root = NIL;

    return p;
}

// 입력받은 노드로 부터 하위 노드를 전부 지우는 재귀 메서드
void free_node(node_t *node)
{
    if (node == NIL)
    {
        return;
    }
    free_node(node->right);
    free_node(node->left);

    free(node);
}

void delete_rbtree(rbtree *t)
{
    if (t != NULL)
    {
        free_node(t->root);
        free(t);
    }
}

void rbtree_left_rotate(rbtree *t, node_t *target_node)
{
    if (target_node == NIL || target_node->right == NIL)
    {
        return;
    }
    node_t *target_node_rChild = target_node->right;
    target_node->right = target_node_rChild->left;

    if (target_node_rChild->left != NIL)
    {
        target_node_rChild->left->parent = target_node;
    }
    target_node_rChild->parent = target_node->parent;
    if (target_node->parent == NIL)
    {
        t->root = target_node_rChild;
    }
    else if (target_node == target_node->parent->left)
    {
        target_node->parent->left = target_node_rChild;
    }
    else
    {
        target_node->parent->right = target_node_rChild;
    }
    target_node_rChild->left = target_node;
    target_node->parent = target_node_rChild;
}

void rbtree_right_rotate(rbtree *t, node_t *target_node)
{
    if (target_node == NIL || target_node->left == NIL)
    {
        return;
    }

    node_t *target_node_lChild = target_node->left;
    target_node->left = target_node_lChild->right;

    if (target_node_lChild->right != NIL)
    {
        target_node_lChild->right->parent = target_node;
    }
    target_node_lChild->parent = target_node->parent;
    if (target_node->parent == NIL)
    {
        t->root = target_node_lChild;
    }
    else if (target_node == target_node->parent->right)
    {
        target_node->parent->right = target_node_lChild;
    }
    else
    {
        target_node->parent->left = target_node_lChild;
    }

    target_node_lChild->right = target_node;
    target_node->parent = target_node_lChild;
}

void rbtree_insert_fixup(rbtree *t, node_t *target_node)
{

    while (target_node != t->root && target_node->parent->color == RBTREE_RED)
    {
        if (target_node->parent == target_node->parent->parent->left)
        {
            node_t *uncle = target_node->parent->parent->right;
            if (uncle->color == RBTREE_RED)
            {
                target_node->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                target_node = target_node->parent->parent;
            }
            else
            {
                if (target_node == target_node->parent->right)
                {
                    target_node = target_node->parent;
                    rbtree_left_rotate(t, target_node);
                }
                target_node->parent->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                rbtree_right_rotate(t, target_node->parent->parent);
            }
        }
        else
        {
            node_t *uncle = target_node->parent->parent->left;
            if (uncle->color == RBTREE_RED)
            {
                target_node->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                target_node = target_node->parent->parent;
            }
            else
            {
                if (target_node == target_node->parent->left)
                {
                    target_node = target_node->parent;
                    rbtree_right_rotate(t, target_node);
                }
                target_node->parent->color = RBTREE_BLACK;
                target_node->parent->parent->color = RBTREE_RED;
                rbtree_left_rotate(t, target_node->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *create_node(const key_t key)
{
    node_t *tempNode = malloc(sizeof(node_t));
    tempNode->color = RBTREE_RED;
    tempNode->key = key;
    tempNode->parent = NIL;
    tempNode->left = NIL;
    tempNode->right = NIL;

    return tempNode;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    node_t *node = t->root;
    node_t *parent = NIL;
    position child_position;

    while (node != NIL)
    {
        parent = node;
        if (node->key > key)
        {
            child_position = LEFT;
            node = node->left;
        }
        else
        {
            child_position = RIGHT;
            node = node->right;
        }
    }
    node_t *new_node = create_node(key);
    new_node->parent = parent;

    if (parent == NIL)
    {
        t->root = new_node;
    }
    else if (child_position == LEFT)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }

    rbtree_insert_fixup(t, new_node);
    return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    node_t *node = t->root;

    while (node != NIL)
    {
        if (node->key == key)
        {
            return node;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    node_t *node = t->root;
    while (node != NIL)
    {
        if (node->left != NIL)
        {
            node = node->left;
        }
        else
        {
            return node;
        }
    }

    return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
    node_t *node = t->root;
    while (node != NIL)
    {
        if (node->right != NIL)
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }

    return t->root;
}

// 노드를 이식 하는 함수. 하나의 노드를 다른 노드로 대체함.
void rbtree_transplant(rbtree *t, node_t *replace_node, node_t *new_node)
{
    if (replace_node->parent == NIL)
    {
        t->root = new_node;
    }
    else if (replace_node == replace_node->parent->left)
    {
        replace_node->parent->left = new_node;
    }
    else
    {
        replace_node->parent->right = new_node;
    }
    new_node->parent = replace_node->parent;
}

node_t *rbtree_sub_min(node_t *node)
{
    while (node != NIL)
    {
        if (node->left != NIL)
        {
            node = node->left;
        }
        else
        {
            return node;
        }
    }
    return node;
}

void rbtree_erase_fixup(rbtree *t, node_t *fixup_node)
{
    if (fixup_node == NIL)
    {
        return;
    }

    node_t *brother;

    while (fixup_node != t->root && fixup_node->color == RBTREE_BLACK)
    {
        if (fixup_node == fixup_node->parent->left)
        {
            brother = fixup_node->parent->left;
            if (brother->color == RBTREE_RED)
            {
                brother->color = RBTREE_BLACK;
                fixup_node->parent->color = RBTREE_RED;
                rbtree_left_rotate(t, fixup_node->parent);
                brother = fixup_node->parent->right;
            }
            if (brother->left->color == RBTREE_BLACK && brother->right->color == RBTREE_BLACK)
            {
                brother->color = RBTREE_RED;
                fixup_node = fixup_node->parent;
            }
            else if (brother->right->color == RBTREE_BLACK)
            {
                brother->left->color = RBTREE_BLACK;
                brother->color = RBTREE_RED;
                rbtree_right_rotate(t, brother);
                brother = fixup_node->parent->right;
            }
            brother->color = fixup_node->parent->color;
            fixup_node->parent->color = RBTREE_BLACK;
            rbtree_left_rotate(t, fixup_node->parent);
            fixup_node = t->root;
        }
        else
        {
            brother = fixup_node->parent->right;
            if (brother->color == RBTREE_RED)
            {
                brother->color = RBTREE_BLACK;
                fixup_node->parent->color = RBTREE_RED;
                rbtree_right_rotate(t, fixup_node->parent);
                brother = fixup_node->parent->left;
            }
            if (brother->right->color == RBTREE_BLACK && brother->left->color == RBTREE_BLACK)
            {
                brother->color = RBTREE_RED;
                fixup_node = fixup_node->parent;
            }
            else if (brother->left->color == RBTREE_BLACK)
            {
                brother->right->color = RBTREE_BLACK;
                brother->color = RBTREE_RED;
                rbtree_left_rotate(t, brother);
                brother = fixup_node->parent->left;
            }
            brother->color = fixup_node->parent->color;
            fixup_node->parent->color = RBTREE_BLACK;
            rbtree_right_rotate(t, fixup_node->parent);
            fixup_node = t->root;
        }
    }
    fixup_node->color = RBTREE_BLACK;
    t->root->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *target_node)
{
    node_t *replacement_node = target_node;
    color_t replacement_node_original_color = replacement_node->color;
    node_t *fixup_node;
    if (target_node->left == NIL)
    {
        fixup_node = target_node->right;
        rbtree_transplant(t, target_node, target_node->right);
    }
    else if (target_node->right == NIL)
    {
        fixup_node = target_node->left;
        rbtree_transplant(t, target_node, target_node->left);
    }
    else
    {
        replacement_node = rbtree_sub_min(target_node->right);
        replacement_node_original_color = replacement_node->color;
        fixup_node = replacement_node->right;
        if (replacement_node->parent == target_node)
        {
            fixup_node->parent = replacement_node;
        }
        else
        {
            rbtree_transplant(t, replacement_node, replacement_node->right);
            replacement_node->right = target_node->right;
            replacement_node->right->parent = replacement_node;
        }

        rbtree_transplant(t, target_node, replacement_node);
        replacement_node->left = target_node->left;
        replacement_node->left->parent = replacement_node;
        replacement_node->color = target_node->color;
    }
    if (replacement_node_original_color == RBTREE_BLACK)
    {
        rbtree_erase_fixup(t, fixup_node);
    }

    free(target_node);
    return 0;
}

void rbtree_inorder(node_t *node, key_t *arr, int *index)
{
    if (node == NIL)
    {
        return;
    }
    rbtree_inorder(node->left, arr, index);
    int key = node->key;
    arr[*index] = key;
    (*index)++;
    rbtree_inorder(node->right, arr, index);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    int index = 0;
    rbtree_inorder(t->root, arr, &index);

    return 0;
}
