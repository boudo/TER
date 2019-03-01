#include "testDeterministes.h"

/*! \file      testDeterministes.c
 *  \brief     Fichier contenant les différents tests probabilistes
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */


/*! \fn int Fermat(mpz_t n, int iter)
 *  \brief Fonction test de Fermat qui permet de tester si un nombre est premier ou non
 *  \param n : nombre à tester
 *  \param iter : nombre d'iterations
 *  \return retourne 1 si premier ou sinon 0
 */

 /*!\fn int Eratosthene(mpz_t n)
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

/*! \fn int Pepin(mpz_t n)
 *  \brief Fonction Test De Pepin
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé
 */
int Pepin(mpz_t n)
{
	mpz_t Fn,trois,Ce,FnMoins1;
	mpz_inits(Fn,trois,Ce,FnMoins1,NULL);
	
	mpz_set_ui(trois,3);
	
	nombre_fermat(Fn,n);
	mpz_sub_ui(FnMoins1,Fn,1);
	
	//gmp_printf("testfnbrfermat=%Zd\n",Fn);
	
	critere_euler(Ce,trois,Fn);
	//gmp_printf("testCe=%Zd\n",Ce);
	
	if(mpz_cmp(Ce,FnMoins1) == 0)
	{
		mpz_clears(Fn,trois,Ce,FnMoins1,NULL);
		return 1;
	}
	
	mpz_clears(Fn,trois,Ce,FnMoins1,NULL);
	return 0;

}

/*! \fn int Lucas(mpz_t n)
 *  \brief Fonction Test De Lucas
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé
 */
int Lucas(mpz_t n) // on a n impaire, on veut savoir si 2^n - 1 est premier
{
	mpz_t pair;
	mpz_init(pair);
	mpz_mod_ui(pair,n,2);
	if (mpz_cmp_ui(pair,0) == 0)
	{ // SI n % 2 est egale a 0
		mpz_clear(pair);
		return 0;
	}
	// initialisation
	mpz_t seq, mers, deux;
	mpz_inits(seq, mers, deux, NULL);
	mpz_set_ui(seq,4);
	mpz_set_ui(deux, 2);
	// calcul de la sequence
	mersen(mers, n);
	calculSequence(seq, mers, n);
	// test du resultat de le sequence
	if( mpz_cmp_ui(seq, 0) == 0)
	{
		// gmp_printf("%Zd est 1er\n", mers);
		mpz_clears( seq, mers, deux, pair, NULL);
		return 1;
	}

	// gmp_printf("%Zd est composé\n", mers);
	mpz_clears(seq, mers, deux, pair, NULL);
	return 0;
}