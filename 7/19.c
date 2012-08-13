/*
 
 Implement the bubble sort. Use it to sort chars from `argc` and `argv`.
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap( char *arr, int i, int j )
{
    char c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
}

void bubble( char *arr, int n )
{
    int i, j;
    for ( i = 0; i < n - 1; i++ )
        for ( j = i + 1; j < n; j++ )
            if ( arr[i] > arr[j] )
                swap( arr, i, j );
}

int main( int argc, const char **argv ) 
{
    if (argc == 2) {
        int n = strlen( argv[1] );
        char *str = malloc( (1 + n) * sizeof(char) );
        strcpy(str, argv[1]);
        bubble(str, n);
        printf("%s\n", str);
        free(str);
    } 

    return 0;
}


