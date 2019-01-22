# Makefile du Projet test de primalité


run: clean principal

principal: test
	#time ./test
	valgrind ./test
	#./test

test:
	gcc -Wall -o test test.c liste_corrige.c -lgmp
	
clean:
	rm -f test
	rm -f *.o
	
