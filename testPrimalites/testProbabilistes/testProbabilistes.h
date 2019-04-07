#ifndef TESTPROBABILISTES_H
#define TESTPROBABILISTES_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

#include "../../fonctions/fonctions.h"

/*! \file      testProbabilistes.h
 *  \brief     Fichier contenant les différents tests probabilistes
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

//TESTS PROBABILISTES

int Fermat(mpz_t n, int iter);

int Miller_Rabin(mpz_t n, int rep);

int solovayStrassen(mpz_t aTraiter, int iterations);

void Test_Fibo(mpz_t res,mpz_t n);

void Test_Lucas(mpz_t res,mpz_t n);

void LucasFrobenius(mpz_t n, mpz_t a, mpz_t b, mpz_t delta);

#endif
