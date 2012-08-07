/*

   Write a C function `chess_board` with two integer arguments
   `width` and `height` to print out a `width x height` chess board
   using ASCII characters. If `width = 4` and `height = 2` the
   output should look as follows:

    ---------
    | |X| |X|
    ---------
    |X| |X| |
    ---------

*/

#include <stdio.h>
#include <stdbool.h>

void empty_line()
{
    printf("\n");
}

void line(int width) 
{
    const int n = 2 * width + 1;
    
    int i;
    for (i = 0; i < n; i++) {
        printf("-");
    }
    printf("\n");
}

void x_cell()
{
    printf("|X");
}

void empty_cell()
{
    printf("| ");
}

void row(int cur_row, int width) 
{
    line(width);
    int i;
    bool cell_type = cur_row % 2;
    for (i = 0; i < width; i++) {
        if (cell_type) {
            x_cell();
        } else {
            empty_cell();
        }

        cell_type = !cell_type;
    }
    printf("|\n");
}

void last_line(int width)
{
    empty_line();
    line(width);
}

void chess_board(int width, int height)
{
    empty_line();

    int i;
    for (i = 0; i < height; i++) {
        row(i, width);
    }
    
    last_line(width);
}


int main( void ) 
{
    chess_board(8, 8);

    return 0;
}

