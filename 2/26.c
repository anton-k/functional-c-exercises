#include <stdio.h>
#include <math.h>

double newton_raphson(double eps, 
        double (*f)(double), double (*f_)(double), double x) 
{
    const double fx = f(x);

    if ( fabs(fx) < eps ) {
        return x;
    } else {
        return newton_raphson(eps, f, f_, x - fx / f_(x));
    }
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
    printf("%7.2f %7.6f\n", x, test_(x));
}

int main( void ) 
{
    test(0.5);
    test(200.0);
    test(1.5);
    
    return 0;
}

