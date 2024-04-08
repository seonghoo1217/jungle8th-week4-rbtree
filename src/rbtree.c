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

void left_rotate(rbtree *t, node_t *x) {
    node_t *y;
    y = x->right;
    x->right = y->left;
    if (y->left != t->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil) {
        t->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return;
}

void right_rotate(rbtree *t, node_t *x) {
    node_t *y;
    y = x->left;
    x->left = y->right;
    if (y->right != t->nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil) {
        t->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    return;
}

void rb_insert_Fixup(rbtree *t, node_t *z) {
    node_t *uncle;
    // while ((z != t->root) && (z->color != RBTREE_BLACK) && (z->parent->color == RBTREE_RED))
    while (z->parent->color == RBTREE_RED) {
        if (z->parent == z->parent->parent->left) {
            uncle = z->parent->parent->right;
            //경우1
            if (uncle->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
                //경우2
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(t, z);
                }
                //경우3
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotate(t, z->parent->parent);
            }
        }
            //반대로
        else {
            uncle = z->parent->parent->left;
            //경우1
            if (uncle != t->nil && uncle->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
                //경우2
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(t, z);
                }
                //경우3
                if (z != t->root && z->parent != t->root) {
                    z->parent->color = RBTREE_BLACK;
                    z->parent->parent->color = RBTREE_RED;
                    left_rotate(t, z->parent->parent);
                }
            }
        }
    }
    t->root->color = RBTREE_BLACK;
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
        newNode->color = RBTREE_BLACK;
    }

    rb_insert_Fixup(t, newNode);

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
        return t->nil;
    while (current->left != t->nil) {
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

    if (current == t->nil)
        return t->nil;
    while (current->right != t->nil) {
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

    if (y_original_color == RBTREE_BLACK) {
        //TODO : 더블리 블랙
    }
    free(z);
    return 0;
}

int inorder_rbtree(node_t *root, key_t *res, const rbtree *t, int index) {
    if (root == t->nil) {
        return index;
    }
    index = inorder_rbtree(root->left, res, t, index);
    res[index] = root->key;
    printf("inorder index : %d \n", res[index]);
    index += 1;
    index = inorder_rbtree(root->right, res, t, index);
    return index;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array
    if (t->root == t->nil) {
        return -1;
    }
    inorder_rbtree(t->root, arr, t, 0);
    return 0;
}

/*int main() {
    rbtree *newTree = new_rbtree();
//    rbtree_insert(newTree, 1);
//    rbtree_insert(newTree, 2);
//    rbtree_insert(newTree, 3);
//    rbtree_insert(newTree, 4);
//    rbtree_insert(newTree, 5);
    key_t arr1[] = {10, 5, 8, 34, 67, 23, 156, 24, 2, 12, 24, 36, 990, 25};
    const size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    key_t *res1 = calloc(n1, sizeof(key_t));
    rbtree_to_array(newTree, res1, n1);
    delete_rbtree(newTree);
}*/
