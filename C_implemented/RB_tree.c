#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct tree {
    char color;
    int key, data;
    struct tree *left, *right, *parent;
} tree;

void swap(int *a, int *b);

tree *init_node(char color, int key, int data, tree *parent, tree *left, tree *right);
tree *search(tree *root, int key);
void in_order_walk(tree *root);
void destroy(tree *root);
tree *left_rotate(tree *x);
tree *right_rotate(tree *x);
tree *RB_insert(tree *root, int key, int data);
tree *insert_fixup(tree *root, tree *z);
tree *get_min_node(tree *root);
tree *get_max_node(tree *root);
tree *RB_delete(tree *root, tree *target);
int define_case(tree *y, tree *x, char side_of_x);
tree *delete_fixup(tree *root, tree *y, tree *x);


int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;

    tree *root = NULL;
    while (1) {
        char ch;
        scanf("%c", &ch);
        if (ch == 'A') {
            int key, data;
            scanf("%d%d", &key, &data);
            root = RB_insert(root, key, data);
        } else if (ch == 'D') {
            int key;
            scanf("%d", &key);
            root = RB_delete(root, search(root, key));
        } else if (ch == 'S') {
            int key;
            scanf("%d", &key);
            tree *node = search(root, key);
            if (node) printf("%d %d\n", node->key, node->data);
        } else if (ch == 'F') {
            break;
        }
    }


    destroy(root);
    fclose(in);
    fclose(out);


    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

tree *init_node(char color, int key, int data, tree *parent, tree *left, tree *right) {
    tree *node = (tree *)malloc(sizeof(tree));
    node->color = color, node->key = key, node->data = data;
    node->parent = parent, node->left = left, node->right = right;
    return node;
}

tree *search(tree *root, int key) {
    if (!root) return NULL;
    if (root->key == key) return root;
    return (key < root->key) ? search(root->left, key) : search(root->right, key);
}

void in_order_walk(tree *root) {
    if (!root) return;
    in_order_walk(root->left);
    printf("%d(%c)", root->key, root->color);
    in_order_walk(root->right);
}

void destroy(tree *root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    free(root);
}

