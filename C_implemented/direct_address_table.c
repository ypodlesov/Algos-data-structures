#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

typedef struct list_node {
    int key, data;
    struct list_node *next, *prev;
} list_node;

void display(list_node *head);
list_node *insert_node(list_node *head, int key, int data);
list_node *search_node(list_node *head, int key);
list_node *delete_node(list_node *head, list_node *target);
void destroy(list_node *head);
int count_size(list_node *head);

static inline int hash(int key);


int main(void) {

    list_node *table[MAX];
    for (int i = 0; i < MAX; ++i) table[i] = NULL;
    while (1) {
        char ch;
        scanf("%c", &ch);
        if (ch == 'A') {
            int key, data;
            scanf("%d%d", &key, &data);
            int h = hash(key);
            list_node *node = search_node(table[h], key);
            if (node) {
                node->data = data;
                printf("ELEMENT IS UPDATED\n");
                continue;
            }
            table[h] = insert_node(table[h], key, data);
            node = search_node(table[h], key);
            printf("%d %d\n", node->key, node->data);
        } else if (ch == 'D') {
            int key;
            scanf("%d", &key);
            int h = hash(key);
            list_node *node = search_node(table[h], key);
            table[h] = delete_node(table[h], node);
            printf("OK\n");
        } else if (ch == 'S') {
            int key;
            scanf("%d", &key);
            int h = hash(key);
            list_node *node = search_node(table[h], key);
            if (node) printf("%d %d\n", node->key, node->data);
            else printf("NO NODE");
        } else if (ch == 'F') {
            printf("GOODBYE\n");
            break;
        }
    }


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

list_node *insert_node(list_node *head, int key, int data) {
    list_node *node = (list_node *)malloc(sizeof(list_node));
    node->key = key, node->data = data;
    if (!head) {
        node->next = head;
        node->prev = NULL;
        head = node;
        return head;
    }
    node->next = head->next;
    node->prev = NULL;
    head = node;
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


static inline int hash(int key) {
    return key % MAX;
}
