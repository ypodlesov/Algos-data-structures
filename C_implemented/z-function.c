#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

int *z_func(char *s);
int min(int a, int b);
int max(int a, int b);

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;

    // for (int i = 0; i < 1000000; ++i) fprintf(in, "a");
    char s[1000006];
    fscanf(in, "%s", s);
    // printf("Hello\n");
    int *z = z_func(s);
    int n = strlen(s);
    for (int i = 0; i < n; ++i) fprintf(out, "%d ", z[i]);
    printf("\n");



    fclose(in);
    fclose(out);

    return 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int *z_func(char *s) {
    int len = strlen(s);
    int *z = (int *)calloc(len, sizeof(int));
    z[0] = len;
    for (int i = 1, l = 0, r = 0; i < len; ++i) {
        // "l" is the beginning and "r" is the ending of "z-block"
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < len && s[i + z[i]] == s[z[i]]) ++z[i];
        if (i + z[i] > r) { // updates the "r" if it is needed
            l = i;
            r = l + z[l];
        }
    }
    return z;
}
