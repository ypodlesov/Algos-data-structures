#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct stack {
    int key;
    struct stack *next;
} stack;

void display(stack *head);
stack *push(stack *head, int key);
stack *search_node(stack *head, int key);
stack *pop(stack *head);
void destroy(stack *head);
int count_size(stack *head);

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;

    stack *head = NULL;
    char *s = (char *)malloc(sizeof(char));
    while (fscanf(in, "%s", s) != EOF) {
       if (!strcmp(s, "pop")) {
           if (!head) continue;
           fprintf(out, "%d\n", head->key);
           head = pop(head);
       } else if (!strcmp(s, "push")) {
           int a;
           fscanf(in, "%d", &a);
           head = push(head, a);
           fprintf(out, "ok\n");
       } else if (!strcmp(s, "size")) {
           fprintf(out, "%d\n", count_size(head));
       } else if (!strcmp(s, "clear")) {
           while (head) head = pop(head);
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

void display(stack *head) {
    stack *node = head;
    while (node) {
        printf("%d ", node->key);
        node = node->next;
    }
    printf("\n");
}

stack *push(stack *head, int key) {
    stack *node = (stack *)malloc(sizeof(stack));
    node->key = key;
    node->next = head;
    return node;
}

stack *search_node(stack *head, int key) {
    stack *node = head;
    while (node && node->key != key) node = node->next;
    return node;
}

stack *pop(stack *head) {
    stack *node = head;
    head = head->next;
    free(node);
    return head;
}

void destroy(stack *head) {
    stack *node = head;
    while (node) {
        stack *t = node;
        node = node->next;
        free(t);
    }
}

int count_size(stack *head) {
    stack *node = head;
    int cnt = 0;
    while (node) {
        ++cnt;
        node = node->next;
    }
    return cnt;
}
