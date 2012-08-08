/*
 
 A 'Bounding box' is a concept used in 2-dimensional graphics.
 A bounding box of a picture is defined as the rectangular box 
 that is just large enough to contain the whole picture:

             ... some pics ...

 Assuming that the edges of the bounding box are parallel 
 to X and Y axes, a bounding box is fully specified by a 
 pair of coordinates: the coordinates of the lower left hand 
 corner and the upper right hand corner.

 Bounding boxes need to be manipulated. In particular, if two
 elements of a drawing have boundary boxes, the combined bounding
 box needs to be calcuated:


  +--------------+                     +==============+======+
  |              |                     |              |      |
  |        +-----+------+  combined    |        +-----+------+          
  |        |     |      |  ========>>  |        |     |      |
  +--------+-----+      |  bounding    +--------+-----+      | 
           |            |  box         |        |            | 
           |            |              |        |            | 
           +------------+              +========+============+

 In general two bounding boxes are defined by defining a new
 bounding box with the minimum $x$ and $y$ coordinates as the 
 lower left corner and the maximum $x$ and $y$ coordinates as
 of the top right hand corner. 
 
 Define and implement the following:

 (a) A datatype to hold the bounding box.

 (b) A function that normalizes bounding box (that is: it insures
     that it stores the lower left and upper right corners, and
     not, for example, the lower right and the upper left corners).

 (c) A function that combines two bounding boxes into one bounding box.

 (d) A datatype to define a line.

 (e) A datatype to define a circle.

 (f) A datatype to define a rectangle.

 (g) A datatype called `element` that can hold any of the line, circle,
     or rectangle.

 (h) A function that takes a value of type `element` and produces
     the bounding box.

 (i) A main program that calculates the combined bounding box of
     the following components:

      ...  here is the picture ...

     A circle at (2,2) with radius 1, a rectangle with corners at (3,5)
     and (5,4), and a line from (2,2) to (6,1).

*/

#include <stdlib.h>
#include <stdio.h>

int int_min(int a, int b)
{
    if ( a < b ) {
        return a;
    } else {
        return b;
    }
}

int int_max(int a, int b)
{
    if ( a > b ) {
        return a;
    } else {
        return b;
    }    
}

/* ------------------------------------------------------ */
/* point */

typedef struct {
    int x, y;
} point;

point point_init(int x, int y)
{
    point res;
    res.x = x;  res.y = y;
    return res;
}

void print_point(point a)
{
    printf("(%d, %d)", a.x, a.y);
}

point point_min( point a, point b )
{
    return point_init( int_min(a.x, b.x), int_min(a.y, b.y) );
}

point point_max( point a, point b )
{
    return point_init( int_max(a.x, b.x), int_max(a.y, b.y) );
}

/* vector */

typedef struct {
    int x, y;
} vec;

vec vec_init(int x, int y) 
{
    vec res;
    res.x = x;  res.y = y;
    return res;
}

point bias(vec v, point a)
{
    return point_init( a.x + v.x, a.y + v.y );
}


/* --------------------------------------------------- */
/* bounding box */

typedef struct {
    point ld;
    point rt;
} box;

box box_init(point ld, point rt)
{
    box res;
    res.ld = ld;  res.rt = rt;
    return res;
}

void print_box(box a)
{
    printf("Box ");
    print_point(a.ld);
    printf(" ");
    print_point(a.rt);
}

box normalize( box a )
{
    return box_init( 
            point_min(a.ld, a.rt), 
            point_max(a.ld, a.rt) );
}

box combine( box a, box b ) 
{
    return box_init(
            point_min(a.ld, b.ld),
            point_max(a.rt, b.rt) );
}


/* --------------------------------------------------- */
/*  elements */

typedef struct {
    point a, b;
} line;

typedef struct {
    point center;
    int   radius;
} circle;

typedef struct {
    point a, b;
} rectangle;


typedef enum { 
    Line, Circle, Rectangle 
} elementTag; 

typedef struct {
    elementTag tag;

    union {
        line        line;
        circle      circle;
        rectangle   rectangle;
    } at;
} element;


element line_init(point a, point b) { 
    element res;
    res.tag     = Line;   
    res.at.line.a = a;
    res.at.line.b = b;
    return res;
}

element circle_init(point c, int r)
{
    element res;
    res.tag = Circle;
    res.at.circle.center = c;
    res.at.circle.radius = r;
    return res;
}

element rectangle_init(point a, point b)
{
    element res;
    res.tag             = Rectangle;
    res.at.rectangle.a  = a;
    res.at.rectangle.b  = b;
    return res;
}


box line_bound( line x )
{
    return normalize( box_init( x.a, x.b ) );
}

box circle_bound( circle x )
{
    return box_init( 
            bias( vec_init(-x.radius, -x.radius), x.center),
            bias( vec_init( x.radius,  x.radius), x.center) );
}

box rectangle_bound( rectangle x )
{
    return normalize( box_init( x.a, x.b ) );
}


box element_bound( element x )
{
    switch ( x.tag ) {
        case Line       :   return line_bound( x.at.line );
        case Circle     :   return circle_bound( x.at.circle );
        case Rectangle  :   return rectangle_bound( x.at.rectangle );
        default         :   abort();    
    }
}


/* ---------------------------------------------------- */
/* testing */


int main(void)
{   
    element 
        c = circle_init( point_init(2, 2), 1 ),
        r = rectangle_init( point_init(3, 5), point_init(5, 4)),
        l = line_init( point_init(2, 2), point_init(6, 1) );

    box 
        res = combine( 
                element_bound(c),
                combine(
                    element_bound(r),
                    element_bound(l)));

    printf("bounding box:\n ");
    print_box( res );
    printf("\n");

    return 0;
}

