#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../liste/liste.h"

void pgcd_gmp(mpz_t resultat, const mpz_t a, const mpz_t b);

void expoRapide_gmp(mpz_t resultat, const mpz_t x, const mpz_t expo);

void squareAndMultiply_gmp(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul);

liste expoEnBinMpz(const mpz_t expo);

void deux_pow(mpz_t res,mpz_t s);

void decomposition(mpz_t x,mpz_t s,mpz_t t);

#endif
