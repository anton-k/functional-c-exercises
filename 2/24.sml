(*
 
 The `nFib` number is a slight variation on the Fibonacci number
 It is defined as follows:

 n, fn  : N

 f0     : 1
 f1     : 1
 f[n]   : 1 + f[n-1] + f[n-2], if n >= 2

 (a) What is the difference between the fibonacci number 
     and the nFib series?

 (b) Write an SML function `nfib` to calculate the n-th nFib number.

 ...  write C ...

 (e) If you study the formula above closely, you will note
     that the value fn is the same as the number of function 
     calls made by your SML or your C function to calculate fn.
     Measure how long it takes SML to compute f[30] and calculate
     number of function calls per second for SML.

 (f) Perform the same measurement for your C program, 
     Which of the two language implementations is faster?
     By how much? Document every aspect of your findings, 
     so that someone else could repeat and corroborate your
     findings.    
 
 *)

(* ------------------------------------------ *)

(* int -> int *)
fun nfib 0 = 1
  | nfib 1 = 1
  | nfib n = 1 + nfib (n-1) + nfib (n-2);

print (Int.toString (nfib 30) ^ "\n");

(* mlton measuring the execution

$ mlton 24.sml
$ time ./24
2692537

real	0m0.015s
user	0m0.016s
sys	0m0.000s

mlton's score is:

Prelude> 0.015 / 2692537
5.570954085310619e-9
 
 *)

