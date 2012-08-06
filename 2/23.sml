(*

 The n-th Fibonacci number fn is defined by the following
 reccurence relation:

 n, fn  : N
 f0     : 0
 f1     : 1
 fn     : f[n-1] + f[n-2] if n >= 2
 
 Write an SML function `fib` to calculate the n-th Fibonacci number.
 Then, give the corresponding C function and main program to test 
 the C version of `fib` for at least three interesting values of n.

 *)

(* int -> int *)
fun fib 0 = 0
  | fib 1 = 1
  | fib n = fib (n-1) + fib (n-2);


(* test sml/nj
 
- fib 10; 
val it = 55 : int
- fib 15; 
val it = 610 : int
- fib 20;
val it = 6765 : int
- fib 25;
val it = 75025 : int

 *)

