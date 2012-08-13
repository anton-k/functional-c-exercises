/*
 
 Write a higher order polymorphic version of the quicksort 
 function from Chapter 7 that takes a comparison function
 as an argument so that it can sort an array of any data type.
 
 */

/* Let's try to reinvent the `qsort` */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef int (*fn_cmp)( const void *, const void * );

typedef struct {
    void   *base;
    size_t size;
    fn_cmp cmp;
    void   *swap_place;
} sort_api;


sort_api *sort_api_init( void *base, size_t size, fn_cmp cmp )
{
    sort_api *res = malloc( sizeof(sort_api) );
    res->base = base;
    res->size = size;
    res->cmp  = cmp;
    res->swap_place = malloc( size );
    return res;
}

void sort_api_free( sort_api *a )
{
    free( a->swap_place );
    free( a );
}

static void *nth( const sort_api *a, int n )
{
    return a->base + n * a->size;
}


static void swap( sort_api *a, int i, int j )
{
    void 
        *p1 = nth( a, i ),
        *p2 = nth( a, j ),
        *k  = a->swap_place;

    memcpy(  k, p1, a->size );
    memcpy( p1, p2, a->size );
    memcpy( p2,  k, a->size );
}

static void _my_qsort( sort_api *api, int l, int r ) ;
static void partition( 
    int p, void *data_p, sort_api *data, 
    int l, int *i, int *j, int r ) ;

static int up( void *data_p, sort_api *data, int i, int r );
static int down( void *data_p, sort_api *data, int l, int j );


void my_qsort( void *base, size_t n, size_t size, fn_cmp cmp)
{
    sort_api *api = sort_api_init( base, size, cmp );
    _my_qsort( api, 0, n-1 );
    sort_api_free( api );
}


static void _my_qsort( sort_api *api, int l, int r ) 
{
    if ( l < r ) {
        int p = l;
        void *data_p = nth( api, p );
        int i = l;
        int j = r;
        partition( p, data_p, api, l, &i, &j, r );
        _my_qsort( api, l, j );
        _my_qsort( api, i, r );
    }
}

static void partition( 
    int p, void *data_p, sort_api *data, 
    int l, int *i, int *j, int r ) 
{
    while (true) {
        *i = up(   data_p, data, *i, r );
        *j = down( data_p, data, l, *j );
        if ( *i < *j ) {
            swap( data, *i, *j );
            (*i)++;
            (*j)--;
        } else if ( *i < p ) {
            swap( data, *i, p );
            (*i)++;
            return ;
        } else if ( p < *j ) {
            swap( data, *j, p );
            (*j)--;
            return ; 
        
        } else {
            return ;
        }
    }
}

static int up( void *data_p, sort_api *data, int i, int r )
{
    while ( i < r && (data->cmp)(nth( data, i), data_p) <= 0 ) {
        i++;
    }
    return i;
}

static int down( void *data_p, sort_api *data, int l, int j )
{
    while ( l < j && (data->cmp)( nth( data, j ), data_p ) >= 0 ) {
        j--;    
    }
    return j;
}


int cmp_int( const void *a, const void *b )
{
    return *(int *) a - *(int *) b;
}

int main( void )
{
    const int vec[7] = { 2, 4, 1, 5, 3, 6, 0 };
    my_qsort( (void *) vec, 7, sizeof(int), cmp_int );

    int i;
    for ( i = 0; i < 7; i++ ) {
        printf("%d ", vec[i]);
    }
    printf("\n");

    return 0;
}

