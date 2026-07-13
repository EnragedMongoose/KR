#include <stdio.h>

int main(void)
{
    int c, d;
    c = getchar();
    d = c;
    while (c != EOF) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
            c = getchar();
        } else if (c == '\b') {
            putchar('\\');
            putchar('b');
            c = getchar();
        } else if (c == '\\') {
            putchar('\\');
            putchar('\\');
            c = getchar();
        } else {
            putchar(c);
            c = getchar();
        }
    }
}
