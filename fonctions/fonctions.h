#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../liste/liste.h"

void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b);

void expoRapide(mpz_t resultat, const mpz_t x, const mpz_t expo);

void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul);

liste getBinaire(const mpz_t expo);

void decomposition(mpz_t s,mpz_t d, mpz_t nMoins1);

void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n);

#endif
