/* Exercise 4.14
  
 Define a `struct` to represent some of the following 2D objects:
 circle, square, box, parallelogram, triangle, and ellipse. Then 
 write a function that given a 2D object computes the area of 
 the object.

 */


/* Exercise 4.15 

 Using the `struct` and function of the previous exercise, define
 another `struct` that makes it possible to represent 3D objects,
 such as sphere, cube, cone, cylinder and pyramid. Write a function
 to compute the volume of the 3D objects.
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* ------------------------------------------------------ */
/* 2D */

typedef struct {
    double rad;
} circle;

typedef struct {
    double side;
} square;

typedef struct {
    double width, height;
} box;

typedef struct {
    double angle, a, b;
} parabox;

typedef struct {
    double a, b, c;
} triangle; 

typedef struct {
    double a, b;
} ellipse;


typedef enum {
    Circle, Square, Box, Parabox, Triangle, Ellipse
} obj2dTag;

typedef struct {
    obj2dTag tag;

    union {
        circle      circle;
        square      square;
        box         box;
        parabox     parabox;
        triangle    triangle;
        ellipse     ellipse;
    } at;
} obj2d;

/*-------------------------------------------------------- */
/* 3D */

typedef struct {
    circle base;
} sphere;

typedef struct {
    square base;
} cube;

typedef struct {
    double h;
    circle base;
} cone;

typedef struct {
    double h;
    circle base;
} cylinder;

typedef struct {
    double   h;
    triangle base;
} pyramid;

typedef enum {
    Sphere, Cube, Cone, Cylinder, Pyramid
} tag_obj3d;

typedef struct {
    tag_obj3d tag;

    union {
        sphere      sphere;
        cube        cube;
        cone        cone;
        cylinder    cylinder;
        pyramid     pyramid;            
    } at;
} obj3d;

/*-------------------------------------------------------- */
/* constructors  */

/* 2D */

obj2d circle_init(double rad)
{
    obj2d res;
    res.tag = Circle;
    res.at.circle.rad    = rad;
    return res;
}

obj2d square_init(double side)
{
    obj2d res;
    res.tag = Square;
    res.at.square.side   = side;
    return res;
}

obj2d box_init(double width, double height)
{
    obj2d res;
    res.tag = Box;
    res.at.box.width  = width;
    res.at.box.height = height;
    return res;
}

obj2d parabox_init( double angle, double a, double b)
{
    obj2d res;
    res.at.parabox.angle  = angle;
    res.at.parabox.a      = a;
    res.at.parabox.b      = b;
    return res;
}

obj2d triangle_init( double a, double b, double c )
{
    obj2d res;
    res.at.triangle.a = a;
    res.at.triangle.b = b;
    res.at.triangle.c = c;
    return res;
}

obj2d ellipse_init( double a, double b )
{
    obj2d res;
    res.at.ellipse.a = a;
    res.at.ellipse.b = b;
    return res;
}

/* 3D */

obj3d sphere_init(double rad)
{
    obj3d res;
    res.tag = Sphere;
    res.at.sphere.base.rad = rad;
    return res;
}

obj3d cube_init(double side)
{
    obj3d res;
    res.tag = Cube;
    res.at.cube.base.side = side;
    return res;
}

obj3d cone_init(double h, double rad)
{
    obj3d res;
    res.tag = Cone;
    res.at.cone.h = h;
    res.at.cone.base.rad = rad;
    return res;
}

obj3d cylinder_init(double h, double rad)
{
    obj3d res;
    res.tag = Cylinder;
    res.at.cylinder.h = h;
    res.at.cylinder.base.rad = rad;
    return res;
}

obj3d pyramid_init(double h, double a, double b, double c)
{
    obj3d res;
    res.tag = Pyramid;
    res.at.pyramid.h = h;
    res.at.pyramid.base.a = a;
    res.at.pyramid.base.b = b;
    res.at.pyramid.base.c = c;
    return res;
}

/*-------------------------------------------------------- */
/* area by elements */

double area_circle(circle x)
{
    return M_PI * x.rad * x.rad;
}

double area_square(square x)
{
    return x.side * x.side;
}

double area_box(box x)
{
    return x.width * x.height;
}

double area_triangle(triangle x)
{
    const double 
        a = x.a,
        b = x.b,
        c = x.c;
    
    const double p = 0.5 * (a + b + c);
    return pow( p * (p - a) * (p - b) * (p - c) , 0.5);
}

double area_parabox(parabox x)
{
    return x.a * x.b * sin(x.angle);
}

double area_ellipse(ellipse x)
{
    return M_PI * x.a * x.b;
}


/*-------------------------------------------------------- */
/* volume by elements */

double h_base( double h, double base )
{
    return h * base;
}

double volume_sphere(sphere x)
{
    return h_base( 4.0 * x.base.rad / 3.0,  area_circle(x.base) );
}

double volume_cube(cube x) 
{
    return h_base( x.base.side,  area_square(x.base) );
}

double volume_cone(cone x)
{
    return h_base( x.h / 3.0, area_circle(x.base) );
}

double volume_cylinder( cylinder x ) 
{
    return h_base( x.h, area_circle(x.base) );
}

double volume_pyramid( pyramid x) 
{
    return h_base( x.h / 3.0, area_triangle(x.base) );
}


/* area of all elements */

double area(obj2d x) 
{
    switch ( x.tag ) {
        case Circle     :   return area_circle(x.at.circle);
        case Square     :   return area_square(x.at.square); 
        case Box        :   return area_box(x.at.box);
        case Parabox    :   return area_parabox(x.at.parabox); 
        case Triangle   :   return area_triangle(x.at.triangle);
        case Ellipse    :   return area_ellipse(x.at.ellipse);

        default         :   abort();
    }
}

/* volume of all elments */

double volume(obj3d x) 
{
    switch ( x.tag ) {
        case Sphere     :   return volume_sphere(x.at.sphere);
        case Cube       :   return volume_cube(x.at.cube);
        case Cone       :   return volume_cone(x.at.cone);
        case Cylinder   :   return volume_cylinder(x.at.cylinder);
        case Pyramid    :   return volume_pyramid(x.at.pyramid);

        default         : abort();
    }
}

/* -------------------------------------------------------------- */
/* testing */

void test(const char *msg, double a)
{
    printf("  ");
    printf("%s", msg);
    printf(" : %5.2f\n", a);    
}


int main( void )
{
    printf("\narea\n");
    test( "square 2", area( square_init(2) ) );
    test( "box 2 5" , area( box_init(2, 5) ) );
    test( "circle 1", area( circle_init(1) ) );
    test( "circle 2", area( circle_init(2) ) );

    printf("\nvolume\n");
    test( "cube 1"  , volume( cube_init(1) ));
    test( "cylinder 1 1", volume( cylinder_init(1,1) ) );
    test( "sphere 1", volume( sphere_init(1) ) );

    printf("\n");
    return 0;
}

