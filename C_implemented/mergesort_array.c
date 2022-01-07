#include <stdio.h>
#include <stdlib.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

void merge(int *a, int left, int mid, int right);
void merge_sort(int *a, int left, int right);

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
    merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; ++i) fprintf(out, "%d ", a[i]);


    fclose(in);
    fclose(out);

    return 0;
}

void merge(int *a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *a1 = (int *)malloc(n1 * sizeof(int));
    int *a2 = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; ++i) a1[i] = a[i + left];
    for (int i = 0; i < n2; ++i) a2[i] = a[i + mid + 1];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (a1[i] < a2[j]) {
            a[k] = a1[i];
            ++i;
        } else {
            a[k] = a2[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        a[k] = a1[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        a[k] = a2[j];
        ++j;
        ++k;
    }
    free(a1);
    free(a2);
}

void merge_sort(int *a, int left, int right) {
    if (left == right) return;
    int mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);
    merge(a, left, mid, right);
}
