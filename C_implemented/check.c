#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

void func1(node *a) {
    free(a);
}

int main(void) {

    


    return 0;
}
