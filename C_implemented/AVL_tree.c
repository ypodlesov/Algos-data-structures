#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct tree {
    int key, data;
    struct tree *left, *right;
    int height;
} tree;

tree *init_node(int key, int data);
tree *destroy(tree *node);
tree *search(tree *node, int key);
tree *get_min_node(tree *node);
tree *delete_min_node(tree *root);
tree *get_max_node(tree *node);
tree *delete_max_node(tree *root);
int height(tree *node);
int skew(tree *node);
void fix_height(tree *node);
tree *rotate_right(tree *x);
tree *rotate_left(tree *x);
tree *balance(tree *x);
tree *insert(tree *node, int key, int data);
tree *delete_node(tree *root, int key);


int main(void) {

    FILE *in, *out;
//    char nin[] = "input.txt", nout[] = "output.txt";
    in = stdin;
    out = stdout;

    tree *root = NULL;
    char ch;
    while (1) {
        fscanf(in, "%c", &ch);
        if (ch == 'A') {
            int a, b;
            fscanf(in, "%d%d", &a, &b);
            root = insert(root, a, b);
        } else if (ch == 'D') {
            int a;
            fscanf(in, "%d", &a);
            root = delete_node(root, a);
        } else if (ch == 'S') {
            int a;
            fscanf(in, "%d", &a);
            tree *node = search(root, a);
            if (node) fprintf(out, "%d %d\n", node->key, node->data);
        } else if (ch == 'F') {
            break;
        }
    }

    destroy(root);
    fclose(in);
    fclose(out);

    return 0;
}

tree *init_node(int key, int data) {
    tree *node = (tree *)malloc(sizeof(tree));
    node->left = node->right = NULL;
    node->key = key, node->data = data, node->height = 1;
    return node;
}

tree *destroy(tree *node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        free(node);
    }
    return NULL;
}

tree *search(tree *node, int key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

tree *get_min_node(tree *node) {
    if (!node) return NULL;
    if (!node->left) return node;
    return get_min_node(node->left);
}

tree *delete_min_node(tree *root) {
    if (!root) return NULL;
    if (!root->left) return root->right;
    root->left = delete_min_node(root->left);
    return balance(root);
}

tree *get_max_node(tree *node) {
    if (!node) return NULL;
    if (!node->right) return node;
    return get_max_node(node->right);
}

tree *delete_max_node(tree *root) {
    if (!root) return NULL;
    if (!root->right) return root->left;
    root->right = delete_max_node(root->right);
    return balance(root);
}

int height(tree *node) {
    return (node) ? node->height : 0;
}

int skew(tree *node) {
    return (node) ? height(node->right) - height(node->left) : 0;
}

void fix_height(tree *node) {
    if (!node) return;
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

tree *rotate_right(tree *x) {
    tree *y = x->left;
    x->left = y->right;
    y->right = x;
    fix_height(x);
    fix_height(y);
    return y;
}

tree *rotate_left(tree *x) {
    tree *y = x->right;
    x->right = y->left;
    y->left = x;
    fix_height(x);
    fix_height(y);
    return y;
}

tree *balance(tree *x) {
    if (!x) return x;
    fix_height(x);
    int bf = skew(x);
    if (bf == 2) {
        if (skew(x->right) < 0) x->right = rotate_right(x->right);
        return rotate_left(x);
    }
    if (bf == -2) {
        if (skew(x->left) > 0) x->left = rotate_left(x->left);
        return rotate_right(x);
    }
    return x;
}

tree *insert(tree *root, int key, int data) {
    if (!root) return init_node(key, data);
    if (key < root->key) root->left = insert(root->left, key, data);
    else if (key > root->key) root->right = insert(root->right, key, data);
    else {
        root->data = data;
        return root;
    }
    return balance(root);
}

tree *delete_node(tree *root, int key) {
    if (!root) return NULL;
    if (key < root->key) root->left = delete_node(root->left, key);
    else if (key > root->key) root->right = delete_node(root->right, key);
    else {
        tree *left = root->left;
        tree *right = root->right;
        free(root);
        if (!right) return left;
        tree *m = get_min_node(right);
        m->right = delete_min_node(right);
        m->left = left;
        return balance(m);
    }
    return balance(root);
}
