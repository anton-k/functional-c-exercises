/*
    
   Exercise 2.21 required the implementation of a `pop_count` function.
   Implement this function in C with a loop.

*/

#include <stdio.h>


int pop_count(int x)
{
    int res = 0;

    while ( x != 0 ) {
        res += x % 2;
        x   /= 2;
    }

    return res;
}


void test_(int got, int expected) {
    if (got == expected) {
        printf(" OK ");
    } else {
        printf("  X ");
    }

    printf("got: %d, expected: %d\n", got, expected);
}

void test(int n, int expected) 
{
    test_(pop_count(n), expected);
}

int main( void ) {    
    printf("\npopulation count:\n");
    test(3,2);
    test(32,1);
    test(1027,3);
    test(0,0);
    test(1,1);

    return 0;
}



