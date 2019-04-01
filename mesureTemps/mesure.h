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

int estPremier(mpz_t nombre,int nombreIteration);

void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration);

void mesureTempsFichier(char *nomFichier,int nbrIteration,int nbrBitMax);

void mesureTempsPepin(char *nomFichier,int max);

void mesureTempsLucas(char *nomFichier,int max);

#endif
