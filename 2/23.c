/*

 The n-th Fibonacci number fn is defined by the following
 reccurence relation:

 n, fn  : N
 f0     : 0
 f1     : 1
 fn     : f[n-1] + f[n-2] if n >= 2
 
 Write an SML function `fib` to calculate the n-th Fibonacci number.
 Then, give the corresponding C function and main program to test 
 the C version of `fib` for at least three interesting values of n.

 */

#include <stdio.h>

int fib(int n) {
    if ( n == 0 ) {
        return 0;
    } else if ( n == 1 ) {
        return 1;
    } else {
        return fib(n-1) + fib(n-2);
    }
}

void test(int got, int expected) {
    if (got == expected) {
        printf(" OK ");
    } else {
        printf("  X ");
    }

    printf("got: %d expected: %d\n", got, expected);
}


int main( void ) {
    printf("fib\n");

    test(fib(10), 55);
    test(fib(15), 610);
    test(fib(20), 6765);
    test(fib(25), 75025);

    return 0;
}


