/*
 
 A program is needed to make sure that the exam results of the 
 first year Computer Science students at your University are 
 correctly processed.

 (a) Define a two dimensional for storing the exam results
     (integers in the range 0 ... 100) of the first year 
     Computer Science students. Make sure that you choose
     appropriate upper bounds on the array(s) for the number
     of the students in your class and the number of modules
     in your course. 

 (b) Write a function to compute the sum of all the scores 
     in the exam results table for a particular student and 
     another function to count the number of non-zero scores
     for a particular student.

 (c) Write a function to print the results as a nicely formatted
     table, with one line per student and one column per module:

     * Each row should be perceeded by its row number.

     * Rows containing only zeros should not be printed.

     * At the end of each row, print the sum, the number of 
       non-zero scores and the average of the scores in the row.

  (d) Write a main function to create a table with some arbitrary
      values. Then call your print function on the table.

  (e) What measures you have taken to make sure that the exam 
      results are proceeded and averaged correctly?

*/


/* first proto
 
 TODO : 
    
    - don't count spaces around bars, count content only
    - flexible cells, should adapt to content
 
 */




#include <stdio.h>
#include <string.h>

#define n_name    35
#define n_student 50
#define n_module  10

typedef char string[n_name];

typedef struct {
    int first_width, next_width, 
        sum_width, non_zero_width, avg_width;
} opts;

typedef struct {
    string first, last;
} name;

typedef int results[n_student][n_module]; 


results table = {
    { 55, 75,  0, 100 },
    { 55, 75,  0, 0 },
    { 55, 75, 95, 100 },
    {100,100,100,100}
};

const int student_length = 4;

name students[] = {
    {"John",     "Fitch" },
    {"Lasley",   "Nilson"},
    {"Joe",      "Armstrong"},
    {"Larse",    "Larsen" }
};

const int module_length = 4;

string modules[] = {
    "Functional Programming",
    "Algorithms",
    "C Programming",
    "Literature"
};

const int score_name_length = 3;

char score_names[][5] = { "sum", ">0", "avg" };

int int_width( int n )
{
    int i;
    for ( i = 0; n > 0 ; i++, n /= 10 );    
    return i;
}

int int_max( int a, int b )
{
    if (a > b)
        return a;
    else 
        return b;
}

int name_width( name a )
{
    return 1 + strlen(a.first) + strlen(a.last);
}

int max_name_width() 
{
    int res = 0;
    int i;
    for ( i = 0; i < student_length; i++ )
        res = int_max( res, name_width(students[i]) );

    return res;
}

opts opts_init( void ) 
{
    opts res;
    res.first_width = max_name_width();
    res.next_width  = 5;
    res.sum_width   = int_max( strlen(score_names[0]), 
                               int_width(module_length * 100) );
    res.non_zero_width = int_max( strlen(score_names[1]),
                                  int_width( module_length ) );
    res.avg_width = int_max( strlen(score_names[2]), 
                             res.sum_width + 3);
    return res;
}

/* ------------------------------------------------------------- */
/* scores */

int sum_marks( const int *ms )
{
    int res = 0;
    int n = module_length;
    while (n--)
        res += *ms++;

    return res;
}

int non_zero_marks( const int *ms ) 
{
    int res = 0;
    int n = module_length;
    while (n--) {
        if ( *ms++ > 0 ) {
            res++;
        }
    }

    return res;
}

double avg_marks( const int *ms )
{
    return (double) sum_marks(ms) / module_length;
}

/* ------------------------------------------------------------- */
/* pretty printing */

void print_first_n( int n, const char *a )
{   
    int i;
    for ( i = 0; i < n; i++ ) {
        if ( *a ) {
            printf("%c", *a++);
        } else {
            printf(" ");
        }
    }
        
}

void print_char( char c )
{
    printf("%c", c);
}

void print_chars( int n, char c )
{
    while (n--)
        printf("%c", c);
}


void print_line( int n )
{
    print_chars( n, '-' );
}

void print_frame_cell( int n )
{
    print_char('+');
    print_line( n );
}

void cell_begin( void ) {
    printf(" | ");
}
void cell_begin( void ) {
    printf(" | ");
}

void cell_last( void ) {
    printf(" |\n");
}

void print_empty_cell( int n )
{
    cell_begin();
    print_chars( n, ' ');
}

void print_string_cell( int n, const char *str )
{
    cell_begin();
    print_first_n( n, str );
}

void print_name( name n, opts a )
{
    printf("%s %s", n.first, n.last);
    print_chars( a.first_width - name_width(n), ' ' );
}

void print_name_cell( name n, opts a )
{
    cell_begin();
    print_name(n, a);
}

void print_modules( opts a )
{
    int fit_to = a.next_width;
    int i;
    for ( i = 0; i < module_length; i++ )
        print_string_cell( fit_to, modules[i] );
}

void print_scores_header( opts a )
{
    print_string_cell( a.sum_width, score_names[0] );
    print_string_cell( a.non_zero_width, score_names[1] );
    print_string_cell( a.avg_width, score_names[2] );
}

void print_frame_line( opts opt )
{
    print_char(' ');
    print_frame_cell( opt.first_width + 2 );
    
    int i;
    for ( i = 0; i < module_length; i++ )        
        print_frame_cell( opt.next_width + 2);

    print_frame_cell( opt.sum_width + 2);
    print_frame_cell( opt.non_zero_width + 2);
    print_frame_cell( opt.avg_width + 2);

    print_char('+');
    printf("\n");
}

void print_header( opts opt ) 
{
    print_frame_line( opt );
    print_empty_cell( opt.first_width ); 
    print_modules( opt ); 
    print_scores_header( opt );
    cell_last();
    print_frame_line( opt );
}

void print_last_line( opts a )
{
    print_frame_line( a );
}

void print_int_cell( int n, int width )
{
    cell_begin();
    char format[10];
    sprintf(format, "%%%dd", width);
    printf(format, n);
}

void print_double_cell( double a, int width )
{
    cell_begin();
    char format[10];
    sprintf(format, "%%%d.2f", width);
    printf(format, a);
}

void print_marks( const int *marks, opts a )
{
    int i;
    for ( i = 0; i < module_length; i++ )
        print_int_cell( *marks++, a.next_width );
}

void print_scores( const int *ms, opts a )
{
    print_int_cell( sum_marks(ms)       , a.sum_width );
    print_int_cell( non_zero_marks(ms)  , a.non_zero_width );
    print_double_cell( avg_marks(ms)    , a.avg_width );
}


void print_student( int i, opts a )
{
    print_name_cell( students[i], a );
    print_marks( table[i], a);
    print_scores( table[i], a);
    cell_last();    
}

void print_results( void )
{
    const opts opt = opts_init();        
    print_header( opt );

    int i;
    for (i = 0; i < student_length; i++) 
        print_student( i, opt );    

    print_last_line( opt );
}


int main( void ) 
{
    print_results();
    return 0;
}




