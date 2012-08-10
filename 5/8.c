/*
 
 The last example assumes that the company has 4 employees
 and 5 years of history. Modify the program to use dynamic 
 arrays so that an arbitrary number of emplyees and years of
 history can be maintained. (a further extension, storing
 the database on a file, can be found in Chapter 7).
 
 */

#define n_name 10

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[n_name];
    int year_of_birth;
    double salary;
    
    struct {
        int *vals;
        int length;
    } sold;
} employee;

typedef struct {
    employee *vals;
    int length;
} personnel;

double mean( const int *s, int n )
{
    int sum = 0;

    int i;
    for ( i = 0 ; i < n; i++) {
        sum += s[i];
    }

    return (double) sum / n;
}

bool enough_sales( const employee* e ) 
{
    return mean( e->sold.vals, e->sold.length ) > 100.0 ;
}

void payrise( employee *e, double percent )
{
    e->salary = e->salary * (1 + percent / 100.0);
}

void update_single( employee *e )
{
    if (enough_sales( e ) ) {
        payrise( e, 10.0 );
    }       
}

void increase( personnel *p )
{
    int n = p->length;
    employee *e = p->vals;
    while (n--) {
        update_single( e++ );
    }
}


void print_employee( const employee *e )
{
    printf( "%s, %f, %d, [", e->name, e->salary, e->year_of_birth ) ;
    int n = e->sold.length;
    int i;
    for ( i = 0; i < n; i++ ) {
        printf("%d ", e->sold.vals[i] );
    }
    printf("]\n");
}

void employee_copy( employee *to, const employee *from )
{
    strcpy(to->name, from->name);
    to->year_of_birth = from->year_of_birth;
    to->salary = from->salary;
    
    int n = from->sold.length;
    if (to->sold.length > 0) {
        free(to->sold.vals);    
    }
    to->sold.length = n;
    to->sold.vals = (int *) calloc(n, sizeof(int));

    int i;
    for ( i = 0; i < n; i++ ) {
        to->sold.vals[i] = from->sold.vals[i];
    }
}

void print_personnel( const personnel *p )
{
    int n = p->length;
    int i;
    for ( i = 0; i < n; i++ ) {
        print_employee( p->vals + i );
    }
}

personnel personnel_init( int n )
{
    personnel res;
    res.length = n;
    res.vals = (employee *) calloc( n, sizeof(employee) );
    return res;
}

void personnel_free( personnel *p )
{
    free( p->vals );
}

void personnel_write( personnel *p, int i, const employee *e )
{
    employee_copy(p->vals + i, e);    
}


employee employee_init(const char *name, int year, double salary, 
        int n_sold, const int *sold_vals) 
{
    employee res;
    
    strcpy(res.name, name);
    res.year_of_birth = year;
    res.salary = salary;
    
    res.sold.length = n_sold;
    res.sold.vals = (int *) calloc(n_sold, sizeof(int));
    int i;
    for ( i = 0; i < n_sold; i++ ) {
        res.sold.vals[i] = sold_vals[i];
    }

    return res;
}

void employee_free( employee *e )
{
    free(e->sold.vals);
}


int main( void ) 
{
    int 
        john_sold[]  = {  80,  90,  75,  20,  69 },
        mary_sold[]  = {  72,  83,  75,  18,  75 },
        bob_sold[]   = { 100, 100, 100, 100, 101 },
        alice_sold[] = { 20,  500,  30, 800, 200 };

    int n = 5;
    employee
        john    = employee_init( "John" , 1963, 18813.00, n, john_sold ),
        mary    = employee_init( "Mary" , 1945, 20000.00, n, mary_sold ),
        bob     = employee_init( "Bob"  , 1983, 10000.00, n, bob_sold ),
        alice   = employee_init( "Alice", 1980, 10000.00, n, alice_sold );

    int m = 4;
    personnel 
        db_val = personnel_init( m );

    personnel *db = &db_val;

    personnel_write(db, 0, &john);
    personnel_write(db, 1, &mary);
    personnel_write(db, 2, &bob);
    personnel_write(db, 3, &alice);
    
    printf("\n  before:\n");
    print_personnel( db );
    
    increase( db );
    
    printf("\n  after:\n");
    print_personnel( db );
    printf("\n");

    personnel_free( db );

    employee_free(&john);
    employee_free(&mary);
    employee_free(&bob);
    employee_free(&alice);

    return 0;
}




