#ifndef TESTDETERMINISTES_H
#define TESTDETERMINISTES_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

#include "../../fonctions/fonctions.h"

/*! \file      testDeterministes.h
 *  \brief     Fichier contenant les différents tests probabilistes
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

 //TESTS DETERMINISTES

int Eratosthene(mpz_t n);

int Pepin(mpz_t n);

int Lucas(mpz_t n);

#endif
