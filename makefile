all:project2

project2: tri.o lib.a
	gcc -o tri tri.o lib.a -lm 
tri.o: tri.c
	gcc -lm -c tri.c
side.o: side.c side.h
	gcc -lm -c side.c side.h
randpoint.o: randpoint.c randpoint.h
	gcc -lm -c randpoint.c randpoint.h
lib.a: side.o randpoint.o
	ar crv lib.a side.o randpoint.o
libs: lib.a

clean:
	rm -f tri *.o *.a *.gch *.h.gch
