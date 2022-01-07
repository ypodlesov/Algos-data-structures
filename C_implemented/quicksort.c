#include <stdio.h>
#include <stdlib.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

void swap(int *a, int *b);
void quick_sort(int *a, int left, int right);
int partition(int *a, int left, int right);

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
    quick_sort(a, 0, n-1);
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

void quick_sort(int *a, int left, int right) {
    if (left > right) return;
    int mid = partition(a, left, right);
    quick_sort(a, left, mid - 1);
    quick_sort(a, mid + 1, right);
}

int partition(int *a, int left, int right) {
    int j = left - 1;
    int key = a[right];
    for (int i = left; i < right; ++i) {
        if (a[i] <= key) {
            ++j;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[j+1], &a[right]);
    return j + 1;
}
