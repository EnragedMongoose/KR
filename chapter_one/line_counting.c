#include<stdio.h>

int main(void)
{
    int c, nl;

    nl = 1;
    while((c = getchar()) != EOF)
        if (c == '\n')
        ++nl;
    printf("%d\n", nl);
}

