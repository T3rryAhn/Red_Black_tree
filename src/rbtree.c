#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *) calloc(1, sizeof(rbtree));

    // 닐 노드 생성. 닐 노드를 가르키는 포인터 NILL 은 변경 불가능한 상수.
    node_t * const NILL = calloc(1, sizeof(node_t));
    NILL->color = RBTREE_BLACK;
    NILL->key = -1;
    NILL->left = NILL;
    NILL->right = NILL;
    NILL->parent = NILL;

    p->nil = NILL;
    p->nil->color = RBTREE_BLACK;
    p->root = NILL;

    return p;
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory
    free(t);
}

node_t *create_node(const key_t key) {
    // TODO: 메모리에 노드 크기만큼 할당받고 값 채우고 주소 뱉어주기. 값만 가지고 트리와 연결되지않은 노드를 생성.
    node_t *temp_node = malloc(sizeof(node_t));
    temp_node->color = RBTREE_RED;
    temp_node->key = key;
    temp_node->parent
    temp_node->left = ;
    temp_node->right
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert
    node_t *node = t->root;
    if (node == t->nil) {

    }

    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    // TODO: implement find
    return t->root;
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
