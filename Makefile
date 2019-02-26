# Makefile du Projet test de primalité

CFLAGS = -c -g -Wall

run: clean principal

principal: test
	#time ./test
	#valgrind ./test
	./test

test: TER.o mesure.o testPrimalites.o fonctions.o
	gcc -o test TER.o mesure.o testPrimalites.o fonctions.o -lgmp

TER.o: TER.c 
	gcc $(CFLAGS) TER.c

mesure.o: mesureTemps/mesure.c mesureTemps/mesure.h
	gcc $(CFLAGS) mesureTemps/mesure.c

testPrimalites.o: testPrimalites/testPrimalites.c testPrimalites/testPrimalites.h
	gcc $(CFLAGS) testPrimalites/testPrimalites.c

fonctions.o: fonctions/fonctions.c fonctions/fonctions.h
	gcc $(CFLAGS) fonctions/fonctions.c
	
clean:
	rm -f test
	rm -f *.o
	 
	
