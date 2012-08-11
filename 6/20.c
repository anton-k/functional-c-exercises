/*
 
 It is interesting to try to simulate SML style pattern matching
 in C. In this exercise we are going to develop a general system 
 to support this. Let us look again at the definition of a character
 list and a typical SML function, `head` that uses pattern matching:

 ~~~
 datatype char_list = Nil
                    | Cons of (char * char_list) ;

 (* head : char_list -> char *)
 fun head (Cons(x,xs)) = x ;
 ~~~

 Firstly. the `head` function needs to analyse its argument so 
 as to check that it is of the form `Cons (...,...)` and not
 of the form `Nil`. Secondly, the `head` function has to bind 
 the value of the first component of the `Cons` constructor to
 the variable `x`. It the also binds the value of the second 
 component to the variable `xs`, even though the later is not
 used on the right hand side of the definition of `head`. Our
 task is to provide support in C for these two activities: case
 analysis and binding.

 (a) Study the following two type definitions carefully and 
     relate the various elments of the definition to the 
     two activities identified before:

 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define tree_ptr_size sizeof( struct tree_struct )

typedef enum { Bind, Data } tree_tag;

typedef struct tree_struct {
    tree_tag tag;

    union {
        struct tree_struct * bind ;         /* Bind */    
        struct data_struct {                /* Data */
            char key;
            int size;
            struct tree_struct ** data ;
        } comp;
    } at;
 
} *tree_ptr;
 
/*

 (b) Write two functions `mkBind` and `mkData` to allocate
     appropriate version of the `tree_struct` on the heap. 
     Use the `vararg` facility so that the function takes 
     an arbitrary number (possibly zero) of sub trees, and
     `calloc` to allocate sufficient memory to hold the 
     pointers to the subtrees. The required prototypes of 
     the functiond are shown below:

*/
     
tree_ptr mkBind( tree_ptr b );
tree_ptr mkData( char k, int s, ... ) ;
     
/*
 
 (c) Write a function `match` with the prototype given below:
*/
     
bool match( tree_ptr pat, tree_ptr exp ) ;
     
     
/*
     The function should compare the two trees and return `true`
     if they match, `false` otherwise. Two trees `pat` and `exp`
     match if:

     * Both have tag `Data` and if both the same `key` and `size`.
       In addition, all subtrees must match.

     * If the argument `pat` has tag `Bind`. In that case, 
       the field `bind` should be set to remember the value 
       of `exp`. You may assume that there are no nodes with 
       tag `Bind` in the trees offered as the second argument 
       to `match`.
    
 (d) Write a `main` function to create some sample patterns
     and expressions to test your `match` function.

 */


void check_ptr( void *ptr, const char *fun_name )
{
    if ( ptr == NULL ) {
        printf("%s: out of memory\n", fun_name);
        abort();
    }
}

tree_ptr mkBind( tree_ptr b )
{
    tree_ptr res = malloc( tree_ptr_size );                 /* M */
    check_ptr( res, "mkBind" );
    res->tag = Bind;
    res->at.bind = b;
    return res;
}

tree_ptr mkData( char key, int size , ... )
{
    tree_ptr res = malloc( tree_ptr_size );                 /* M */
    check_ptr( res, "mkData" );

    res->tag = Data; 
    res->at.comp.key = key;
    res->at.comp.size = size;
    res->at.comp.data = calloc( size, tree_ptr_size );      /* M */
    check_ptr( res->at.comp.data, "mkData" );

    va_list args;    
    va_start( args, size );

    int i;
    for ( i = 0 ; i < size; i++ ) 
        res->at.comp.data[i] = va_arg( args, tree_ptr );    

    va_end( args );
    return res;
}

void tree_ptr_free( tree_ptr t)
{
    switch ( t->tag ) {
        case Bind   : free( t ); 
                      break;
        case Data   : free( t->at.comp.data ); 
                      free( t ); 
                      break;
    
        default     : abort();
    }          
}

void tree_ptr_frees( int n, ... )
{
    va_list args;
    va_start( args, n );
    
    int i;
    for ( i = 0; i < n; i++ ) 
        tree_ptr_free( va_arg( args, tree_ptr ) );

    va_end( args );
}

bool matchData( tree_ptr pat, tree_ptr exp )
{
    if (    pat->at.comp.key  == exp->at.comp.key 
         && pat->at.comp.size == exp->at.comp.size ) {

        int n = pat->at.comp.size;
        int i;
        for ( i = 0; i < n; i++ ) {
            if (! match( pat->at.comp.data[i], 
                         exp->at.comp.data[i] ) ) {
                return false;            
            }       
        }
        return true;
    } else {
        return false;    
    }
}

bool match( tree_ptr pat, tree_ptr exp )
{
    switch ( pat->tag ) {
        case Bind   : pat->at.bind = exp;
                      return true;
        case Data   : return matchData( pat, exp );
    
        default     : abort();
    }        
}



int main( void ) 
{
    tree_ptr 
        t1 = mkData( 'A', 0 ), 
        t2 = mkData( 'B', 0 ),
        t3 = mkData( 'C', 2, t1, t2 ),
        t4 = mkData( 'D', 1, t3 ),

        p1 = mkData( 'A', 0 ),
        p2 = mkBind( NULL ),
        p3 = mkData( 'C', 2, p1, p2 ),
        p4 = mkData( 'D', 1, p3 );

    bool res = match(p4, t4);
    printf("%d\n", res);
    
    tree_ptr_frees( 8, 
        t1, t2, t3, t4, 
        p1, p2, p3, p4 );
    return 0;
}

