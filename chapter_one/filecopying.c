#include <stdio.h>

int main(void) 
{

    int c;  

    c = getchar();      // getchar() reads the next input character from a text stream and returns the value
    while (c != EOF) { //  
        putchar(c);   // putchar() prints a character each time
        c = getchar();
    }
}


// int is used for c: c must be a type big enough to hold any value getchar() returns
// EOF is a value that cannot be confused with any other character



int main(void) 
{
    int c;

    while ((c = getchar()) != EOF)
        putchar(c);
}


 // concise way of writing the same program
