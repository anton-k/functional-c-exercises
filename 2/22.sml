(*
 
 A *nibble* is a group of four adjacent bits. A checksum 
 of a word can be calculated by adding nibbles of a word 
 together. Fow example, the checksum of 17 is 2 and the
 checksum of 18 is 3.

 (a) Give a spec for `checksum` function. Assume that
     a given word x is represented as a sequence of k+1 
     nibbles as follows n[k] n[k-1] ... n[1] n[0], where
     each n[i] has a value in the range 0 ... 15

 (b) Give an SML function to compute checksum of a word, 
     where an integer is used to represent a word. Test 
     your function.

 ... write C code ....

 
 *)

(*

 (a) Specification

     The task is the same as previous, but know instead of 
     2 we use 16 as modulus. Let's coin a general solution.
 *)

(*
 
 ----------------------------------------------------

 implementation
 
 *)

(* int -> int -> int * int *)
fun div_mod n m = (n div m, n mod m);

(* int -> int -> int *)
fun gensum k 0 = 0
  | gensum k n = 
    let
        val dm = div_mod n k
    in
        (#2 dm) + gensum k (#1 dm)
    end;
        (* in the SML `(#n t)` is the way 
           to select the n-th element from tuple *)

(* int -> int *)
fun pop_count n = gensum  2 n;
fun checksum  n = gensum 16 n;

fun test n = checksum n;

(* sml/nj

- test 17;
val it = 2 : int
- test 18;
val it = 3 : int
- test 1024;
val it = 4 : int
- test 12341234;
val it = 59 : int

*)

