/*
 
 The database of employees (Section 5.9 and Exercise 5.8) was stored
 in a memory. A real data base would be stored on a file. Design
 functions wich will allow the employee data base to be stored on 
 a file. Use the following file format: the members of the structure
 are terminated by hash signs (#), each new structure starts on a new
 file. For example:

 John#18813#1963#80#90#75#20#69#
 Mary#19900#1946#72#83#75#18#75#
 Bob#12055#1969#120#110#100#99#99#
 Alice#15133#1972#200#230#75#11#35#

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

/* --------------------------------------------------------- */
/* load from file */

FILE* init_src( const char *filename )
{
    FILE *file = fopen( filename, "r" );
    if ( file == NULL ) {
        printf("no such a file: %s", filename);
        abort();
    }
    return file;
}

void free_src( FILE *file ) 
{
    fclose( file );
}


int read_length( const char *filename )
{
    FILE *file = init_src( filename );
    int res = 0;

    char c1, c2;

    bool is_first = true;
    c1 = getc( file );
    if ( c1 == EOF ) { 
        free_src( file );
        return res; 
    }    

    /* circlular buffer with two elements `c1` and `c2` */
    while ( true ) {
        if ( is_first ) {
            c2 = getc( file );
            if ( c2 == EOF ) { 
                free_src( file );
                return res; 
            }
            res += (c1 == '#') && (c2 == '\n');
            is_first = false;            
        } else {
            c1 = getc( file );
            if ( c1 == EOF ) { 
                free_src( file );
                return res; 
            }
            res += (c2 == '#') && (c1 == '\n');
            is_first = true;
        }        
    }
}


void prepare_store( int n, personnel *p )
{
    p->length = n;
    p->vals   = calloc( n, sizeof(employee) );    
}

bool read_name( FILE *src, employee *e )
{
    char c;
    int i = 0;
    while ( true ) {
        c = getc( src );
        if ( c == EOF ) { return false; }
        if ( c == '#' ) { 
            e->name[i] = '\0';
            return true;  }

        if ( i < n_name - 1 ) {
            e->name[i] = c;
            i++;             
        }
    }
}
bool read_double( FILE *src, double *a )
{
    return fscanf( src, "%lf#", a ) == 1;
}

bool read_int( FILE *src, int *n )
{
    return fscanf( src, "%d#", n ) == 1;
}

bool read_salary( FILE *src, employee *e )
{
    return read_double( src, &(e->salary) );
}

bool read_year_of_birth( FILE *src, employee *e )
{
    return read_int( src, &(e->year_of_birth) );
}

int read_store_length( FILE *src )
{
    int res = 0;
    int n;
    while ( read_int( src, &n ) ) 
        res ++;
    return res;
}


void prepare_sold_store( FILE *src, employee *e )
{
    long int current = ftell( src );
    int n = read_store_length( src );
    e->sold.length = n;
    e->sold.vals   = calloc( n, sizeof(int) );
    fseek( src, current, 0 );
}

bool read_store_vals( FILE *src, employee *e )
{
    int i, n;
    for ( i = 0; read_int( src, &n ); i++ ) 
        e->sold.vals[i] = n;

    return  true; 
}

bool read_sold( FILE *src, employee *e )
{
    prepare_sold_store( src, e );
    return read_store_vals( src, e ); 
}


bool employee_read( FILE *src, employee *e )
{
    return read_name( src, e ) 
        && read_salary( src, e )        
        && read_year_of_birth( src, e )
        && read_sold( src, e );
}

void load_employees( const char *filename, personnel *p )
{
    FILE *src = init_src( filename );
    int n = p->length;
    int i;
    for ( i = 0; i < n; i++ ) {
        if ( !employee_read( src, p->vals + i ) ) { 
            free_src( src );
            return ; }
    }
    free_src( src );
}


personnel personnel_load( const char *filename )
{
    personnel res;
    prepare_store( read_length( filename ), &res );
    load_employees( filename, &res );
    return res;
}

/* --------------------------------------------------------- */
/* dump to file */

void write_name( FILE *file, char name[n_name] )
{
    fprintf( file, "%s#", name );
}

void write_int( FILE *file, int n )
{
    fprintf(file, "%d#", n);
}

void write_double( FILE *file, double n )
{
    fprintf( file, "%lf#", n );
}

void write_salary( FILE *file, double n )
{
    write_double( file, n );
}

void write_year_of_birth( FILE *file, double n )
{
    write_int( file, n );
}

void write_sold( FILE *file, employee e )
{
    int i,
        n = e.sold.length;

    for ( i = 0; i < n; i++ ) 
        write_int( file, e.sold.vals[i] );
}

void write_end_of_employee( FILE *file )
{
    fprintf( file, "\n" );
}


void employee_dump( FILE *file, employee e )
{
    write_name( file, e.name );
    write_salary( file, e.salary );
    write_year_of_birth( file, e.year_of_birth );
    write_sold( file, e );
    write_end_of_employee( file );
}

void personnel_dump( personnel p, const char *filename )
{
    FILE *file = fopen( filename, "w" );
    if ( file == NULL ) {
        printf("Could not open file %s for writing\n", filename);
        abort();
    }

    int i,
        n = p.length;

    for ( i = 0; i < n; i ++ )
        employee_dump( file, p.vals[i] );

    fclose( file );
}

/* -------------------------------------------------------- */
/* pretty print db */

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

void print_personnel( const personnel *p )
{
    int n = p->length;
    int i;
    for ( i = 0; i < n; i++ ) {
        print_employee( p->vals + i );
    }
}

/* -------------------------------------------------------- */
/* constructors - desructors */

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

/* -------------------------------------------------------- */
/* testing */

int main( void ) 
{
    personnel p;
    p = personnel_load( "db" );
    print_personnel( &p );
    return 0;    
}


