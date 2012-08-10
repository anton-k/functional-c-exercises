/*
 
 Rewrite your card simulation program from Exercise 5.4 so 
 that it plays a real game. When playing, the user should 
 choose a secret number and the program should try to 'guess' it.
 Here is sample dialogue with such a program. The input of th user 
 is underlined; the text produced by the program is in plain font.

 ~~~
 Does the number appear on the first card:   1 3 5 7? _y_
 Does it appear on the second:               2 3 6 7? _n_
 And on the third:                           4 5 6 7? _n_
 Your secret number must be: 1!
 ~~~
 
 */

#include <stdio.h>
#include <stdbool.h>

typedef bool code[3];

const code ind[] = {
    { false, false, false },   
    {  true, false, false },     /* 1 */
    { false,  true, false },
    { true,   true, false },
    { false, false,  true },
    { true,  false,  true },
    { false,  true,  true },
    { true,   true,  true } };    /* 7 */


void flush(void){
    int c;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

bool is_right( int a, bool *c )
{
    return (ind[a][0] == c[0])
        && (ind[a][1] == c[1])
        && (ind[a][2] == c[2]);
}

int guess( bool *c )
{
    int res;
    for (res = 0; !is_right(res, c); res++)  ;        
    return res;        
}

void read_num(bool *ans)
{
    char c = getchar();
    flush();
    if        ( c == 'y' ) {
        *ans = true;        
    } else if ( c == 'n' ) {
        *ans = false;
    }
    else {
        printf("\nAnswer should be 'y' or 'n', try again: ");
        read_num(ans);
    }
}

void read_code(bool *ans)
{
    printf("Does the number appear on the first card:   1 3 5 7? ");
    read_num(ans++);
    printf("Does it appear on the second:               2 3 6 7? ");
    read_num(ans++);
    printf("And on the third:                           4 5 6 7? ");
    read_num(ans++);
}

void show_result(int n)
{
    if ( n == 0) {
        printf("You are kidding! There is no such a number on the table.\n");
    } else {
        printf("Your secret number must be: %d!\n", n);
    }
}


void game( void ) 
{
    code c;
    read_code( c );
    show_result( guess( c ) );
}

int main( void ) 
{
    game();
    return 0;
}

