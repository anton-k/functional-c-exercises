
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"

#define array_size sizeof(array)


struct array_struct {
    void   *mem;
    size_t size;
    int    length;
};


array *array_init( int n, size_t size )
{
    array *res = malloc( array_size );
    res->mem = malloc( n * size );
    res->size = size;
    res->length = n;
    return res;
}

void array_free( array *a )
{
    free(a->mem);
    free(a);
}

void out_of_bounds( const array *arr, int n )
{
    printf( "array_read: out of bounds, index is %d" 
            "but length is %d", n, arr->length );
}

void array_read( const array *arr, int n, void *dst )
{
    if ( 0 <= n && n < arr->length ) {
        memcpy( dst, arr->mem + n * arr->size, arr->size );
    } else {
        out_of_bounds(arr, n);
    }
}

void array_write( array *arr, int n, const void *src )
{
    if ( 0 <= n && n < arr->length ) {
        memcpy( arr->mem + n * arr->size, src, arr->size );
    } else {
        out_of_bounds(arr, n);
    }
    
}

void array_fill( array *arr, const void *src )
{
    int i;
    for ( i = 0; i < arr->length; i++ )
        array_write( arr, i, src );
}

void array_foreach( array *arr, void (*f)( void * )  )
{
    int i;
    for ( i = 0; i < arr->length; i++ )
        f( arr->mem + i * arr->size ); 
}


int int_min( int a, int b )
{
    return ( a < b ) ? a : b ;
}

void array_rebound( array *arr, int new_length )
{
    void *new_mem = malloc( new_length * arr->size );
    memcpy( new_mem, arr->mem, 
        arr->size * int_min( new_length, arr->length ) );
    free( arr->mem );
    arr->mem = new_mem;
    arr->length = new_length;
}

