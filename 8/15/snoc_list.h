#ifndef SNOC_LIST_H
#define SNOC_LIST_H

typedef struct snoc_struct *snoc_list;

snoc_list snoc( snoc_list head, void *tail ) ;
snoc_list head( snoc_list as ) ;
void * tail( snoc_list as ) ;
void sprint( void (*print)( void * ), snoc_list l ) ;

#endif

