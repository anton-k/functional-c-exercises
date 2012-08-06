#include <stdio.h>

int nfib(int n) {
    if ( n == 0 ) {
        return 1;
    } else if ( n == 1 ) {
        return 1;
    } else {
        return 1 + nfib(n-1) + nfib(n-2);   
    }
}


int main( void ) {
    printf("%d\n", nfib(30));

    return 0;
}

/* gcc

$ gcc -Wall -o 24c 24.c
$ time ./24c
2692537

real	0m0.023s
user	0m0.016s
sys	0m0.004s

gcc's score:

8.542129597476283e-9

*/

/* mlton is faster than gcc on function calls by

    0.23 / 0.15  = 1.5(3) 

*/

