#include <stdio.h>
#include <stdlib.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct clist {
    int val;
    struct clist *prev, *next;
} clist;

clist *insert(clist *after, int val);
clist *delete(clist *head, int val);
clist *search(clist *head, int val);
void display(clist *head);
void destroy(clist *head);

int main(void) {

    // FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");

    int a;
    clist *head = NULL;
    while (scanf("%d", &a) && a != -1) {
        if (a == 0) {
            destroy(head);
        } else if (a == 1) {
            int val;
            scanf("%d", &val);
            head = insert(head, val);
            printf("OK\n");
        } else if (a == 2) {
            int val;
            scanf("%d", &val);
            head = delete(head, val);
            printf("OK\n");
        } else if (a == 3) {
            int val;
            scanf("%d", &val);
            clist *node = search(head, val);
            if (node) printf("FOUND: %d\n", node->val);
            else printf("NOT FOUND\n");
        } else if (a == 4) {
            display(head);
        }
    }


    // fclose(in);
    // fclose(out);

    return 0;
}

clist *insert(clist *after, int val) {
    clist *node = (clist *)malloc(sizeof(clist));
    node->val = val;
    if (after == NULL) {
        node->prev = node;
        node->next = node;
    } else {
        node->next = after->next;
        node->prev = after;
        after->next = node;
    }
    return node;
}

clist *delete(clist *head, int val) {
    if (head->val == val) {
        head = head->next;
        head->prev = head->prev->prev;
        free(head->prev);
        return head;
    }
    clist *tmp = head->next;
    while (tmp != head && tmp->val != val) tmp = tmp->next;
    if (tmp == head) return head;
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    free(tmp);
    return head;
}

clist *search(clist *head, int val) {
    clist *tmp = head->next;
    while (tmp != head && tmp->val != val) tmp = tmp->next;
    if (tmp->val == val) return tmp;
    return NULL;
}

void display(clist *head) {
    clist *node = head->next;
    printf("%d ", head->val);
    while (node != head) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

void destroy(clist *head) {
    clist *node = head->next;
    while (node != head) {
        clist *tmp = node;
        node = node->next;
        free(tmp);
    }
    free(node);
}
