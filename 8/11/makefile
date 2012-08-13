
cc 		= gcc
objects	= array.o

test: main.c $(objects) 
	$(cc) -o test main.c  $(objects)

array.o: array.c array.h
	$(cc) -c array.c 


run: test
	./test

