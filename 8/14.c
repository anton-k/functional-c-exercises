/*
 
 An n-ary tree is a generalisation of a binary treewhich has n
 branches at each interior node rather than two. The following SML
 data represents an n-ary tree with integer values at the leafs.
 Here we have chosen to use snoc list from previous exercise.

 ~~~
 datatype ntree = Br of (ntree snoc_list)
                | Lf of int ;   
 ~~~
 
 Here is a sample `ntree`:

 ~~~
                |
             +--+--+
             |     |
             1  +--+--+
                |  |  |
                2  3  4

 ~~~

 In an SML program, the sample `ntree` could be created as follows:

 ~~~
 val sample 
    = let
         val 1234 = Snoc( Snoc( Snoc( Nil, Lf 2 ),
                                Lf 3
                               ),
                           Lf 4
                        )
      in
         Br (Snoc( Snoc( Nil, Lf 1 ),
                       ( 1234 )
                 )
      end ;
 ~~~

 (a) Give an equivalent type definition of the SML `ntree` above
     in C. Use the `snoc_list` as defined in the previous exercise.

 (b) Write a C function `elf` to create a leaf from a given integer
     key value. Also write a C function `nbr` to construct a branch
     from a given snoc list of n-ary trees.

 (c) Write a function `nprint` with this prototype:

     ~~~
     void nprint( ntree t );
     ~~~

     Your function should print `ntree` as follows: 

     1. For each leaf print the key value kept in the leaf.

     2. Print all elements of a snoc list of branches enclosed
        in parentheses. Use the function `sprint` from the
        previous exercise.

     The sample `ntree` above should be printed as: (1, (2,3,4)).

 (d) Write a C `main` function to create the sample `ntree` above
     and print it using `nprint`.               

 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/*----------------------------------------------------------*/
/* snoc list */

typedef struct snoc_struct {
   void               * snoc_tail;
   struct snoc_struct * snoc_head;
} *snoc_list ;
 
snoc_list snoc( snoc_list head, void *tail )
{
    snoc_list res = malloc( sizeof( struct snoc_struct ) );
    res->snoc_head = head;
    res->snoc_tail = tail;
    return res;
}

snoc_list head( snoc_list as )
{
    return as->snoc_head;
}

void * tail( snoc_list as )
{
    return as->snoc_tail;
}

void sprint_( void (*print)( void * ), snoc_list l ) 
{
    if (l != NULL) {
        sprint_( print, head(l) );
        if (head(l) != NULL ) {
            printf(",");
            print( tail(l) );
        } else {
            print( tail(l) );
        }
    }
}

void sprint( void (*print)( void * ), snoc_list l )
{
    printf("(");  sprint_( print, l );   printf(")"); 
}

/*----------------------------------------------------------*/
/* ntree */

#define ntree_size sizeof( struct ntree_struct )

typedef enum { Br, Lf } ntree_tag;

typedef struct ntree_struct {
    ntree_tag tag;

    union {
        int lf;
        snoc_list br;
    } at;
} *ntree;


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

void nprint_( void * );

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

void nprint_( void *v )
{
    nprint( (ntree)v );
}


int main( void )
{
    ntree res = br(snoc( snoc( NULL, lf(1) ), lfs( 3, 2, 3, 4 )));
    nprint( res );
    return 0;
}
