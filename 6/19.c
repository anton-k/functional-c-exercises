/*
 
 In this exercise, binary trees will be implemented.

 (a) Give an equivalent definition in C of the following
     SML data type:

     ~~~
     datatype tree = Branch of (tree * tree)   
                   | Leaf   of int ;
     ~~~
 
 (b) Write a C function `mkLeaf` to create a leaf node
     of the `tree` type. The function `mkLeaf` should
     have the following prototype:

     ~~~
     tree_ptr mkLeaf( int leaf );
     ~~~

     Also write a function `mkBranch` with the prototype
     below to create an interior node:

     ~~~
     tree_ptr mkBranch( tree_ptr left, tree_ptr right ) ;
     ~~~

 (c) Write a recursive C function to print a tree as follows:   

     * For each leaf, print its key value.

     * For each branch, print its left branch and its right 
       branch, separated by a comma and enclosed in parentheses.
       As an example, the tree below should be printed as (1, (2, 3)).

                               |
                            +--+--+
                            |     |
                            1  +--+--+
                               |     |
                               2     3

 (d) A binary tree can be rotated by swapping the left and right 
     fields at every interior node. For example:

     ~~~
     rotate (Branch (Leaf(1), Leaf(2)))
          =  Branch (Leaf(2), Leaf(1))
     rotate (Leaf(0))
          =  Leaf(0)
     ~~~

     First write a function `rotate` in SML. Then write a C function
     with exactly he same functionality as the SML function, that is,
     make sure that the original tree is not destroyed.

 */


#include <stdlib.h>
#include <stdio.h>

#define new_tree malloc( sizeof( struct _tree ) )

typedef enum { 
    Branch, Leaf 
} tree_tag;

typedef struct _tree {
    tree_tag tag;
    union {
        struct {
            struct _tree *left, *right;
        } branch;

        int leaf;
    } at;
} *tree;

void check_ptr( void *ptr, const char *fun_name )
{
    if ( ptr == NULL ) {
        printf("%s: out of memory\n", fun_name);
        abort();
    }
}

tree mkLeaf( int a )
{
    tree res = new_tree;
    check_ptr(res, "mkLeaf");

    res->tag = Leaf;
    res->at.leaf = a;
    return res;
}

tree mkBranch( tree left, tree right )
{
    tree res = new_tree;
    check_ptr(res, "mkBranch");

    res->tag = Branch;
    res->at.branch.left = left;
    res->at.branch.right = right;
    return res;
}

/* getters */
int  get_leaf( tree a )     { return a->at.leaf;         }
tree get_left( tree a )     { return a->at.branch.left;  }
tree get_right( tree a )    { return a->at.branch.right; }


void tree_free( tree a )
{
    tree t1, t2;
    switch ( a->tag ) {
        case Leaf   : free( a ); break;
        case Branch : 
            t1 = get_left( a );
            t2 = get_right( a );
            free( a );
            tree_free( t1 );
            tree_free( t2 );
            break;
    
        default     : abort();
    }
}

void tree_print( tree a )
{
    switch ( a->tag ) {
        case Leaf   : 
            printf("%d", get_leaf(a)); 
            break;
        case Branch : 
            printf("("); 
            tree_print( get_left(a) );
            printf(", ");
            tree_print( get_right(a) );
            printf(")");
            break;

        default     : abort();  
    }
}

/* SML
 
datatype tree = Branch of (tree * tree)
              | Leaf   of int ;

(* tree -> tree *)
fun rotate (Branch (left, right)) 
                        = Branch (rotate right, rotate left)
  | rotate (Leaf (a))   = Leaf (a) 
 
 */

tree rotate( tree a )
{
    switch ( a->tag ) {
        case Leaf   : return mkLeaf( get_leaf( a ) ); 
        case Branch : return mkBranch( 
                        rotate( get_right( a ) ),
                        rotate( get_left( a ) ) ); break;

        default     : abort();
    }
}



int main( void ) 
{
    tree t1 = mkBranch(
                mkLeaf(1),
                mkBranch(
                    mkLeaf(2),
                    mkLeaf(3))            
            ),
         t2 = rotate( t1 );

    tree_print( t1 );
    printf("\n");
    tree_print( t2 );
    printf("\n");

    tree_free(t1);
    tree_free(t2);

    return 0;
}





