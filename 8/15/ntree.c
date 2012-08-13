
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "snoc_list.h"
#include "ntree.h"

/*----------------------------------------------------------*/
/* ntree */

#define ntree_size sizeof( struct ntree_struct )

typedef enum { Br, Lf } ntree_tag;

struct ntree_struct {
    ntree_tag tag;

    union {
        int lf;
        snoc_list br;
    } at;
};


ntree lf( int n ) 
{
    ntree res = malloc( ntree_size );
    res->tag = Lf;
    res->at.lf = n;
    return res;
}

ntree br( snoc_list as )
{
    ntree res = malloc( ntree_size );
    res->tag = Br;
    res->at.br = as;
    return res;
}

ntree lfs( int n, ... )
{
    ntree res = malloc( ntree_size );
    res->tag = Br;

    va_list args;
    va_start( args, n );

    int i;
    snoc_list list = NULL;
    for ( i = 0; i < n; i++ ) {
        int elem = va_arg( args, int );
        list = snoc( list, lf(elem) );
    }
    va_end( args );

    res->at.br = list;
    return res;
}

static void nprint_( void * );

void nprint( ntree t )
{
    switch ( t->tag ) {
        case Lf     : printf("%d", t->at.lf); 
                      break;
        case Br     : sprint( nprint_, t->at.br );
                      break;
    
        default     : abort();
    }
}

static void nprint_( void *v )
{
    nprint( (ntree)v );
}


