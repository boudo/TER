#ifndef TESTPRIMALITES_H
#define TESTPRIMALITES_H_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../fonctions/fonctions.h"

//TESTS PROBABILISTES

int Fermat(mpz_t n, int iter);
int Miller_Rabin(mpz_t n, int rep);
int solovayStrassen(mpz_t aTraiter, int iterations);

//TESTS DETERMINISTES

int Eratosthene(mpz_t n);

#endif
