#include "rbtree.h"
#include <stdlib.h>

static const node_t NIL_NODE = { RBTREE_BLACK, -1, NULL, NULL, NULL};
static const node_t *const NIL = &NIL_NODE;
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
    // TODO: implement find


    return t->root;
}

node_t *rbtree_max(const rbtree *t) {
    // TODO: implement find
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
