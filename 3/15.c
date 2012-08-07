/*
 
   The functio `sum_of_sum_of_powers` is rather inefficient
   if it uses a naive `power` function, that is one that 
   performs `k` multiplications to compute `i^k`. 
   Rewrite `sum_of_sum_of_powers` such that it completely
   avoids the use of `power` function, and thus makes the least
   possible number of multiplications.

*/

#include <stdio.h>

/* initial definition */

int power(int m, int n){
    int res = 1;
    int i;
    for (i = 0; i < n; i++) {
        res *= m;
    }

    return res;
}

int slow_sum_of_sum_of_powers(int m, int n)
{
    int i, k; 
    int accu = 0;

    for (i = 0; i <= m; i++) {
        for (k = 0; k <= n; k++) {
            accu += power(i, k);
        }
    }

    return accu;
}

/* solution */


int sum_of_sum_of_powers(int m, int n)
{
    int res = 0;
    int cur = 1; /* curent value of power */

    int i, k;
    for (i = 0; i <= m; i++) {
        cur = 1;        
        for (k = 0; k <= n; k++) {
            res += cur;
            cur *= i;
        }
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

void test(int n) 
{
    test_(sum_of_sum_of_powers(n, n), slow_sum_of_sum_of_powers(n, n));
}

int main( void )
{    
    printf("sum_of_sum_of_powers\n");
    test_(sum_of_sum_of_powers(4, 5), 1799);

    printf("slow == fast\n");
    test(4);
    test(6);
    test(8);
    
    return 0;
}