tree *left_rotate(tree *x) {
    if (!x) return NULL;
    tree *y = x->right;
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

tree *right_rotate(tree *x) {
    if (!x) return NULL;
    tree *y = x->left;
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

tree *RB_insert(tree *root, int key, int data) {
    tree *x, *y;
    x = root, y = NULL;
    while (x) {
        y = x;
        if (key < x->key) x = x->left;
        // else x = x->right;
        else if (key > x->key) x = x->right;
        else {
            x->data = data;
            return root;
        }
    }
    tree *z = init_node('R', key, data, y, NULL, NULL);
    if (!y) {
        z->color = 'B';
        return z;
    }
    if (key < y->key) y->left = z;
    else y->right = z;
    root = insert_fixup(root, z);
    return root;
}

tree *insert_fixup(tree *root, tree *z) {
    if (!z) return root;
    while (z->parent && z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            tree *y = z->parent->parent->right;
            if (y && y->color == 'R') {
                // CASE 1
                z->parent->color = 'B';
                y->color = 'B';
                z = y->parent;
                z->color = 'R';
            } else {
                tree *x = z->parent;
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
        } else {
            tree *y = z->parent->parent->left;
            if (y && y->color == 'R') {
                // CASE 4
                z->parent->color = 'B';
                y->color = 'B';
                z = y->parent;
                z->color = 'R';
            } else {
                tree *x = z->parent;
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

tree *get_min_node(tree *root) {
    if (!root) NULL;
    if (!root->left) return root;
    return get_min_node(root->left);
}

tree *get_max_node(tree *root) {
    if (!root) NULL;
    if (!root->right) return root;
    return get_max_node(root->right);
}

tree *RB_delete(tree *root, tree *target) {
    if (!target) return root;
    if (target->color == 'R') {
        if (target->left && target->right) {
            // case 1
            tree *x = get_max_node(target->left);
            swap(&x->key, &target->key);
            swap(&x->data, &target->data);
            root = RB_delete(root, x);
        } else {
            // case 2 is imposible
            // so case 3
            if (root == target) {
                free(root);
                return NULL;
            } else {
                if (target->parent->left == target) target->parent->left = NULL;
                else target->parent->right = NULL;
                free(target);
            }
        }
    } else {
        if (target->left && target->right) {
            // case 4
            tree *x = get_max_node(target->left);
            swap(&x->key, &target->key);
            swap(&x->data, &target->data);
            root = RB_delete(root, x);
        } else if (target->left) {
            //  case 5
            tree *x = target->left;
            swap(&x->key, &target->key);
            swap(&x->data, &target->data);
            root = RB_delete(root, x);
        } else if (target->right) {
            // still case 5
            tree *x = target->right;
            swap(&x->key, &target->key);
            swap(&x->data, &target->data);
            root = RB_delete(root, x);
        } else {
            // case 6
            if (target == root) {
                free(root);
                return NULL;
            } else {
                tree *x = target->parent;
                if (x->left == target) x->left = NULL;
                else x->right = NULL;
                free(target);
                root = delete_fixup(root, x, NULL);
            }
        }
    }
    return root;
}

int define_case(tree *y, tree *x, char side_of_x) {
    if (!y) return 0;
    if (side_of_x == 'l') {
        tree *z = y->right;
        if (y->color == 'R') {
            if (!z->right && !z->right) return 1;
            if (!z->right && z->right->color == 'B') return 1;
            if (z->right->color == 'B' && !z->right) return 1;
            if (z->right->color == 'B' && z->right->color == 'B') return 1;
            if (z->right->color == 'R') return 2;
        } else {
            tree *zr = z->right;
            if (z->color == 'R') {
                if (!zr->right && !zr->right) return 3;
                if (!zr->right && zr->right->color == 'B') return 3;
                if (zr->right->color == 'B' && !zr->right) return 3;
                if (zr->right->color == 'B' && zr->right->color == 'B') return 3;
                if (zr->right->color == 'R') return 4;
            } else {
                if (zr && zr->color == 'R') return 5;
                if (!z->right && !z->right) return 6;
                if (!z->right && z->right->color == 'B') return 6;
                if (z->right->color == 'B' && !z->right) return 6;
                if (z->right->color == 'B' && z->right->color == 'B') return 6;
            }
        }
    } else {
        tree *z = y->left;
        if (y->color == 'R') {
            if (!z->left && !z->right) return 1;
            if (!z->left && z->right->color == 'B') return 1;
            if (z->left->color == 'B' && !z->right) return 1;
            if (z->left->color == 'B' && z->right->color == 'B') return 1;
            if (z->left->color == 'R') return 2;
        } else {
            tree *zl = z->left;
            if (z->color == 'R') {
                if (!zl->left && !zl->right) return 3;
                if (!zl->left && zl->right->color == 'B') return 3;
                if (zl->left->color == 'B' && !zl->right) return 3;
                if (zl->left->color == 'B' && zl->right->color == 'B') return 3;
                if (zl->left->color == 'R') return 4;
            } else {
                if (zl && zl->color == 'R') return 5;
                if (!z->left && !z->right) return 6;
                if (!z->left && z->right->color == 'B') return 6;
                if (z->left->color == 'B' && !z->right) return 6;
                if (z->left->color == 'B' && z->right->color == 'B') return 6;
            }
        }
    }
    return 0;
}

tree *delete_fixup(tree *root, tree *y, tree *x) {
    if (!y) return root;
    if (x && x->color == 'R') return root;
    if (y->left == x) {
        int var = define_case(y, x, 'l');
        if (var == 1) {
            y->color = 'B';
            y->right->color = 'R';
        } else if (var == 2) {
            if (y == root) {
                root = left_rotate(root);
                root->left->color = root->color = root->right->color = 'B';
            } else {
                y = left_rotate(y);
                y->right->color = y->left->color = 'B';
                y->color = 'R';
                y->right->color = y->left->color = 'B';
            }
        } else if (var == 3) {
            if (y == root) {
                root = left_rotate(root);
                root->left->right->color = 'R';
            } else {
                y = left_rotate(y);
                y->color = 'B';
                y->left->right->color = 'R';
            }
        } else if (var == 4) {
            tree *z = y->right;
            z = right_rotate(z);
            if (y == root) {
                root = left_rotate(root);
                root->right->left->color = 'B';
            } else {
                y = left_rotate(y);
                y->right->left->color = 'B';
            }
        } else if (var == 5) {
            tree *z = y->right;
            z = right_rotate(z);
            if (y == root) {
                root = left_rotate(root);
            } else {
                y = left_rotate(y);
                y->color = 'B';
            }
        } else if (var == 6) {
            y->right->color = 'R';
            root = delete_fixup(root, y->parent, y);
        } else {
            printf("UNDEFINED CASE\n");
        }
    } else {
        int var = define_case(y, x, 'r');
        if (var == 1) {
            y->color = 'B';
            y->left->color = 'R';
        } else if (var == 2) {
            if (y == root) {
                root = right_rotate(root);
                root->right->color = root->color = root->left->color = 'B';
            } else {
                y = right_rotate(y);
                y->left->color = y->right->color = 'B';
                y->color = 'R';
                y->left->color = y->right->color = 'B';
            }
        } else if (var == 3) {
            if (y == root) {
                root = right_rotate(root);
                root->right->left->color = 'R';
            } else {
                y = right_rotate(y);
                y->color = 'B';
                y->right->left->color = 'R';
            }
        } else if (var == 4) {
            tree *z = y->left;
            z = left_rotate(z);
            if (y == root) {
                root = right_rotate(root);
                root->left->right->color = 'B';
            } else {
                y = right_rotate(y);
                y->left->right->color = 'B';
            }
        } else if (var == 5) {
            tree *z = y->left;
            z = left_rotate(z);
            if (y == root) {
                root = right_rotate(root);
            } else {
                y = right_rotate(y);
                y->color = 'B';
            }
        } else if (var == 6) {
            y->left->color = 'R';
            root = delete_fixup(root, y->parent, y);
        } else {
            printf("UNDEFINED CASE\n");
        }
    }
    root->color = 'B';
    return root;
}
