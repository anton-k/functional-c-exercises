/*
 
 Functions with a small domain are often implemented using 
 a *memo* table. For each value in the domain, one would keep
 the coresponding function value. Instead of computing the value,
 it is merely looked up. The factorial function is a good example
 of a function with a small domain. Here is a table for some of its
 values:

 +======+=============+
 | n    |          n! |
 +======+=============+
 | 1    |          1  |
 +------+-------------+
 | 2    |          6  |
 +------+-------------+
 | ..   |         ..  |
 +------+-------------+

  The function values grow so quickly that, with 32-bit arithmetic, 
  overflow occurs for 13!. Thus a table of 12 values is sufficient 
  to maintain the entire domain and range of the factorial function 
  for 32-bit arithmetic. 

  Write a function that uses an array as a memo table. Your function
  should compute apropriate values just once, and it shouldn't compute
  more values than it's strictly necessary. When the argument is beyond
  the domain, your function should abort.
 
 */

#include <stdlib.h>
#include <stdio.h>


int fac( int n )
{
    static int table[13] = { 1 };    
    static int computed_so_far = 0;

    if (n < 0 || n > 12 ) { 
        printf( "fac: value %d is out of domain\n", n );
        abort(); 
    }   

    if ( n <= computed_so_far ) {
        printf("easy\n");
        return table[n];    
    } else {
        printf("busy\n");
        int i = computed_so_far;
        for ( ; i < n; i++ )
            table[ i + 1 ] = (i + 1) * table[ i ];       

        computed_so_far = n;
        return table[n];
    }
}

int main( void )
{
    int i;
    for ( i = 12; i > 0; i--)
        printf( "%3d %10d\n", i, fac(i) );

    return 0;
}


