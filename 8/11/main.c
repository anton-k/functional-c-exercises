
/*
 
 Exercise 8.7 requiered the implementation of a dynamic array
 of integers. Define a module that implements a polymorphic
 dynamic array. Upon the creation of an array, the size of
 the data elements is passed, subsequent functions (for indexing 
 and bound changes) do not need extra parameters. 
 
 */

#include <stdio.h>

#include "array.h"

void print_double( void *a )
{
    printf("%7.4f ", *(double *)a);
}

int main( void )
{
    const double ds[10] = {0,1,2,3,4,5,6,7,8,9};
    array *q = array_init( 5, sizeof(double) );

    /* write value */
    printf("write value\n");
    array_fill( q, ds + 2 );
    array_write(q, 4, ds);
    array_foreach( q, print_double );
    printf("\n");

    /* read value */
    printf("read value\n");
    double d;
    array_write( q, 3, ds + 9 );
    array_read( q, 3, &d );
    printf(" %d %5.4f \n", 3, d);

    /* rebound */
    printf("rebound\n");
    array_rebound( q, 7 );
    array_write( q, 5, ds + 3 );
    array_write( q, 6, ds + 4 );
    array_foreach( q, print_double );
    printf("\n");

    array_free( q );

    return 0;
}




