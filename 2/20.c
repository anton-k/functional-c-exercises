/*
    Write a program that converts a temperature from 
    Centigrade to     Farehiet: 0'C = 32'F, and 10'C = 50'F. 
    Test it on 0, 28, 37, and 100 degrees of Centigrade.
*/

#include <stdio.h>

int cent2faren(int n) {
    return (int) (1.8 * (double) n + 32.0);
}


void test(int n) {
    printf("%d\'C = %d\'F\n", n, cent2faren(n));
}


int main( void ) {
    test(0);
    test(28);
    test(37);
    test(100);

    return 0;
}


