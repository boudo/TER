#include "testDeterministes.h"

/*! \file      testDeterministes.c
 *  \brief     Fichier contenant le crible d'erastotene
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

/*! \fn int Eratosthene(mpz_t n)
 *  \brief Fonction Deterministe qui utilise le crible d'erastothene pour dire si un nombre est premier ou non
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé et -1 si erreur
 */
int Eratosthene(mpz_t n)
{
	//Si n < 2
	if (mpz_cmp_ui(n, 2) < 0)
	{
		return -1;
	}
	
	//Si n = 2
	if (mpz_cmp_ui(n, 2) == 0)
	{
		return 1;
	}

	mpz_t racine_n,resteDiv,nmoins1;
	mpz_inits(racine_n,resteDiv,nmoins1,NULL);

	//Liste des nombres premiers < à racine_n
	mpz_sqrt(racine_n,n);
	listegmp premier = creer_listegmp();
	
	if(mpz_cmp_ui(n,3)==0)//Cas pour 3
	{
		mpz_sub_ui(nmoins1,n,1);
		premier = crible_era_gmp(nmoins1);
	}
	else
	{
		premier = crible_era_gmp(racine_n); 
	}

	//On teste si chacun de ces nombres premiers / n
	listegmp tmp = premier;

	while (tmp->val != NULL)
	{
		if (tmp->primalite == 1)
		{
			mpz_mod(resteDiv,n,tmp->val);
			
			//Cas quand composé
			if (mpz_cmp_ui(resteDiv,0) == 0 ) 
			{
				mpz_clears(resteDiv, racine_n,nmoins1, NULL);
				libere_listegmp(premier);
				return 0;
			}
		}
		tmp = tmp->suiv;
	}
		
	//Cas quand 1er
	mpz_clears(resteDiv,racine_n,nmoins1,NULL);
	libere_listegmp(premier);
	return 1;
}

