#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct array_struct array;

array *array_init( int n, size_t size );
void array_free( array *a );

void array_read( const array *arr, int n, void *dst );
void array_write( array *arr, int n, const void *src );

void array_fill( array *arr, const void *src );
void array_foreach( array *arr, void (*f)( void * )  );

void array_rebound( array *arr, int new_length );

#endif

