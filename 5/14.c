/*

 A particlular spread sheet program has the following features:

 (a) The program knows about fixed maximum number of work sheets.

 (b) Each work sheet has a name (of fixed maximum length), and
     a date and time of when it was last used.

 (c) Each wark sheet is a rectangular 2d array of cells with bounds 
     that will not exceed certain fixed maximum values.

 (d) There are four kinds of cells: a formula (represented as a
     string of a fixed maximum length), an integer, a real number,
     or a boolean.

 (e) The spread sheet program should be able to tell what kind of
     cell it is dealing with.

 (f) Each cell has a flag string whether it is in use or not.

 Design the C data structures required to support all these features
 by giving `#define` and typedef declarations. *Do not write the rest
 of the program that might use the datastructures*.

*/

#include <stdbool.h>

#define n_wsheet    1
#define n_name      1
#define n_row       1
#define n_col       1


typedef struct {
    int year, month, day, 
        hour, minute, second; 
} date;

typedef enum { 
    Formula, Integer, Real, Boolean 
} cell_tag;

typedef struct {
    cell_tag tag;
    bool in_use;
    union {
        char    formula[n_name];
        int     int_;
        double  double_; 
        bool    bool_;
    } at;
} cell;

typedef struct { 
    char name[n_name];
    date last_time;
    cell cell[n_row][n_col];
} wsheet;


int main( void ) 
{
    return 0;
}







