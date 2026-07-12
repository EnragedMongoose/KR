#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */

int main(void)
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc; // adds to  character count.
        if (c == '\n')
            ++nl; // adds to line count.
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT; // spaces and tabs exit words, but \n does too and
        else if (state == OUT) { // is why it is a condition again. Keep the
                                 // purpose of the code
            state = IN;          // in mind
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}
