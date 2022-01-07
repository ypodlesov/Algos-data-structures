#include <stdio.h>
#include <stdlib.h>
#include "leak.c"

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

#define ll long long
#define uchar unsigned char


struct list_node {
    int val;
    struct list_node *next;
};
typedef struct list_node list_node;

typedef struct list {
    int size;
    list_node *head, *tail;
} list;

list *init_list(int val);
list_node *init_node(int val);
void insert(list **l, int val);
void destroy(list **l);
void merge_sort(list *l, list *buf_l, list_node *left, int n);
void print_list(FILE *out, list *l);


int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;
    list *l = NULL;
    list *buf_list = NULL;
    int a;
    fscanf(in, "%d", &a);
    while (a != 0) {
        insert(&l, a);
        insert(&buf_list, 0);
        fscanf(in, "%d", &a);
    }

    merge_sort(l, buf_list, l->head, l->size);
    print_list(out, l);

    destroy(&l);
    // leak_print_list(memory_list);


    fclose(in);
    fclose(out);

    return 0;
}

list_node *init_node(int val) {
    list_node *node = malloc(sizeof(list_node));
    node->val = val;
    node->next = NULL;
    return node;
}

list *init_list(int val) {
    list *l = malloc(sizeof(list));
    l->head = l->tail = init_node(val);
    l->size = 1;
    return l;
}

void insert(list **l, int val) {
    if (!*l) *l = init_list(val);
    else {
        list_node *node = init_node(val);
        node->next = (*l)->head;
        (*l)->head = node;
        (*l)->size++;
    }
}

void destroy(list **l) {
    list_node *node = (*l)->head;
    while (node) {
        list_node *tmp = node;
        node = node->next;
        free(tmp);
    }
    free(*l);
}

void merge_sort(list *l, list *buf_list, list_node *left, int n) {
    if (n <= 1) return;
    int mid = n / 2;
    list_node *mid_node = left;
    list_node *tmp = left;
    for (int i = 0; i < mid; ++i) mid_node = mid_node->next;
    merge_sort(l, buf_list, left, mid);
    merge_sort(l, buf_list, mid_node, n-mid);

    int i = 0, j = mid;
    list_node *buf_node = buf_list->head;
    while (i < mid && j < n) {
        if (left->val < mid_node->val) {
            buf_node->val = left->val;
            left = left->next;
            ++i;
        } else {
            buf_node->val = mid_node->val;
            mid_node = mid_node->next;
            ++j;
        }
        buf_node = buf_node->next;
    }
    while (i < mid) {
        buf_node->val = left->val;
        left = left->next;
        ++i;
        buf_node = buf_node->next;
    }
    while (j < n) {
        buf_node->val = mid_node->val;
        mid_node = mid_node->next;
        ++j;
        buf_node = buf_node->next;
    }
    buf_node = buf_list->head;
    i = 0;
    while (i++ < n) {
        tmp->val = buf_node->val;
        buf_node = buf_node->next;
        tmp = tmp->next;
    }
}

void print_list(FILE *out, list *l) {
    list_node *node = l->head;
    while (node) {
        fprintf(out, "%d ", node->val);
        node = node->next;
    }
    printf("\n");
}
