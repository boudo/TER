#ifndef MESURE_H
#define MESURE_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../testPrimalites/testProbabilistes/testProbabilistes.h"
#include "../testPrimalites/testDeterministes/testDeterministes.h"

/*! \file      mesure.h
 *  \brief     Fichier contenant les tests de mesures
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

/*! \fn int estPremier(mpz_t nombre,int nombreIteration)
 *  \brief Fonction qui permet de dire si un nombre est premier ou non
 *  \param nombre : nombre à tester
 *  \param nombreIteration : nombre d'iterations
 * 	\return retourne 1 si premier sinon 0
 */
int estPremier(mpz_t nombre,int nombreIteration);

/*! \fn void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration)
 *  \brief Fonction qui permet de generer un nombre premier
 *  \param resultat : nombre à tester
 *  \param nbrBit : nombrede bits
 *  \param nombreIteration : nombre d'iterations
 */
void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration);

/*! \fn void mesureTempsFichier(char *nomFichier,int nbrIteration)
 *  \brief Fonction qui permet d'ecrire les mesures dans un fichier
 *  \param nomFichier : nom du Fichier où seront stockés les mesures
 *  \param nbrIteration : nombre d'iterations
 */
void mesureTempsFichier(char *nomFichier,int nbrIteration,int nbrBitMax);

#endif
