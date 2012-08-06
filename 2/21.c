#include <stdio.h>

int pop_count(int x) 
{  
    if ( x == 0 ) {
        return 0;
    } else {
        const int d = x / 2;
        const int m = x % 2;

        return m + pop_count(d);
    }
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


