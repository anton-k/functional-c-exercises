/*

   Exercise 2.25 required the implementation of a `power_of_power`
   function. Reimplement the C function using loops. Try to embed
   the functions into each other so that you don't have 
   an auxiliary function `power`.

sidenote:

   Solution uses simplified version of `power`, not an Indian mwethod
   as in initial exercise. I don't know how to rewrite Indian `power`
   with loops.

*/

#include <stdio.h>

int power_of_power(int m, int n)
{
    int res = 1;

    int i, j;
    for (i = n; i > 0; i--) {
        const int k = res;
        res = 1;
        for (j = 0; j < k; j++) {
            res *= m;
        }
    }

    return res;
}


void test(int got, int expected) {
    if (got == expected) {
        printf(" OK ");
    } else {
        printf("  X ");
    }

    printf("got: %d, expected: %d\n", got, expected);
}


int main( void ) {
    printf("power_of_power\n");

    test( power_of_power(2, 3), 16 );
    test( power_of_power(2, 4), 65536);
    test( power_of_power(3, 2), 27);

    return 0;
}




