#include <stdio.h>
#define IN 1
#define OUT 0

int main(void)
{
    int c, state, n;
    n = 0;
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            putchar('\n');
            state = IN;
            putchar(c);
        } else {
            putchar(c);
        }
    }
}
