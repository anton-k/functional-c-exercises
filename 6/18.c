/*
 
 Give the specification of reversing a sequence and implement an
 efficient function `reverse` to operate on type `char_list`

 */

/* 
-- specification
 
reverse :: [a] -> [a]
reverse xs = go [] xs
    where go res xs = case xs of
            []      -> res
            a:as    -> go (a:res) as
 
 */

#include <stdio.h>
#include <stdlib.h>

#define char_list_size sizeof(struct list_char)

typedef struct list_char {
    char list_head;
    struct list_char *list_tail;
} *char_list;


char head( char_list as )
{
    return as->list_head;
}

char_list tail( char_list as )
{
    return as->list_tail;
}

char_list cons( char a, char_list as )
{
    char_list res = malloc( char_list_size );
    if ( res == NULL ) {
        printf("cons: out of memory");
        abort();    
    }
    res->list_head = a;
    res->list_tail = as;
    return res;
}


char_list reverse( char_list as )
{
    char_list res = NULL;
    char_list *last = &res;

    while ( as != NULL ) {        
        char_list new = cons( head( as ), *last );
        last = &new;
        as = tail( as );
    }

    return *last;
}


void print_list( char_list as )
{
    while ( as != NULL ) {
        printf("%c:", head( as ) );
        as = tail( as );    
    }
    printf("\n");
}

int main( void ) 
{
    char_list hi  = cons('K', cons('a', cons('t', cons( 'e', NULL))));
    char_list bye = reverse( hi );

    print_list(hi);
    print_list(bye);

    return 0;
}


