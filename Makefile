# Makefile du Projet test de primalité

CFLAGS = -c -g -Wall

run: clean principal

principal: test
	#time ./test
	#valgrind ./test
	./test

test: tests_prim.o mesure.o testProbabilistes.o testDeterministes.o fonctions.o
	gcc -o test tests_prim.o mesure.o testProbabilistes.o testDeterministes.o fonctions.o -lgmp

tests_prim.o: tests_prim.c 
	gcc $(CFLAGS) tests_prim.c

mesure.o: mesureTemps/mesure.c mesureTemps/mesure.h
	gcc $(CFLAGS) mesureTemps/mesure.c

testProbabilistes.o: testProbabilistes/testProbabilistes.c testProbabilistes/testProbabilistes.h
	gcc $(CFLAGS) testProbabilistes/testProbabilistes.c

testDeterministes.o: testDeterministes/testDeterministes.c testDeterministes/testDeterministes.h
	gcc $(CFLAGS) testDeterministes/testDeterministes.c

fonctions.o: fonctions/fonctions.c fonctions/fonctions.h
	gcc $(CFLAGS) fonctions/fonctions.c
	
clean:
	rm -f test
	rm -f *.o
	 
	
