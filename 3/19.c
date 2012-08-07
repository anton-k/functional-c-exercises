/*
 
 Using a loop, write a function that determines the root of a
 continuous function using Newton-Raphson method. Use the answer of
 Exrcise 2.26 as the starting point.
 
 */


#include <stdio.h>
#include <math.h>

typedef double (*fn_double)(double);

double newton_raphson(double eps, 
    fn_double f, fn_double f_, double x)
{
    double fx = f(x);

    while ( fabs(fx) > eps ) {
        x -= fx / f_(x);
        fx = f(x);
    }

    return x;
}


double parabola(double x)
{
    return x * x - 2.0;
}

double parabola_(double x)
{
    return 2.0 * x;
}

double test_(double x) 
{
    return newton_raphson(0.001, parabola, parabola_, x);
}

void test(double x) 
{
    printf("%7.2f %10.6f\n", x, test_(x));
}

int main( void ) 
{
    test(0.5);
    test(200.0);
    test(1.5);
    
    return 0;
}


