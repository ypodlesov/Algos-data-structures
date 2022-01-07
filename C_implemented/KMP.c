#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

int *prefix(char *s);

void kmp(char *t, char *s);

int main(void) {

    FILE *in, *out;
    // char nin[] = "input.txt", nout[] = "output.txt";
    // in = fopen(nin, "r");
    // out = fopen(nout, "w");
    in = stdin;
    out = stdout;

    char s[50005], t[50005];
    fscanf(in, "%s%s", t, s);
    kmp(t, s);
    printf("\n");

    fclose(in);
    fclose(out);


    return 0;
}

int *prefix(char *s) {
    int l = strlen(s);
    int *p = (int *)calloc(l + 1, sizeof(int));
    p[0] = -1;
    for (int i = 1; i <= l; ++i) {
        int k = p[i-1];
        while (k >= 0) {
            if (s[k] == s[i-1]) break;
            else k = p[k];
        }
        p[i] = k + 1;
    }
    return p;
}

void kmp(char *t, char *s) {
    int n = strlen(t);
    int m = strlen(s);
    int *p = prefix(s);
    int k = 0;
    for (int i = 1; i <= n; ++i) {
        while (k >= 0 && s[k] != t[i - 1]) k = p[k];
        ++k;
        if (k == m) {
            printf("%d ", i - k);
            k = p[k];
        }
    }
}
