/*
 
 In this exercise, create a function that prints a table of 
 the months of a year with the number of days in each month.
 Futhermore, write a function that when given a particular 
 date in a year calculates what date it will be exactly one 
 week later.

 (a) Write a C function `print_three` to print the first three
     characters of a string. The function should have one 
     argument (the string) and its return type should be `void`.

 (b) Give C type definition of a structure `month` with two fields:
     an integer `days` and a character string `name`. The string 
     should have an appropriately chosen length. Use this declaration
     to create an array of months called `leap`. Initialize the
     entries of th array with the number of days in each month and 
     the *full* name of the month. You may assume that February 
     has 29 days.

 (c) Create a function `print_year` that prints a table of the 
     months of a year with the number of days in each month. 
     Your function should take one argument, the array of `month`.
     Its return type should be `void`. Furthermore print the total
     number of days in all the months/ Here is a fragment of the
     output that your function `print_year` should produce:

     ~~~
     Jan. has 31 days
     Feb. has 29 days
     / * ... rest of months * /
     Dec has 31 days
     This year has 366 days
     ~~~

 (d) Given a particular date in a year, for example February 24th,
     write a C function that calculates what date it will be exactly
     one week later. In a `leap` year, the answer should be March 2nd.
     Thus you will need to know how many days each month has. Use
     the table of part(b) for this purpose. Design a suitable interface
     for your function. 
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_MONTH_NAME 15

void print_three(const char *s)
{
    printf("%c%c%c", s[0], s[1], s[2]);
}

typedef struct {
    char name[N_MONTH_NAME];
    int days;
} month;

typedef struct {
    char month[N_MONTH_NAME];
    int date;
} day;

month leap[] = {
    { "January",        31 },
    { "February",       29 },
    { "March",          31 },
    { "April",          30 },
    { "May",            31 },
    { "June",           30 },
    { "July",           31 },
    { "August",         30 },
    { "September",      31 },
    { "October",        31 },
    { "November",       30 },
    { "December",       31 }
};


void print_year( const month *a ) 
{
    int i;
    for ( i = 0; i < 12; i++ ) {
        print_three(a[i].name);
        printf(" has %d days\n", a[i].days);
    }
}

day day_init( const char *month, int date )
{
    day res;
    res.date = date;
    strcpy(res.month, month);
    return res;        
}

void day_print(day *a)
{
    print_three(a->month);
    printf(" %d", a->date);
}

day next_week( day a )
{
    int i;
    for ( i = 0; i < 12 && strcmp( a.month, leap[i].name ); i++)
        ;

    if ( i == 12 ) {
        printf("Error, wrong month name: %s\n", a.month);
        abort();
    } 
    
    int new_date = a.date + 7;
    if ( new_date > leap[i].days ) {
        return day_init( 
                leap[(i+1) % 12].name,
                new_date - leap[i].days);
    } else {
        return day_init( leap[i].name, new_date );
    }
    
}

void test(day a)
{
    day b = next_week(a);

    printf("\nCurrent day: ");
    day_print(&a);
    printf("\nWeek later : ");
    day_print(&b);
    printf("\n");
}

int main( void )
{
    printf(" Leap year:\n");
    print_year(leap);
    printf("\n");

    test( day_init("February", 24) );
    test( day_init("August", 9) );
    test( day_init("December", 30) );

    return 0;
}

