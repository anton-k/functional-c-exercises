/*
 
 Exercise 5.11

 The bissection method of the previous chapter can be used
 not only to search the roots of a function but it also can 
 be used to search efficiently for some special item in 
 non numerical data.

 (a) Modify extra bissection form Section 4.5 to work with
     discrete rather than continious data. That is replace
     all types `double` by `int` and reconsider the use 
     of `eps`, `delta` and `absolute`. 

 (b) Write a `main` function to call your dicrete bissection
     function such that it will search for an occurence of
     a string in a sorted array of strings. Use the arguments
     to your `a.out` to search for another occurence of `a.out` 
     to test your code. For example, the following command should
     produce the number `5`, and it should make only two string
     comparisons.

     ~~~
     a.out a.1 a.2 a.3 a.4 a.out b.1
     ~~~

 (c) Generalise the bissection function such that it assume the role
     of the dicrete as well as the continuous bisection. Then
     rewrite your program to use generalised bisection rather than
     the discrete.

 */


/*

 Exercise 5.12

 If you use a machine with a UNIX like operating system you might
 try to write the following program that determines how much 
 address space your program is allowed to use. A standard UNIX 
 function, `brk`, attempts to set the highest address that your 
 program may use (the 'break'). The function returns either `0`
 to indicate that the break was set successfully, or `-1` to signal
 to signal that the break could not be set that high. Use the bisection
 function of the previous exercise to find the highest break that you
 can use (assume that your system allows pointers and integers 
 to be mixed, and that the break is somewhere between 0 and 0xFFFFFFFF)

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>   

#include <unistd.h>

#define EPS 0.0001

/* ---------------------------------------------- */
/* generic algorithm */

typedef void (*fn_middle)( const void *, const void *, void * );
typedef bool (*fn_eq)( const void *, const void * );
typedef void (*fn_copy)(void *, const void*);

typedef struct {
    fn_middle   middle;
    fn_eq       eq;
    fn_copy     copy;
} api_bisection;

void extra_bisection( api_bisection api, 
    int (*ord)(const void *, const void *), 
    const void *param, void *l, void *h, void *out ) 
{
    int f_m; 
    if ( ord(param, l) == 0 ) {
        api.copy(out, l);
        return;
    }

    if ( ord(param, h) == 0 ) {
        api.copy(out, h);
        return;
    }

    while (true) {
        api.middle( l, h, out );
        f_m = ord( param, out );

        if ( f_m == 0 || api.eq(l, h) ) {
            return ;
        } else if ( f_m < 0 ) {
            api.copy(l, out);
        } else {
            api.copy(h, out);
        }
    }
}

/* ------------------------------------------------------ */
/* bisection api for integers */

void int_middle( const void *pa, const void *pb, void *pout )
{
    const int 
        *a = pa,
        *b = pb;
    int *out = pout;

    *out = *a + (*a - *b) / 2;
}

bool int_eq( const void *pa, const void *pb )
{
    const int
        *a = pa,
        *b = pb;
    return *a == *b;
}

void int_copy( void *pout, const void *pin )
{
    const int *in = pin;
    int *out = pout;
    *out = *in;
}

const api_bisection int_bisection = { 
    int_middle, int_eq, int_copy };

/* ------------------------------------------------------ */
/* bisection api for unsigned integers */

void uint_middle( const void *pa, const void *pb, void *pout )
{
    const unsigned int 
        *a = pa,
        *b = pb;
    unsigned int *out = pout;

    *out = *a + (*b - *a) / 2;
}

bool uint_eq( const void *pa, const void *pb )
{
    const unsigned int
        *a = pa,
        *b = pb;
    return *a == *b;
}

void uint_copy( void *pout, const void *pin )
{
    const unsigned int *in = pin;
    unsigned int *out = pout;
    *out = *in;
}

const api_bisection uint_bisection = { 
    uint_middle, uint_eq, uint_copy };

