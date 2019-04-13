# Makefile du Projet test de primalité

CC = gcc
CFLAGS = -c -g -Wall
LIB = -lgmp
NOM = -o $@

ODIR  = binaires
MTDIR = mesureTemps
TPDIR = testPrimalites
TDDIR = testDeterministes
TPRDIR = testProbabilistes
FDIR = fonctions
DOC = Documentation
SITE = $(DOC)/html



run: clean principal

all: creation test doc

graphe: test
	gcc gnuplot_i/src/gnuplot_i.c mesureGraphe.c -o $(ODIR)/main
	./$(ODIR)/main

principal: test
	#time ./test
	#valgrind ./test
	./test

test: $(ODIR)/TER.o $(ODIR)/mesure.o $(ODIR)/testProbabilistes.o $(ODIR)/testDeterministes.o $(ODIR)/fonctions.o
	$(CC) -o test $^ $(LIB)

$(ODIR)/TER.o: TER.c 
	$(CC) $(CFLAGS) $(NOM) TER.c

$(ODIR)/mesure.o: $(MTDIR)/mesure.c $(MTDIR)/mesure.h
	$(CC) $(CFLAGS) $(NOM) $(MTDIR)/mesure.c

$(ODIR)/testProbabilistes.o: $(TPDIR)/$(TPRDIR)/testProbabilistes.c $(TPDIR)/$(TPRDIR)/testProbabilistes.h
	$(CC) $(CFLAGS) $(NOM) $(TPDIR)/$(TPRDIR)/testProbabilistes.c

$(ODIR)/testDeterministes.o: $(TPDIR)/$(TDDIR)/testDeterministes.c $(TPDIR)/$(TDDIR)/testDeterministes.h
	$(CC) $(CFLAGS) $(NOM) $(TPDIR)/$(TDDIR)/testDeterministes.c

$(ODIR)/fonctions.o: $(FDIR)/fonctions.c $(FDIR)/fonctions.h
	$(CC) $(CFLAGS) $(NOM) $(FDIR)/fonctions.c
	
creation:
	mkdir -p $(ODIR)
	mkdir -p $(DOC)

doc :
	doxygen

site:
	xdg-open $(SITE)/index.html

# graph:
# 	gnuplot graph.gnu


cleanAll:clean
	rm -rf $(ODIR)
	rm -rf $(DOC)

clean:
	rm -f test
	rm -f $(ODIR)/*.o
	 
	
