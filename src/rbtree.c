#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

void delete_node(rbtree *t, node_t *node);

node_t *node_find(const rbtree *t, node_t *current, const key_t key);

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *) calloc(1, sizeof(rbtree));
    node_t *nil = (node_t *) calloc(1, sizeof(node_t));
    nil->color = RBTREE_BLACK;
//    p->nil = NULL;
//    p->root = NULL;
    p->nil = p->root = nil;
    // TODO: initialize struct if needed
    return p;
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory
    node_t *node = t->root;
    if (node != t->nil)
        delete_node(t, node);

    free(t->nil);
    free(t);
}

void delete_node(rbtree *t, node_t *node) {
    if (node->left != t->nil)
        delete_node(t, node->left);
    if (node->right != t->nil)
        delete_node(t, node->right);

    free(node);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert
    node_t *newNode = (node_t *) calloc(1, sizeof(node_t));
    newNode->color = RBTREE_RED;
    newNode->key = key;
    newNode->left = newNode->right = t->nil;

    /*if (newNode->key > t->root) {
        newNode->left = rbtree_insert(t,key);
    } else if (newNode->key <t->root) {
    } else {
    }*/
    node_t *current = t->root;
    while (current != t->nil) {
        if (key < current->key) {
            if (current->left == t->nil) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else {
            if (current->right == t->nil) {
                current->right = newNode;
                break;
            }
            current = current->right;
        }
    }
    newNode->parent = current;

    if (current == t->nil) {
        t->root = newNode;
    }
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    // TODO: implement find
    node_t *current = t->root;

    while (current != t->nil) {
        if (key == current->key)
            return current;
        else
            current = (key < current->key) ? current->left : current->right;
    }
    return NULL;
}

//node_t *node_find(const rbtree *t, node_t *current, const key_t key) {
//    if (current->key == key) {
//        return t->root;
//    }
//    if (current->key > key) {
//        return node_find(t, current->left, key);
//    } else {
//        return node_find(t, current->right, key);
//    }
//}

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
