(* 
 Some computers offer a 'populaition' count intruction to count
 the number of bits in an integer that are set to 1; for example,
 the population count of 7 is 3 and the population count of 8 is 1.

 (a) Write a specidfication for population count

 (b) Give an SML function to compute the population count of 
     a word, where an integer is used to represent a word. 
 
 *)

(*
 (a) Specification

     Let's solve this task by induction.

     checksum : int -> int

     base: x == 0, so sum is 0

     step: split nibble from x, and add it to the recursive call.
            Recursive call is made on (x div 16), so x gets smaller
            with each call end eventually it becomes zero.

     Assumption: The argument is positive
*)


(* ------------------------------------------------------ *)
(* implementation *)

(* int -> int -> int * int *)
fun div_mod n m = (n div m, n mod m);

(* int -> int *)
fun pop_count 0 = 0
  | pop_count x = 
    let 
        val dm = div_mod x 2
    in 
        #2 dm + pop_count (#1 dm)
    end;
    

fun test n = pop_count n;

(* sml/nj

- test 3;
val it = 2 : int
- test 32;
val it = 1 : int
- test 1027;       
val it = 3 : int
- test 0; 
val it = 0 : int
- test 1;
val it = 1 : int
 
 *)

