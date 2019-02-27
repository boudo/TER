#include "testPrimalites.h"

/*! \file      testPrimalites.c
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
// ************* Fermat ***************************

int Fermat(mpz_t n, int iter)
{
	//printf("taille = %d\n", iter);
	if(mpz_cmp_ui(n,2) < 0)
	{
		return 0;
	}
	if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
	{
		return 1;
	}

	mpz_t pair;
	mpz_init(pair);
	mpz_mod_ui(pair,n,2);
	if (mpz_cmp_ui(pair,0) == 0)
	{ // SI n % 2 est egale a 0
		mpz_clear(pair);
		return 0;
	}

	mpz_t pg, sqm, alea, nMoins1;
	gmp_randstate_t state;
	mpz_inits(pg, sqm, alea, nMoins1, NULL);
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));	
	mpz_sub_ui(nMoins1, n, 1); // nMoins1 = n - 1
	for(int i=0; i<iter; i++)
	{	
		gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));	
		mpz_urandomm (alea , state , n);
		// gmp_printf("alea = %Zd\n", alea);

		if(mpz_cmp_ui(alea, 2) < 0)
		{
			mpz_add_ui(alea, alea, 2);
		}
		// gmp_printf("alea = %Zd\n", alea);
		pgcd(pg, n, alea);
		if (mpz_cmp_ui(pg, 1) != 0)
		{
			// gmp_printf("pgcd = %Zd et alea = %Zd donc %Zd est composé\n",pg,alea, n);
			mpz_clears(pg, sqm, alea, nMoins1, pair, NULL);
			gmp_randclear(state);
			return 0;
		}
		squareAndMultiply(sqm, alea, nMoins1, n);
		if(mpz_cmp_ui(pg, 1) == 0 && mpz_cmp_ui(sqm, 1) != 0)
		{
			// gmp_printf("sqm = %Zd et alea = %Zd expo = %Zd donc  %Zd est composé pgcd = %Zd\n", sqm, alea, nMoins1, n, pg);
			mpz_clears(pg, sqm, alea, nMoins1, pair, NULL);
			gmp_randclear(state);
			return 0;
		}
	}

	// gmp_printf("sqm = %Zd et %Zd est 1er pgcd = %Zd et alea =  %Zd\n", sqm, n, pg, alea);
	mpz_clears(pg, sqm, alea, nMoins1, pair, NULL);
	gmp_randclear(state);
	return 1;
}

/*! \fn int Miller_Rabin(mpz_t n, int rep)
 *  \brief Fonction test de Miller_Rabin qui permet de tester si un nombre est premier ou non
 *  \param n : nombre à tester
 *  \param rep : nombre d'iterations
 *  \return retourne 1 si premier sinon 0
 */
// ************* Miller ***************************
int Miller_Rabin(mpz_t n, int rep)
{
	if(mpz_cmp_ui(n,2) < 0)
	{
		return 0;
	}
	if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
	{
		return 1;
	}

	mpz_t pair;
	mpz_init(pair);
	mpz_mod_ui(pair,n,2);
	if (mpz_cmp_ui(pair,0) == 0)
	{ // SI n % 2 est egale a 0
		mpz_clear(pair);
		return 0;
	}

	mpz_t nMoins1, alea, temoin;
	mpz_inits(nMoins1, alea, temoin, NULL);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_sub_ui(nMoins1, n, 1); // n - 1
	for(int i=0; i<rep; i++)
	 { 	//printf("ici for\n");
		gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));			
		mpz_urandomm (alea , state , nMoins1);
		// gmp_printf("alea = %Zd\n", alea);

		if(mpz_cmp_ui(alea, 2) < 0)
		{//printf("ici comp\n");
			mpz_add_ui(alea, alea, 2);
		}
		temoinMiller(temoin, alea, n);
		if (mpz_cmp_ui(temoin, 0) > 0)
		{//printf("ici temoin\n");
			// printf("ce nombre est composé\n");
			mpz_clears(nMoins1, alea, temoin, pair, NULL);
			gmp_randclear(state);
			return 0;
		}
	}
	// printf("ce nombre est premier\n");
	mpz_clears(nMoins1, alea, temoin, pair, NULL);
	gmp_randclear(state);
	return 1;
}

/*! \fn int solovayStrassen(mpz_t aTraiter, int iterations)
 *  \brief Fonction permettant de calculer si un nombre est premier ou composé.
 *  \param aTraiter : le nombre que l'on désire traiter.
 *  \param iterations : le nombre d'iterations que l'on désire faire lors du teste.
 *  \return on retourne 1 s'il est premier ou bien 0 s'il est composé
 */
int solovayStrassen(mpz_t aTraiter, int iterations) 
{	
	if (mpz_cmp_ui(aTraiter,2) < 0)
		return 0;

	if(mpz_cmp_ui(aTraiter, 2) == 0 || mpz_cmp_ui(aTraiter, 3) == 0)
	{
		return 1;
	}
	
	mpz_t tmp;
	mpz_init(tmp);
	mpz_mod_ui(tmp,aTraiter,2);
	if (mpz_cmp_ui(tmp,0) == 0){ // SI aTraiter % 2 est egale a 0
		mpz_clear(tmp);
		return 0;
	}
	
	int jacobi = 0;
	mpz_t i,randomNumber,exposant,resultatM,itt,r,aTraiterMoins1;
	mpz_inits(i,randomNumber,exposant,resultatM,itt,r,aTraiterMoins1,NULL);
	
	mpz_set_ui(itt,iterations);
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	//mpz_sub_ui(exposant,aTraiter,1); //On fait exposant-1
	mpz_sub_ui(aTraiterMoins1,aTraiter,1); //On fait exposant-1
	for (mpz_set_ui(i,0); mpz_cmp(i,itt) < 0; mpz_add_ui(i, i, 1)) {
		gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));	
		mpz_urandomm (randomNumber , state , aTraiter);
		
		if(mpz_cmp_ui(randomNumber, 2) < 0)
			mpz_add_ui(randomNumber, randomNumber, 2);
		
		jacobi = jacobiSymbol(randomNumber, aTraiter);
		
		critere_euler(resultatM, randomNumber,aTraiter);
		//~ mpz_cdiv_q_ui(exposant, aTraiterMoins1, 2);
		//~ mpz_mod_ui(r, aTraiterMoins1, 2);
		//~ mpz_sub(exposant,exposant,r);
		//~ squareAndMultiply(resultatM, randomNumber, exposant, aTraiter);
		
		// Si jacobie donne 0 et que jacobi est different de l'exponentiation modulaire, alors on renvoi 0
		if(jacobi == 0 || ( jacobi != -1 && mpz_cmp_ui(resultatM,jacobi) != 0) || (jacobi == -1 && mpz_cmp(resultatM, aTraiterMoins1) != 0)){
			mpz_clears(i,randomNumber,tmp, exposant, itt, resultatM,r,aTraiterMoins1,NULL);
			gmp_randclear(state);
			return 0;
		}
	}
	mpz_clears(i,randomNumber,tmp,resultatM, exposant, itt, r, aTraiterMoins1,NULL);
	gmp_randclear(state);
	return 1;
}

int Lucas()


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
