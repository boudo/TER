#ifndef MESURE_H
#define MESURE_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../testProbabilistes/testProbabilistes.h"

int estPremier(mpz_t nombre,int nombreIteration);

void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration);

#endif