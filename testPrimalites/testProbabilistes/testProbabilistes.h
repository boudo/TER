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

/*! \fn int Fermat(mpz_t n, int iter)
 *  \brief Fonction test de Fermat qui permet de tester si un nombre est premier ou non
 *  \param n : nombre à tester
 *  \param iter : nombre d'iterations
 *  \return retourne 1 si premier ou sinon 0
 */
int Fermat(mpz_t n, int iter);

/*! \fn int Miller_Rabin(mpz_t n, int rep)
 *  \brief Fonction test de Miller_Rabin qui permet de tester si un nombre est premier ou non
 *  \param n : nombre à tester
 *  \param rep : nombre d'iterations
 *  \return retourne 1 si premier sinon 0
 */
int Miller_Rabin(mpz_t n, int rep);

/*! \fn int solovayStrassen(mpz_t aTraiter, int iterations)
 *  \brief Fonction permettant de calculer si un nombre est premier ou composé.
 *  \param aTraiter : le nombre que l'on désire traiter.
 *  \param iterations : le nombre d'iterations que l'on désire faire lors du teste.
 *  \return on retourne 1 s'il est premier ou bien 0 s'il est composé
 */
int solovayStrassen(mpz_t aTraiter, int iterations);


#endif