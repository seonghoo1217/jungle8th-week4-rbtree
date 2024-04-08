#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

void delete_node(rbtree *t, node_t *node);

node_t *node_find(const rbtree *t, node_t *current, const key_t key);

void rb_transplant(rbtree *t, node_t *u, node_t *v);

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
    node_t *current = t->root;
    if (current == t->nil)
        return current;
    while (current != t->nil) {
        current = current->left;
    }
    return current;
}

node_t *tree_minimum(const rbtree *t, node_t *sub_root) {
    // TODO: implement find
    node_t *r = sub_root;
    if (r == t->nil)
        return r;
    while (r->left != t->nil) {
        r = r->left;
    }
    return r;
}

node_t *rbtree_max(const rbtree *t) {
    // TODO: implement find
    node_t *current = t->root;
    while (current != t->nil) {
        current = current->right;
    }
    return current;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v) {
    if (u->parent == t->nil) {
        t->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else
        u->parent->right = v;
    v->parent = u->parent;
    return;
}

int rbtree_erase(rbtree *t, node_t *z) {
    // TODO: implement erase
//    node_t *delete_node;
//    node_t *remove_parent_node, *replace_node;
    node_t *y = z;
    color_t y_original_color = y->color;
    node_t *x;
    //왼쪽 자식 없음
    if (z->left == t->nil) {
        x = z->right;
        rb_transplant(t, z, z->right);
    }
        // 오른쪽 자식 없음
    else if (z->right == t->nil) {
        x = z->left;
        rb_transplant(t, z, z->left);
    }
        // 자식이 둘다 있음
    else {
        y = tree_minimum(t, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rb_transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_orginal_color == RBTREE_BLACK) {
        //TODO : 더블리 블랙
    }
    free(z);
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array
    return 0;
}
