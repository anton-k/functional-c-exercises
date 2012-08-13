/*
 
 Modify one of the sorting functions from this chapter to sort
 strings rather then characters. Then use your sort function 
 to sort the lines of a file, representing the contents of a 
 line as a string.

 */

/* smth wrong with free array_string and 
   I can not figure out what */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define arr_string_size  sizeof( arr_string )

typedef struct {
    char **arr;    
    char * string;
    int length;
} arr_string;

void flen( FILE *file, int *filelen, int *lines )
{
    rewind( file );
    char c;
    *filelen = 0;
    *lines   = 0;
    while ( (c = getc(file)) != EOF ) {
        (*filelen)++;
        if ( c == '\n' ) {
            (*lines)++;
        }
    }
    
 //   (*lines)++;
    rewind( file );
}

void fcpy( FILE *file, char **ptr, char *dst )
{
    rewind( file );
    char c;
    int i = 0, j = 0;
    ptr[0] = dst;
    while ( (c = getc(file)) != EOF ) {
        if ( c == '\n' ) { 
            c = '\0'; 
            i++;
            ptr[i] = dst + j+1;
        }
        dst[j] = c;
        j++;
    }
    
    dst[j] = '\0';
}

arr_string *arr_string_init( const char *filename )
{
    FILE *file = fopen( filename, "r" );
    if ( file == NULL ) { return NULL; }

    int n_chars, n_lines;
    flen( file, &n_chars, &n_lines );

    arr_string *res = (arr_string *) malloc( sizeof(arr_string) );
    if (res == NULL) { 
        printf("out of memory\n"); 
        abort(); 
    }

    res->length = n_lines;
    res->arr    = (char **) calloc( (n_lines) , sizeof(char*) );
    res->string = (char *)  calloc( (n_chars+1) , sizeof(char) );

    if (res->arr == NULL || res->string == NULL ) { 
        printf("out of memory\n"); 
        abort(); 
    }
   
    char ** p = res->arr;
    char *sp = res->string;
    fcpy( file, res->arr, res->string );
    if (p != res->arr) { printf("BOOM\n"); }
    if (sp != res->string) { printf("BOOM-s\n"); }
    fclose( file );
    return res;
}

void arr_string_free( arr_string *a )
{
    free(a->string);
    free(a->arr);
    free(a);
}

void arr_string_dump( const arr_string *lines, const char *filename )
{
    FILE *file = fopen( filename, "w" );
    if ( file == NULL ) { 
        printf("can not open file for writing %s\n", filename); 
        abort(); 
    }

    int i;    
    int n = lines->length; 
    for ( i = 0; i < n; i++ ) {
        fprintf( file, (i < n-1) ?"%s\n":"%s", lines->arr[i] );
    }

    fclose( file );
}

int cmp_ptr_str( const void *a, const void *b )
{
    return strcmp( *(char **)a, *(char **)b );
}

void arr_string_sort( arr_string *a )
{
    qsort( a->arr, a->length, sizeof(char *), cmp_ptr_str );
}


void arr_string_print( arr_string *a )
{
    int n = a->length;
    char **it = a->arr;
    int i;    
    for ( i = 0; i < n; i++ ) {
        printf("%s*", *it++);
    }
    printf("\n");
}


int main( void )
{
    arr_string *lines = arr_string_init( "text" );
    printf("*** before\n");
    arr_string_print( lines );
    arr_string_free( lines );
/*
    printf("*** before\n");
    arr_string_print( lines );
//    arr_string_sort( lines );

    printf("*** after\n");
    arr_string_print( lines );
 //   arr_string_dump( lines, "text_dump" );
   // arr_string_free( lines );
*/
    return 0;
}



