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

/*! \fn int Eratosthene(mpz_t n)
 *  \brief Fonction Deterministe qui utilise le crible d'erastothene pour dire si un nombre est premier ou non
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé et -1 si erreur
 */
int Eratosthene(mpz_t n);

/*! \fn int Pepin(mpz_t n)
 *  \brief Fonction Test De Pepin
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé
 */
int Pepin(mpz_t n);

/*! \fn int Lucas(mpz_t n)
 *  \brief Fonction Test De Lucas
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé
 */
int Lucas(mpz_t n);

#endif