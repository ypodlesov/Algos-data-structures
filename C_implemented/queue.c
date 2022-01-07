#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct q_node {
    int val;
    struct q_node *next, *prev;
} q_node;

typedef struct queue {
    int size;
    struct q_node *head, *tail;
} queue;

queue *push(queue *q, int val);
queue *pop(queue *q);
void display(queue *q);
queue *clear(queue *q);

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;

    queue *q = (queue *)malloc(sizeof(queue));
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    char *s = (char *)malloc(sizeof(char));
    while (fscanf(in, "%s", s) != EOF) {
       if (!strcmp(s, "pop")) {
           if (q->head) fprintf(out, "%d\n", q->head->val);
           q = pop(q);
       } else if (!strcmp(s, "push")) {
           int a;
           fscanf(in, "%d", &a);
           q = push(q, a);
           fprintf(out, "ok\n");
       } else if (!strcmp(s, "size")) {
           fprintf(out, "%d\n", q->size);
       } else if (!strcmp(s, "clear")) {
           q = clear(q);
           fprintf(out, "ok\n");
       } else if (!strcmp(s, "exit")) {
           fprintf(out, "bye\n");
           break;
       } else if (!strcmp(s, "front")) {
           if (q->head) fprintf(out, "%d\n", q->head->val);
       } else if (!strcmp(s, "display")) {
           display(q);
       }
    }


    fclose(in);
    fclose(out);

    return 0;
}

queue *push(queue *q, int val) {
    q_node *node = (q_node *)malloc(sizeof(q_node));
    node->val = val;
    node->next = NULL;
    node->prev = q->tail;
    if (q->size == 0) {
        q->head = q->tail = node;
        ++q->size;
        return q;
    }
    q->tail->next = node;
    q->tail = node;
    ++q->size;
    return q;
}

queue *pop(queue *q) {
    if (!q->head) return q;
    --q->size;
    q_node *node = q->head;
    q->head = q->head->next;
    free(node);
    return q;
}

void display(queue *q) {
    q_node *node = q->head;
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

queue *clear(queue *q) {
    q_node *node = NULL;
    while (q->head) {
        node = q->head;
        q->head = q->head->next;
        free(node);
    }
    q->size = 0;
    return q;
}
