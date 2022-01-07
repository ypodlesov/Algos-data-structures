#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct list_node {
    int key;
    struct list_node *next, *prev;
} list_node;

void display(list_node *head);
list_node *insert_node(list_node *head, list_node *after, int key);
list_node *search_node(list_node *head, int key);
list_node *delete_node(list_node *head, list_node *target);
void destroy(list_node *head);
int count_size(list_node *head);

int main(void) {

    FILE *in, *out;
    char nin[] = "input.txt", nout[] = "output.txt";
    in = fopen(nin, "r");
    out = fopen(nout, "w");
    // in = stdin;
    // out = stdout;


    list_node *head = NULL;
    char *s = (char *)malloc(sizeof(char));
    while (fscanf(in, "%s", s) != EOF) {
       if (!strcmp(s, "pop")) {
           fprintf(out, "%d\n", head->key);
           head = delete_node(head, head);
       } else if (!strcmp(s, "push")) {
           int a;
           fscanf(in, "%d", &a);
           head = insert_node(head, NULL, a);
           fprintf(out, "ok\n");
       } else if (!strcmp(s, "size")) {
           fprintf(out, "%d\n", count_size(head));
       } else if (!strcmp(s, "clear")) {
           while (head) head = delete_node(head, head);
           fprintf(out, "ok\n");
       } else if (!strcmp(s, "exit")) {
           fprintf(out, "bye\n");
           break;
       } else if (!strcmp(s, "back")) {
           fprintf(out, "%d\n", head->key);
       }
    }

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
        node->prev = NULL;
        head = node;
        return head;
    }
    node->next = after->next;
    node->prev = after;
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
        if (head) head->prev = NULL;
        free(target);
        return head;
    }
    list_node *node = head;
    while (node->next != target) node = node->next;
    node->next = target->next;
    node->prev = target->prev;
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
