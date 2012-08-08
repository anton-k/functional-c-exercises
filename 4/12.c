/*
 
 An accounting package needs to calculate net salaries 
 given gross salaries, and gross salaries given net salaries.

 (a) Previously, floating point numbers were used to represent
     money. Thi is not proper, as the figure `1.01` can not be
     represented exactly (Section 2.4). Design a data structure
     that represents an amount of money with a pair of integers,
     where one integer maintains the whole pounds (dollar, yen, ...)
     and the other represents the pennies (cent, sen, ...).

 (b) Define functions that operate on the money data type. 
     The functions should allow to add to amounts of money,
     subtract, and multiply a sum with an integer, and divide 
     a sum by an integer. The division should round amounts 
     to the nearest penny/cent/sen.

 (c) Define a function that calculates the net salary given
     the following formula:


        r    =   9g/10  ,   if g > 15000
                 g      ,   otherwise  

        p    =   r      ,   if g > 18500
                 9r/10  ,   otherwise

        n    =   p              ,   if p < 10000
                 4p/5 + 2000    ,   if 10000 < p < 15000
                 3p/5 + 5000    ,   if 15000 < p < 20000
                 p/2  + 7000    ,   otherwise

     where `g` is the gross salary, `r` is after retirement 
     contributions are taken out, `p` is after insurance is
     taken out, and n is the net salary.

 (d) Define a function that determines a gross salary that
     someone has to be paid in order to get a given net salary.
     Do not attempt to invert the equations for `p` and `n`
     (this is in real life not feasible), instead use the function
     defined above and search for the right amount using 
     `bisection`.
  
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int yen, sen;
} money;

money money_init( int yen, int sen )
{
    money res;
    res.yen = yen;
    res.sen = sen;
    return res;
}

/* -------------------------------------------------------- */

void print_money(money a)
{
    printf("Money %d %d", a.yen, a.sen);
}

bool eq( money a, money b ) 
{
    return a.yen == b.yen && a.sen == b.sen;    
}

int absolute(int a) 
{
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}

int to_int(money a) 
{
    return a.yen * 100 + a.sen;
}

double to_double(money a)
{
    return a.yen + (double) a.sen / 100.0;
}

money add(money a, money b)
{
    int sen = a.sen + b.sen;
    return money_init(a.yen + b.yen + sen / 100,  sen % 100);
}

money sub(money a, money b)
{
    int sen = a.sen - b.sen;
    if (sen < 0) {
        return money_init(a.yen - b.yen - 1, 100 + sen);
    } else {    
        return money_init(a.yen - b.yen, sen);
    }
}


money mul( int n, money a )
{
    int sen = a.sen * n;
    return money_init(a.yen * n + sen / 100, sen % 100);
}

money div( int n, money a )
{
    return money_init(a.yen / n, ((a.yen % n) * 100 + a.sen) / n);
}


money frac( int num, int denom, money a)
{
    return div(denom, mul(num, a));
}


money lincomb( int num, int denom, int bias, money a )
{
    return add(frac(num, denom, a), money_init(bias, 0));
}

/* -------------------------------------------------------- */

money net_salary(money g)
{
    /* get r */
    money r;
    if ( to_double(g) > 15000.0 ) {
        r = frac(9, 10, g);
    } else {
        r = g;
    }

    /* get p */
    money p;
    if ( to_double(g) > 18500.0 ) {
        p = r;
    } else {
        p = frac(9, 10, r);
    }

    /* get n */
    const double dp = to_double(p);
    if        (dp < 10000) {
        return p;
    } else if (dp < 15000) {
        return lincomb(4, 5, 2000, p);
    } else if (dp < 20000) {
        return lincomb(3, 5, 5000, p);
    } else {
        return lincomb(1, 2, 7000, p);
    }
}

/* -------------------------------------------------------- */

int estimate_gross_salary(const void *vn, money x)
{
    const money* n = vn;
    return to_int( sub( net_salary( x ), *n) );
}


money bisection_money( int (*f)(const void *, money), 
    const void *n, money l, money h)
{
    money m;
    int f_m;

    while (true) {
        m = div(2, add(l, h));
        f_m = f(n, m);

        if (f_m == 0 || to_int(sub(h, l)) == 0) { 
            return m;
        } else if (f_m < 0) {
            l = m;                                
        } else {
            h = m;
        }
    }    
}

money get_lower(const void *pn) 
{
    money res = money_init(0, 0);    
    while ( estimate_gross_salary( pn, res ) > 0 ) {
        res.yen -= 3000;
    }

    return res;
}

money get_higher(const void *pn) 
{
    money res = money_init(0, 0);    
    while ( estimate_gross_salary( pn, res ) < 0 ) {
        res.yen += 3000;
    }

    return res;
}

money gross_salary( money n )
{
    void *pn = &n;
    return bisection_money( estimate_gross_salary, pn, 
            get_lower(pn), get_higher(pn));
}

/* -------------------------------------------------------- */

void test( money got, money expected )
{
    if ( eq(got, expected) ) {
        printf(" Ok ");    
    } else {
        printf("  X ");
    }

    printf("| got: ");
    print_money(got);
    printf("  expected: ");
    print_money(expected);
    printf("\n");
}



int main( void )
{
    money a = money_init(10, 0);
    money b = money_init(40, 75);

    /* operators */
    printf("\noperators\n\n");

    printf("add\n");
    test( add(a, a), money_init(20, 0) );
    test( add(b, b), money_init(81, 50) );

    printf("sub\n");
    test( sub(a, a), money_init(0, 0) );
    test( sub(a, b), money_init(-31, 25) );
    test( sub(b, a), money_init(30, 75) );

    printf("mul\n");
    test( mul(4, a), money_init(40, 0));
    test( mul(4, b), money_init(163, 0));

    printf("div\n");
    test( div(4, a), money_init(2, 50));
    test( div(4, b), money_init(10, 18));   

    /* gross to net and back */
    printf("\ngross - net salary\n\n");

    test( a, gross_salary(net_salary(a)) );
    test( b, gross_salary(net_salary(b)) );

    test( a, net_salary(gross_salary(a)) );
    test( b, net_salary(gross_salary(b)) );

    return 0;
}
