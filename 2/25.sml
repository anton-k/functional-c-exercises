(*
 Write an SML function `power_of_power` to compute
 n-th tern in the following series:

 0  1  2     3         4
 1, m, m^m, m^(m^m), m^(m^(m^m))

 The n counts the number of occurances of m in the term. Give the C
 version of `power_of_power` and give a main program to test the C version
 for at least three interesting values of m and n.

 *)

(* int -> bool *)
fun odd  x = 1 = x mod 2;
fun even x = 0 = x mod 2;

(* int -> int *)
fun square_int x = x * x;

(* int -> int -> int *)
fun power n 0 = 1
  | power n m = if odd m 
                then n * power n (m-1)
                else square_int (power n (m div 2));
        
(* int -> int -> int *)
fun power_of_power m 0 = 1
  | power_of_power m n = power m (power_of_power m (n-1));

(* sml/nj
 
- power_of_power 2 5;

uncaught exception Overflow [overflow]
  raised at: <file 25.sml>
- power_of_power 2 3;
val it = 16 : int
- power_of_power 2 4;
val it = 65536 : int
- power_of_power 3 4;

uncaught exception Overflow [overflow]
  raised at: <file 25.sml>
- power_of_power 3 3;

uncaught exception Overflow [overflow]
  raised at: <file 25.sml>
- power_of_power 3 2;
val it = 27 : int

so we get

2 3 => 16
2 4 => 65536
3 2 => 27
 *)
