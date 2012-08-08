/*
 
 (a) Explain the relationship between C language operators * and &.
  
 answer: The operator * is a dereference operator and oprator &
         is a reference operator. Dereference means getting a value
         of the pointer and reference means getting an address of
         the value. They are dual operators.

 */

 /*

 (b) What is the output of the following programm
  
 */

#include <stdio.h>

int main_b( void ) 
{
    int i = 3;
    int *p = &i;
    int **q = &p;

    printf("%d %d %d %d %d %d %d\n", 
        3, i, p==*q, *p, q==&p, *q==&i, **q);

    return 0;
}

/*
    answer:

    3  i p==*q  *p   q==&p  *q==&i  **q
   
    3  3   1     3    1       1      3
 
 */

 /*

    (c) State what the output of the following program would be and
        explain why

  */

int twice_c(int (*f)(int), int a)
{
    return f( f( a ) );
}

int add_c(int a)
{
    return a + 1;
}

int main_c(void)
{
    printf("%d\n", twice_c(add_c, 2));
    return 0;
}

/* answer          : 4
   what's going on : The function `twice` applies function `f` two times.
                     We add one to the two but two times, so we get `4`.
   why is it so    : By definition.
 
 */


/* 
 
  (d) Which are the differences between the program below and 
      that of question (c)?
 
 */

int twice_d( int (*f)(int, int, int), 
           int x, int y, int a)
{
    return f(x, y, f(x, y, a));
}

int add_d(int a, int b, int c)
{
    return a + b + c;
}


int main_d(void)
{
    printf("%d\n", twice_d(add_d, 2, 3, 4));
    return 0;
}


/*
  
 answer: difference lies in the number of parameters. 
         Now we supply three but it was one in the (c) case.
 
 we get: 14        

 */


/*

  (e) Which are the differences between the program below and
      that of question (d):

*/

typedef struct {
    int l, r;
} pair;


int twice_e(int (*f)(void *, int), 
            void *x, int a)
{
    return f(x, f(x, a));
}

int add_e(void *x, int a) 
{
    pair *p = x;
    return p->l + p->r + a;
}


int main_e(void)
{
    pair p = { 2, 3 };
    printf("%d\n", twice_e( add_e, &p, 4 ));

    return 0;
}

/*
 
    answer: output is the same but the way that leads to it is
            slightly different. Now we pack two int's in pair
            and use void* as parameter to supply pair.
 
 */

int main(void)
{
    return main_e();
}


