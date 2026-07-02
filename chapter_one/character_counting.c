#include <stdio.h>

int main(void)
{
    double nc;
    for( nc = 0; getchar() != EOF; ++nc) 
        ; // emtpy statement, a null value. Required by C, placed here for visibility.
    printf("%.0f\n", nc);  // .0f supresses any decimal points. f is used for both float and double
}


// need to output by piping, ex: echo -n "hello" | ./c



