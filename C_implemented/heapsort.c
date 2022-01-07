#include <stdio.h>
#include <stdlib.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

void swap(int *a, int *b);
void max_heapify(int *a, int i, int n);
void build_max_heap(int *a, int n);
void heap_sort(int *a, int n);

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;

    int n;
    fscanf(in, "%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) fscanf(in, "%d", &a[i]);
    heap_sort(a, n);
    for (int i = 0; i < n; ++i) fprintf(out, "%d ", a[i]);





    fclose(in);
    fclose(out);

    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void max_heapify(int *a, int i, int n) {
    int left = i * 2;
    int right = i * 2 + 1;
    int largest = i;
    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(&a[i], &a[largest]);
        max_heapify(a, largest, n);
    }

}
void build_max_heap(int *a, int n) {
    for (int i = n / 2; i >= 0; --i) max_heapify(a, i, n);
}

void heap_sort(int *a, int n) {
    build_max_heap(a, n);
    int heap_size = n;
    for (int i = n-1; i > 0; --i) {
        swap(&a[i], &a[0]);
        --heap_size;
        max_heapify(a, 0, heap_size);
    }
}
