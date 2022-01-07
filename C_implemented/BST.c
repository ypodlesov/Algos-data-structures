#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

int max(int a, int b);

typedef struct tree {
    int key;
    struct tree *parent, *left, *right;
} tree;

tree *min_node(tree *node); // returns the min-node from node-subtree
tree *max_node(tree *node); // returns the max-node from node-subtree
tree *insert(tree *root, int key); // returns the pointer to the root
void delete(tree **root, tree *target); // deletes the target
tree *search(tree *root, int key); // returns the pointer to the node or NULL
int count_height(tree *root, int cur_height); // returns the height of the tree
void in_order_tree_walk(tree *node); // prints the tree as the sorted sequence
void destroy(tree *root); // to free memory

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;


    tree *root = NULL;
    char ch;
    while (1) {
        fscanf(in, "%c", &ch);
        if (ch == 'A') {
            int a;
            fscanf(in, "%d", &a);
            root = insert(root, a);
        } else if (ch == 'D') {
            int a;
            fscanf(in, "%d", &a);
            delete(&root, search(root, a));
        } else if (ch == 'S') {
            int a;
            fscanf(in, "%d", &a);
            tree *node = search(root, a);
            if (node) fprintf(out, "%d\n", node->key);
        } else if (ch == 'F') {
            break;
        }
    }

    destroy(root);
    fclose(in);
    fclose(out);

    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

tree *min_node(tree *node) {
    if (!node) return NULL;
    while (node->left) node = node->left;
    return node;
}

tree *max_node(tree *node) {
    if (!node) return NULL;
    while (node->right) node = node->right;
    return node;
}

tree *insert(tree *root, int key) {
    tree *node = (tree *)malloc(sizeof(tree));
    node->left = node->right = NULL;
    node->key = key;
    tree *x = root;
    tree *y = NULL;
    while (x) { // finds the place for "node"
        y = x;
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else return root;
    }
    // now "y" is a parent for "node"
    node->parent = y;
    if (!y) root = node; // the tree was empty
    else if (key < y->key) y->left = node; // new node is the left-child
    else y->right = node; // new node is the right child
    return root;
}

void delete(tree **root, tree *target) {
    if (!target) return; // to prevent mistakes with NULL->...
    if (target->left && target->right) { // "target" has both children
        tree *x = max_node(target->left);
        target->key = x->key;
        delete(root, x);
    } else if (target->left) { // "target" has ONLY left child
        if (target != *root) {
            if (target->parent->left == target) target->parent->left = target->left;
            else target->parent->right = target->left;
        } else {
            *root = target->left;
        }
        target->left->parent = target->parent;
        free(target), target = NULL;
    } else if (target->right) { // "target" has ONLY right child
        if (target != *root) {
            if (target->parent->left == target) target->parent->left = target->right;
            else target->parent->right = target->right;
        } else {
            *root = target->right;
        }
        target->right->parent = target->parent;
        free(target), target = NULL;
    } else { // "target" has no children
        if (target != *root) {
            if (target->parent->left == target) target->parent->left = NULL;
            else target->parent->right = NULL;
            free(target), target = NULL;
        } else {
            free(*root), *root = NULL;
        }
    }
}

// all operations below are trivial
tree *search(tree *node, int key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

int count_height(tree *root, int cur_height) {
    if (!root) return cur_height;
    return max(count_height(root->left, cur_height + 1),
               count_height(root->right, cur_height + 1));
}

void in_order_tree_walk(tree *node) {
    if (!node) return;
    in_order_tree_walk(node->left);
    printf("%d ", node->key);
    in_order_tree_walk(node->right);
}

void destroy(tree *root) {
    if (root) {
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}
