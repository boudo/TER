# Makefile du Projet test de primalité

CFLAGS = -c -g -Wall

run: clean principal

principal: test
	#time ./test
	#valgrind ./test
	./test

test: tests_prim.o testProbabilistes.o crible.o fonctions.o liste.o
	gcc -o test tests_prim.o testProbabilistes.o crible.o fonctions.o liste.o -lgmp

tests_prim.o: tests_prim.c testProbabilistes/testProbabilistes.c crible/crible.c
	gcc $(CFLAGS) tests_prim.c

testProbabilistes.o: testProbabilistes/testProbabilistes.c testProbabilistes/testProbabilistes.h
	gcc $(CFLAGS) testProbabilistes/testProbabilistes.c

crible.o: crible/crible.c crible/crible.h
	gcc $(CFLAGS) crible/crible.c

fonctions.o: fonctions/fonctions.c fonctions/fonctions.h
	gcc $(CFLAGS) fonctions/fonctions.c

liste.o: liste/liste.c liste/liste.o
	gcc $(CFLAGS) liste/liste.c
	
clean:
	rm -f test
	rm -f *.o
	 
	
