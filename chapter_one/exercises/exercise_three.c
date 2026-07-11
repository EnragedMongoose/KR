#include <stdio.h>

/* print Fahrenheight-Celsius table
    for fahr = 0, 20, ..., 300 */
int main(void)
{
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;   // lower limit of the tempearute table
    upper = 300; // upper limit
    step = 20;   // step size

    fahr = lower;
    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        printf("Farenheight | Celsius\n");
        printf("%d\t        %d\n", fahr, celsius);
        fahr = fahr + step;
    }
}

// Reason for multiplying by 5 then dividing by 9 instead of just multiplying by
// 5/9 is that in C, in many other languages, integer division truncates: any
// fractional part is discarded. 5/9 would be truncated to 0, and so all Celsius
// temperatures would be reported as 0.

// This is the same as before except for fahr and celsius being floats, to make
// the celcius output accurate, as before 0F would output -17, instead of -17.8C
// %3.0f shows F printed three characters wide with no decimal point and no
// fraction digits. %6.1f tells celsius to be displayed 6 wide with 1 digit
// after the decimal.
