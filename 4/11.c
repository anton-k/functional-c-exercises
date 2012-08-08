/*
 
 Design a program that displays the character set of 
 your computer  in a sensible way. Your solution should
 have a function that classifies a character. Given a 
 character, the function should return  a structure
 that identifies the class of the character and some 
 information within the class. The classes to be 
 distinguished  are:

    1. A digit. The numerical value of the digit 
       should be returned as well.

    2. A lower case letter. In addition the index of
       the letter (1..26) must be returened.

    3. An upper case letter. In addition the index of
       the letter (1..260 must be returned.

    4. White space. Nothing extra needs to be returned.

    5. Someting else.
 
 */


/*
 
 Spec:

 data Class 
    = Digit Int
    | Lower Int
    | Upper Int
    | Space
    | Something Char

 Let's bring it down to the C 

 */

#include <stdio.h>
#include <ctype.h>

/* ------------------------------------------- */

typedef enum { 
    Digit, Lower, Upper, Space, Something 
} ClassTag;

typedef struct {
    ClassTag tag;

    union {
        int  digit, lower, upper;
        char something;
    } at;   
} Class;


/* ------------------------------------------- */
/* constructors */

void digit( int a, Class *res ) 
{
    res->tag = Digit;
    res->at.digit = a;
}

void lower( int a, Class *res )
{
    res->tag = Lower;
    res->at.lower = a;
}

void upper( int a, Class *res )
{
    res->tag = Upper;
    res->at.upper = a;
}

void space(Class *res)
{
    res->tag = Space;    
}

void something(char a, Class *res)
{
    res->tag = Something;
    res->at.something = a;
}

/* ------------------------------------------- */

void classify(char a, Class *res)
{
    if        ( isdigit(a) ) {
        digit(a - '0', res);            
    } else if ( islower(a) ) {
        lower(1 + a - 'a', res);    
    } else if ( isupper(a) ) {
        upper(1 + a - 'A', res);
    } else if ( isspace(a) ) {
        space(res);
    } else {
        something(a, res);
    }
}

void print_class(const Class *res)
{
    switch ( res->tag ) {
        case Digit      : printf("Digit %d", res->at.digit); break;
        case Lower      : printf("Lower %d", res->at.lower); break;
        case Upper      : printf("Upper %d", res->at.upper); break;
        case Space      : printf("Space"); break;
        case Something  : printf("Something %c", res->at.something); break;
        default         : printf("error no parse");     
    }
}


void print_msg(int i, Class *res)
{
    char c = i;
    classify(c, res);

    printf( "%c  ->  ", c); 
    print_class(res);
    printf("\n");
}

void test(int n)
{
    Class res;

    int i;
    for (i = 0; i < n; i++) {
        print_msg(i, &res);
    }
}

int main(void)
{
    test(128);
    return 0;
}



