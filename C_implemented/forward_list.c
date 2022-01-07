#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct list_node {
    int key;
    struct list_node *next;
} list_node;

void display(list_node *head);
list_node *insert_node(list_node *head, list_node *after, int key);
list_node *search_node(list_node *head, int key);
list_node *delete_node(list_node *head, list_node *target);
void destroy(list_node *head);
int count_size(list_node *head);

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;




    fclose(in);
    fclose(out);



    return 0;
}

void display(list_node *head) {
    list_node *node = head;
    while (node) {
        printf("%d ", node->key);
        node = node->next;
    }
    printf("\n");
}

list_node *insert_node(list_node *head, list_node *after, int key) {
    list_node *node = (list_node *)malloc(sizeof(list_node));
    node->key = key;
    if (!after) {
        node->next = head;
        head = node;
        return head;
    }
    node->next = after->next;
    after->next = node;
    return head;
}

list_node *search_node(list_node *head, int key) {
    list_node *node = head;
    while (node && node->key != key) node = node->next;
    return node;
}

list_node *delete_node(list_node *head, list_node *target) {
    if (!target) return head;
    if (target == head) {
        head = head->next;
        free(target);
        return head;
    }
    list_node *node = head;
    while (node->next != target) node = node->next;
    node->next = target->next;
    free(target);
    return head;
}

void destroy(list_node *head) {
    list_node *node = head;
    while (node) {
        list_node *t = node;
        node = node->next;
        free(t);
    }
}

int count_size(list_node *head) {
    list_node *node = head;
    int cnt = 0;
    while (node) {
        ++cnt;
        node = node->next;
    }
    return cnt;
}
