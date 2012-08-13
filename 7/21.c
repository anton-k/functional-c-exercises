/*
 
 Sensitive information is often encrypted such that it is difficult 
 for unauthorised persons to intercept that information. An ancient
 method for encryption is the *Cesar cipher*. If a letter in the
 original message or *plaintext* is the n-th letter of character set
 then replace this letter by $n + k$-th letter in the encrypted message 
 or cipher text. The key to encrypting and decrypting the message is
 the number $k$. For example is the plain text is "Functional C" and
 the key is 4? then the cipher text is "Jyrgxmsrep$G", for the fourth
 letter after F is J, and so on. Write a program to implement a Cesar
 cipher method, taking the text to be processed from `stdin` and writing
 the output to `stdout`. The program should take a single argument: $+k$
 for encryption and $-k$ for decryption. Would you be able to prove 
 for all values of $k$ that decryption after encryption is equivalent 
 to do nothing at all, or, for people familiar with UNIX terminology:

 ~~~
 (a.out +k | a.out -k) = cat
 ~~~
  
 */


#include <stdio.h>
#include <ctype.h>

int main( int argc, const char **argv ) 
{
    if ( argc == 2 ) {
        int k = 0;
        sscanf(argv[1], "%d", &k);
        
        char c;        
        while ( ( c = getchar() )  != EOF ) {
            if ( isalpha(c) ) {
                putchar(c + (char) k );
            } else {
                putchar(c);
            }

        }
    }

    return 0;
}

