#include <stdio.h>

int gensum(int k, int n) 
{
    if ( n == 0 ) {
        return 0;
    } else {
        const int d = n / k;
        const int m = n % k;

        return m + gensum(k, d);
    }
}

int pop_count(int n) 
{
    return gensum(2, n);
}

int checksum(int n) 
{
    return gensum(16, n);
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
    test_(checksum(n), expected);
}

int main( void ) 
{
    printf("checksum\n");

    test(17, 2);
    test(18, 3);
    test(1024, 4);
    test(12341234, 59);

    return 0;
}

