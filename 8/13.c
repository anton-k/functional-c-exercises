/*

 A snoc list is an alternative representation of a list, which stores
 the head and the tail of the list in reverse order. Here is the SML
 definition of the snoc list:

 ~~~
 datatype 'a snoc_list = Snoc of ('a snoc_list * 'a)
                       | Nil ;
 ~~~

 Three numbers 1, 2,and 3 could be gathered in a snoc list as follows:

 ~~~
 Snoc(Snoc(Snoc(Nil,1),2),3) ;
 ~~~

 An equivalent ordinary list representation would be:

 ~~~
 Cons(1,Cons(2,Cons(3,Nil))) ;
 ~~~

 This uses the following definition of a polymorphic list:

 ~~~
 datatype 'a list = Nil
                  | Cons of ('a * 'a list) ;
 ~~~

 Note that in both representations the order of the elements 
 is always 1, 2, 3. Here is the C data structure that we will
 be using to represent snoc lists:

 */

typedef struct snoc_struct {
   void               * snoc_tail;
   struct snoc_struct * snoc_head;
} *snoc_list ;
 
/*
 
 (a) Define the C functions `snoc`, `head` and `tail` similar to
     those at the beggining of this chapter 6, but associated with 
     the type `snoc_list`
     
 (b) Create a higher order C function `sprint` with the following
     prototype:
*/
  
void sprint( void (*print)( void * ), snoc_list l ) ;

/*
 
     The purpose of this function is to print all elements of the snoc 
     list and in the correct order. Use a comma to separate the elements 
     when printed. 


 (c) Write a main function to test your snoc list type and the associated 
     functions.
 */

#include <stdlib.h>
#include <stdio.h>

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

void print_char( void *c )
{
    printf("'%c'", *(char *)c );
}



int main( void )
{
    char name[] = "Kate";
    
    snoc_list res = 
        snoc(
            snoc( 
                snoc( 
                    snoc(NULL, name), 
                    name + 1), 
                name + 2),     
            name + 3);

    sprint( print_char, res );
    printf("\n");
    
    return 0;
}



