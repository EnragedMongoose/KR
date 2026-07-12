#include <stdio.h>
#define IN 1
#define OUT 0
int main(void)
{
    int c, n, state;
    state = OUT;
    n = 0;
    while ((c = getchar()) != EOF) {
        if (n == 0)
            putchar(c);
        if (c != ' ' || c != '\n' || c != '\t')
            n = n - n;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            n++;
        }
    }
}
