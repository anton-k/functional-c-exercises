#include <stdlib.h>
#include <stdio.h>

#include "snoc_list.h"

/*----------------------------------------------------------*/
/* snoc list */

struct snoc_struct {
   void               * snoc_tail;
   struct snoc_struct * snoc_head;
};
 
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

static void sprint_( void (*print)( void * ), snoc_list l ) 
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

