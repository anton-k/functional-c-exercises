/*
 
 In Exercises 8.13 and 8.14 we have created a data structure, and
 sets of functions operating on the data structure. Package each
 data structure with its associated functions into a separate C module.

 (a) Create a C header file and a C implementation for the snoc lists 
     data type and the functions `snoc`, `head`, `tail`, and `sprint`.

 (b) Create a C header file and a C implementation for the `ntree`
     data type and the functions `nlf`, `nbr` and `nprint`.

 (c) Write a program to test that your modules are usable.
 
 */


#include <stdio.h>

#include "snoc_list.h"
#include "ntree.h"

void print_char( void *c )
{
    printf("'%c'", *(char *)c );
}


int main( void )
{
    printf("snoc list:\n");
    char name[] = "Kate";    
    snoc_list res0 = 
        snoc(
            snoc( 
                snoc( 
                    snoc(NULL, name), 
                    name + 1), 
                name + 2),     
            name + 3);

    sprint( print_char, res0 );
    printf("\n");
    

    printf("\nntree :\n");
    ntree res1 = br(snoc( snoc( NULL, lf(1) ), lfs( 3, 2, 3, 4 )));
    nprint( res1 );
    printf("\n");
    return 0;
}
