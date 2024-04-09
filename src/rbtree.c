#include "rbtree.h"
#include <stdlib.h>

static  node_t NIL_NODE = { RBTREE_BLACK, -1, NULL, NULL, NULL};
static  node_t *NIL = &NIL_NODE;
typedef enum { LEFT, RIGHT } position;

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *) calloc(1, sizeof(rbtree));
    if (!p) { return NULL; }

    // 모든 트리는 같은 NIL 노드를 공유.
    p->nil = NIL;
    p->root = NIL;

    return p;
}

// 입력받은 노드로 부터 하위 노드를 전부 지우는 재귀 메서드
void free_node(node_t *node) {
    if (node == NIL) {
        return;
    }
    free_node(node->right);
    free_node(node->left);

    free(node);
}

void delete_rbtree(rbtree *t) {
    if (t != NULL) {
        free_node(t->root);
        free(t);
    }
}

void rbtree_left_rotate(rbtree *t, node_t *target_node) {
    node_t *target_node_rChild = target_node->right;
    target_node->right = target_node_rChild->left;

    if (target_node_rChild->left != NIL) {
        target_node_rChild->left->parent = target_node;
    }
    target_node_rChild->parent = target_node->parent;
    if (target_node->parent == NIL) {
        t->root = target_node_rChild;
    }
    else if (target_node == target_node->left) {
        target_node->parent->left = target_node_rChild;
    }
    else {
        target_node->parent->right = target_node_rChild;
    }
    target_node_rChild->left = target_node;
    target_node->parent = target_node_rChild;
}

void rbtree_right_rotate(rbtree *t, node_t *target_node) {
    node_t *target_node_lChild = target_node->left;
    target_node->left = target_node_lChild->right;

    if (target_node_lChild->right != NIL) {
        target_node_lChild->right->parent = target_node;
    }
    if (target_node->parent == NIL) {
        t->root = target_node_lChild;
    }
    else if (target_node == target_node->parent->left) {
        target_node->parent->left = target_node_lChild;
    }
    else {
        target_node->parent->right = target_node_lChild;
    }

    target_node_lChild->right = target_node;
    target_node->parent = target_node_lChild;
}

void rbtree_insert_fixup(rbtree *t, node_t *target_node) {
    node_t *target_parent = target_node->parent;
    node_t *target_grand_parent = target_parent->parent;

    while (target_parent->color == RBTREE_RED) {
        if (target_parent == target_grand_parent->left) {
            node_t *uncle = target_grand_parent->right;
            if (uncle->color == RBTREE_RED) {
                target_parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                target_node = target_grand_parent;
            } else if (target_node == target_parent->right) {
                target_node = target_parent;
                rbtree_left_rotate(t, target_node);
            }
            target_parent->color = RBTREE_BLACK;
            target_grand_parent->color = RBTREE_RED;
            rbtree_right_rotate(t, target_grand_parent);
        } else {
            node_t *uncle = target_grand_parent->left;
            if (uncle->color == RBTREE_RED) {
                target_parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                target_node = target_grand_parent;
            } else if (target_node == target_parent->left) {
                target_node = target_parent;
                rbtree_right_rotate(t, target_node);
            }
            target_parent->color = RBTREE_BLACK;
            target_grand_parent->color = RBTREE_RED;
            rbtree_left_rotate(t, target_grand_parent);
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *create_node(const key_t key) {
    node_t *tempNode = malloc(sizeof(node_t));
    tempNode->color = RBTREE_RED;
    tempNode->key = key;
    tempNode->parent = NIL;
    tempNode->left = NIL;
    tempNode->right = NIL;

    return tempNode;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // todo fixup 기능 붙이기
    node_t *node = t->root;
    node_t *pParent = NIL;
    position child_position;

    while (node != NIL) {
        pParent = node;
        if (node->key > key) {
            child_position = LEFT;
            node = node->left;
        }
        else {
            child_position = RIGHT;
            node = node->right;
        }
    }
    node_t *new_node = create_node(key);
    new_node->parent = pParent;

    if (pParent == NIL) {
        t->root = new_node;
    }
    else if (child_position == LEFT) {
        pParent->left = new_node;
    } else {
        pParent->right = new_node;
    }

    rbtree_insert_fixup(t, new_node);
    return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    node_t *node = t->root;

    while (node != NIL) {
        if (node->key == key) {
            return node;
        }
        else if (node->key > key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return NULL;
}

node_t *rbtree_min(const rbtree *t) {
    node_t *node = t->root;
    while (node != NIL) {
        if (node->left != NIL) {
            node = node->left;
        }
        else {
            return node;
        }
    }

    return t->root;
}

node_t *rbtree_max(const rbtree *t) {
    node_t *node = t->root;
    while (node != NIL) {
        if (node->right != NIL) {
            node = node->right;
        }
        else {
            return node;
        }
    }

    return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
    // TODO: implement erase


    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array


    return 0;
}
