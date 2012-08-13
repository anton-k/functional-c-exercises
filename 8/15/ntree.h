#ifndef NTREE_H
#define NTREE_H

typedef struct ntree_struct *ntree;

ntree lf( int n ) ;
ntree br( snoc_list as ) ;
ntree lfs( int n, ... ) ;
void nprint( ntree t ) ;

#endif
