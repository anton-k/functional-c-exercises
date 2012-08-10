/*
 
 Write a program that calculates the magic squares.

 I've tried a brute force with random walk, but it doesn't
 work. There have to be some standard algorithm.. 
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *vals;
    int order;
} square; 


int rand_index( square *a )
{
    return rand() % a->order;    
}

void swap( int *a, int i, int j )
{
    int k = a[i];
    a[i] = a[j];
    a[j] = k;
}

void permute( square *a )
{
    swap(a->vals, rand_index( a ), rand_index( a ) );
}

int square_sum_row( square *a, int k )
{
    const int n = a->order;
    int i, 
        res = 0;

    int *p = a->vals + n * k;
    for ( i = 0; i < n; i++ ) {
        res += *p++;
    }

    return res;
}

int square_sum_col( square *a, int k )
{
    const int n = a->order;
    int i,
        res = 0;

    int *p = a->vals + k;
    for ( i = 0; i < n; i++ ) {
        res += *p;
        p   += n;
    }

    return res;
}

int square_sum_diag0( square *a ) 
{
    const int n = a->order;
    int i,
        res = 0;

    int *p = a->vals;
    const int step = n + 1;
    for ( i = 0; i < n; i++ ) {
        res += *p;
        p   += step;
    }

    return res;
}

int square_sum_diag1( square *a ) 
{
    const int n = a->order;
    int i,
        res = 0;
    
    int *p = a->vals + n - 1;
    const int step = n - 1;
    for ( i = 0; i < n; i++ ) {
        res += *p;
        p   += step;
    }

    return res;
}

bool is_magic( square *a ) 
{
    const int sum = square_sum_row( a, 0 );
    const int n = a->order;

    int i;
    for ( i = 1; sum == square_sum_row( a, i ) && i < n; i++ ) ;
    if (i < n) { return false; }
    
    for ( i = 0; sum == square_sum_col( a, i ) && i < n; i++ ) ;
    if (i < n) { return false; }

    if ( sum != square_sum_diag0( a ) ) { return false; }
    if ( sum != square_sum_diag1( a ) ) { return false; }

    return true;
}


void magic( square *a )
{
    int i = 0;
    while ( !is_magic( a ) ) {
        permute(a);
        printf("%d, ", i++);
    }
}

square *square_init(int n)
{
    square *res = malloc( sizeof(square) );
    res->order = n;
    res->vals = malloc( n * n * sizeof(int) );

    int i;
    for ( i = 0; i < n * n; i++)
        res->vals[i] = i+1;

    return res;
}

void square_free( square *a ) 
{
    free( a->vals );
    free( a );
}

void square_print( square *a )
{
    const int n = a->order;
    int i, j;
    for ( i = 0; i < n; i++ ) {
        for ( j = 0; j < n; j++ ) {
            printf("%5d", a->vals[ i * n + j ] );
        }

        printf("\n");
    }
    printf("\n");
}

int square_sum( square *a )
{
    return square_sum_row(a, 0);
}


int main( int argc, const char **argv )
{
    if ( argc == 2 ) {
        square *q = square_init( atoi(argv[1]) );
        magic(q);
        square_print(q);
        printf("\nMagic sum : %d\n", square_sum(q));
        square_free(q);
    } else {
        printf("Wrong number of arguments, should be 1 and"
                " the argument have to be an integer\n");
    }

    return 0;
}

/*
void tp( square *a )
{   
    printf("\n");
    permute(a);
    square_print(a);

}


int main( void ) 
{
    int w[] = { 6, 1, 8, 7, 5, 3, 2, 9, 4 };
    square *q = square_init( 3 );

    q->vals = w;
    printf("%d\n", is_magic(q));
    square_print(q);

    int i;
    int n = q->order;
        printf("%d\n", square_sum_diag1(q));

//    tp(q); tp(q); tp(q);
    

    square_free(q);
    return 0;
}

*/
