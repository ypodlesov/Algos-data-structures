#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct tree {
    char color;
    int key, data;
    struct tree* left, * right, * parent;
} tree;

void swap(int* a, int* b);

tree* init_node(char color, int key, int data, tree* parent, tree* left, tree* right);
tree* search(tree* root, int key);
void in_order_walk(tree* root);
void destroy(tree* root);
tree* left_rotate(tree* x);
tree* right_rotate(tree* x);
tree* RB_insert(tree* root, int key, int data);
tree* insert_fixup(tree* root, tree* z);
tree* get_min_node(tree* root);
tree* get_max_node(tree* root);
tree* RB_delete(tree* root, tree* z);


int main(void) {

    FILE* in, * out;
    char nin[] = "input.txt", nout[] = "output.txt";
    in = fopen(nin, "r");
    out = fopen(nout, "w");
    // in = stdin;
    // out = stdout;

    tree* root = NULL;
    while (1) {
        char ch;
        fscanf(in, "%c", &ch);
        if (ch == 'A') {
            int key, data;
            fscanf(in, "%d%d", &key, &data);
            root = RB_insert(root, key, data);
        }
        else if (ch == 'D') {
            int key;
            fscanf(in, "%d", &key);
            if (key == 30)
                key = 30;
            root = RB_delete(root, search(root, key));
        }
        else if (ch == 'S') {
            int key;
            fscanf(in, "%d", &key);
            tree* node = search(root, key);
            if (node) printf("%d %d\n", node->key, node->data);
        }
        else if (ch == 'F') {
            break;
        }
    }

    destroy(root);
    fclose(in);
    fclose(out);


    return 0;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

tree* init_node(char color, int key, int data, tree* parent, tree* left, tree* right) {
    tree* node = (tree*)malloc(sizeof(tree));
    node->color = color, node->key = key, node->data = data;
    node->parent = parent, node->left = left, node->right = right;
    return node;
}

tree* search(tree* root, int key) {
    if (!root) return NULL;
    if (root->key == key) return root;
    return (key < root->key) ? search(root->left, key) : search(root->right, key);
}

void in_order_walk(tree* root) {
    if (!root) return;
    in_order_walk(root->left);
    printf("%d(%c)", root->key, root->color);
    in_order_walk(root->right);
}

void destroy(tree* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    free(root);
}

tree* left_rotate(tree* x) {
    if (!x) return NULL;
    tree* y = x->right;
    if (x->parent) {
        if (x->parent->left == x) x->parent->left = y;
        else x->parent->right = y;
    }
    y->parent = x->parent;
    x->parent = y;
    if (y->left) y->left->parent = x;
    x->right = y->left;
    y->left = x;
    return y;
}

tree* right_rotate(tree* x) {
    if (!x) return NULL;
    tree* y = x->left;
    if (x->parent) {
        if (x->parent->left == x) x->parent->left = y;
        else x->parent->right = y;
    }
    y->parent = x->parent;
    x->parent = y;
    if (y->right) y->right->parent = x;
    x->left = y->right;
    y->right = x;
    return y;
}

tree* RB_insert(tree* root, int key, int data) {
    tree* x, * y;
    x = root, y = NULL;
    while (x) {
        y = x;
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else {
            x->data = data;
            return root;
        }
    }
    tree* z = init_node('R', key, data, y, NULL, NULL);
    if (!y) {
        z->color = 'B';
        return z;
    }
    if (key < y->key) y->left = z;
    else y->right = z;
    root = insert_fixup(root, z);
    return root;
}

tree* insert_fixup(tree* root, tree* z) {
    if (!z) return root;
    while (z->parent && z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            tree* y = z->parent->parent->right;
            if (y && y->color == 'R') {
                // CASE 1
                z->parent->color = 'B';
                y->color = 'B';
                z = y->parent;
                z->color = 'R';
            }
            else {
                tree* x = z->parent;
                if (z->parent->right == z) {
                    // CASE 2
                    x = left_rotate(x);
                }
                // CASE 3
                if (x->parent == root) root = right_rotate(root);
                else x = x->parent, x = right_rotate(x);
                z = x->left;
                x->color = 'B';
                x->right->color = 'R';
                // z->color = 'B';
            }
        }
        else {
            tree* y = z->parent->parent->left;
            if (y && y->color == 'R') {
                // CASE 4
                z->parent->color = 'B';
                y->color = 'B';
                z = y->parent;
                z->color = 'R';
            }
            else {
                tree* x = z->parent;
                if (z->parent->left == z) {
                    // CASE 5
                    x = right_rotate(x);
                }
                // CASE 6
                if (x->parent == root) root = left_rotate(root);
                else x = x->parent, x = left_rotate(x);
                z = x->right;
                x->color = 'B';
                x->left->color = 'R';
                // z->color = 'R';
            }
        }
    }
    if (!z->parent) root = z;
    if (root) root->color = 'B';
    return root;
}

tree* get_min_node(tree* root) {
    if (!root) NULL;
    if (!root->left) return root;
    return get_min_node(root->left);
}

tree* get_max_node(tree* root) {
    if (!root) NULL;
    if (!root->right) return root;
    return get_max_node(root->right);
}

tree* RB_delete(tree* root, tree* z) {
    if (!z) return root;
    

}

// A 20 20
// A 30 30
// A 40 40
// A 50 50
// A 60 60
// A 70 70
// A 80 80
// A 45
// A 35
// D 40
// D 50
// D 70
// D 30
// F