/* ------------------------------------------------------ */
/* bisection api for doubles */

void double_middle( const void *pa, const void *pb, void *pout )
{
    const double
        *a = pa,
        *b = pb;
    double *out = pout;

    *out = 0.5 * (*a + *b);
}

bool double_eq( const void *pa, const void *pb )
{
    const double
        *a = pa,
        *b = pb;
    return fabs( *a - *b ) < EPS;
}


void double_copy( void *pout, const void *pin )
{
    const double *in = pin;
    double *out = pout;
    *out = *in;
}

const api_bisection double_bisection = {
    double_middle, double_eq, double_copy };

/* ------------------------------------------------------ */
/* strings in the array case */

typedef struct {
    const char **array;
    const char *target;
} data_find_string;

int cmp_find_string( const void *pdata, const void *pn )
{
    const data_find_string *data = pdata;
    const int *n = pn; 

    return strcmp( data->array[*n], data->target );
}


int find_string( 
    const char **array, const char *target, int array_length )
{
    int res, 
        l = 0, 
        h = array_length - 1;
    data_find_string data = { array, target };

    extra_bisection( int_bisection, cmp_find_string, 
        &data, &l, &h, &res);

    if ( strcmp(array[res], target) == 0 ) {
        return res;
    } else {
        return -1;
    }
}

/* ----------------------------------------------------- */
/* find roots */


typedef struct {
    double (*fn)(double);
} data_roots; 

int cmp_roots( const void *pdata, const void *px )
{
    const data_roots *data = pdata;
    const double *x = px;
    double  y = (data->fn)(*x);
    if ( fabs(y) < EPS ) {
        return 0;
    } else if ( y > 0 ) {
        return 1;
    } else {
        return -1;   
    }
}

double roots( double (*f)(double), double l, double h )
{
    double res;
    data_roots data = { f };

    extra_bisection( double_bisection, cmp_roots,
        &data, &l, &h, &res);

    return res;
}

/* ----------------------------------------------------- */
/* finding switch of UNIX `brk` function 
   (Exercise 5.12)  */

int cmp_brk( const void *pdata, const void *pa )
{
    const int *va = pa;

    int
        a = *va,
        b = a + 1,
        ya = brk((void *) a),
        yb = brk((void *) b);

 //   printf("%d %d\n", ya, yb);
 //   printf("%p %p\n", (void *) a, (void *) b);
    if ( ya != yb ) {
        return 0;
    } else if (ya == 0) {
        return -1;
    } else {
        return 1;
    }
}


int find_brk( void ) 
{
    int res,
        l = 0,
        h = 0xDFFFFFFF;

    extra_bisection( uint_bisection, cmp_brk,
        NULL, &l, &h, &res);

    return res;
}


unsigned int to_mem(unsigned int a, int n) 
{
    int i;
    for ( i = 0; i < n; i++ )
        a /= 2;
    return a;
}

unsigned int to_mb(unsigned int a)
{
    return to_mem(a, 20);
}

unsigned int to_gb(unsigned int a)
{
    return to_mem(a, 30);
}



/* ----------------------------------------------------- */
/* testing */

double parabola( double x )
{
    return x * x - 2;
}

int main( int argc, const char **argv )
{
    int id;
    if (argc > 2) {
        id = find_string( argv + 2, argv[1], argc - 2 );
    } else {
        id = -1;
    }

    double sqrt_two = roots( parabola, 0.0, 200.0 );
    double m_pi = - 2.0 * roots( cos, -2.0, 0 );

    printf( "%d\n", id );
    printf( "sqrt(2) = %12.7f\n", sqrt_two );
    printf( "pi      = %12.7f\n", m_pi );

    int barrier = find_brk();
    printf("brk = %p\n", (void *) barrier);
    printf("You've got %u Mb or %u Gb. \n", 
        to_mb(barrier), to_gb(barrier));

    return 0;
}

