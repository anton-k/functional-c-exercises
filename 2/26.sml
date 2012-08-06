(*
 
 The Newton-Raphson method is an alternative to the bisection 
 method for finding the roots of a function f(x). It works 
 on the basis of the following observation: if there is a value x[i],
 so that f(x[i]) is approximately zero, then a better approximation
 of the root is x[i+1] defined as:

    x[i+1] = x[i] - f(x[i]) / f'(x[i]) 
 
 Here the function f'(x) is the derivative of f(x). (...)

 (b) Give an SML function `newton_raphson` that implements the
     Newton-Raphson method on the basis of the mathematics from (a)
     above. Make sure that as much information as possible is
     captured by arguments. 

 (c) Use your Newton-Raphson function to calculate the root of
     the `parabola` function from Section 2.5

 ... write C code ...
 
 *)


(* real -> (real -> real) -> (real -> real) -> real -> real *)
fun newton_raphson eps f f_ x =
    let 
        val fx = f x 
    in
        if abs (fx) < eps
        then
            x
        else
            newton_raphson eps f f_ ( x - fx / f_ x )
    end;

(* real -> real *)
fun parabola x = x * x - 2.0;

(* real -> real *)
fun parabola_ x = 2.0 * x; 

(* real -> real *)
fun test x = newton_raphson 0.001 parabola parabola_ x

(* sml/nj

- test 0.5;
val it = 1.41423428594 : real
- test 200.0;
val it = 1.4142150151 : real
- test 1.5;
val it = 1.41421568627 : real

 *)

