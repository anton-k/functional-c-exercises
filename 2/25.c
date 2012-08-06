#include <stdio.h>
#include <stdbool.h>

bool odd(int x) {
    return 1 == (x % 2);
}

bool even(int x) {
    return 0 == (x % 2);
}


int square_int(int x) {
    return x * x;
}

int power(int n, int m) {
    if (m == 0) {
        return 1;
    } else {
        if ( odd(m) ) {
            return n * power(n, m-1);
        } else {
            return square_int( power(n, m / 2) );
        }
    }
}


int power_of_power(int m, int n) {
    if ( n == 0 ) {
        return 1;
    } else {
        return power(m, power_of_power(m, n-1));
    }
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




