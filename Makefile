# Makefile du Projet test de primalité

CC = gcc
CFLAGS = -c -g -Wall
LIB = -lgmp
NOM = -o $@

ODIR  = binaires
MTDIR = mesureTemps
TPDIR = testPrimalites
FDIR = fonctions



run: clean principal

all: test doc

principal: test
	#time ./test
	#valgrind ./test
	./test

test: $(ODIR)/TER.o $(ODIR)/mesure.o $(ODIR)/testPrimalites.o $(ODIR)/fonctions.o
	$(CC) -o test $^ $(LIB)

$(ODIR)/TER.o: creation TER.c 
	$(CC) $(CFLAGS) $(NOM) TER.c

$(ODIR)/mesure.o: creation $(MTDIR)/mesure.c $(MTDIR)/mesure.h
	$(CC) $(CFLAGS) $(NOM) $(MTDIR)/mesure.c

$(ODIR)/testPrimalites.o: creation $(TPDIR)/testPrimalites.c $(TPDIR)/testPrimalites.h
	$(CC) $(CFLAGS) $(NOM) $(TPDIR)/testPrimalites.c

$(ODIR)/fonctions.o: creation $(FDIR)/fonctions.c $(FDIR)/fonctions.h
	$(CC) $(CFLAGS) $(NOM) $(FDIR)/fonctions.c
	
creation:
	mkdir -p $(ODIR)

doc :
	doxygen

cleanAll:clean
	rm -rf $(ODIR)
	rm -rf Documentation

clean:
	rm -f test
	rm -f $(ODIR)/*.o
	 
	
