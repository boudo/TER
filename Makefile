# Makefile du Projet test de primalité


run: clean principal

principal: test
	#time ./test
	#valgrind ./test
	./test

test:
	gcc -Wall -o test Tests_prim.c liste/liste.c fermat/fermat.c fonctions/fonctions.c miller/miller.c crible/crible.c -lgmp
	
clean:
	rm -f test *.o
	 
	
