
cc		= gcc
objects	= snoc_list.o ntree.o

test: main.c $(objects)
	$(cc) -o test main.c $(objects)

run: test
	./test	

clean:
	rm test $(objects)

ntree.o: ntree.h ntree.c snoc_list.h
	$(cc) -c ntree.c

snoc_list.o: snoc_list.c snoc_list.h
	$(cc) -c snoc_list.c




