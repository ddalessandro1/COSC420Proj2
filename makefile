all:proj2

proj2: tri.c lib.a
	mpicc tri.c lib.a -o proj2 -lm

#for the static library
side.o: side.c side.h
	gcc -lm -c side.c side.h
randpoint.o: randpoint.c randpoint.h
	gcc -lm -c randpoint.c randpoint.h
height.o: height.c height.h
	gcc -lm -c height.c height.h
Area.o: Area.c Area.h
	gcc -lc -c Area.c Area.h

#static library creation
lib.a: side.o randpoint.o height.o Area.o
	ar crv lib.a side.o randpoint.o height.o Area.o
libs: lib.a

#clean up
clean:
	rm -f tri *.o *.a *.gch *.h.gch
