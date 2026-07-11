#include <stdio.h>

int main(void)
{
    int c, d;
    c = getchar();
    d = c; // for some reason I thought this needed to be initalized within the
           // while loop.
    while (c != EOF) {
        if (c != ' ') {
            putchar(c);
            d = c;
            c = getchar();
        } else if (d == ' ') {
            c = getchar();
        } else {
            d = c;
            putchar(c);
            c = getchar();
        }
    }
}
