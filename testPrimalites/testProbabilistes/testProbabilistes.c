#include "testProbabilistes.h"

/*! \file      testProbabilistes.c
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

/*! \fn Test_Fibo(mpz_t res,mpz_t n)
 * 	\brief Fonction permettant de calculer le theoreme de Fibo et Lucas
 * 	\param res : resultat
 *	\param n : nombre entier premier
 */
void Test_Fibo(mpz_t res,mpz_t n)
{
	int en;
	mpf_set_default_prec(PRECISION);
		
	mpz_t Un,nMoinsen,engmp,cinq;
	mpz_inits(Un,engmp,nMoinsen,cinq,NULL);
	
	
	mpz_set_ui(cinq,5);
	en=jacobiSymbol(n,cinq);

	//gmp_printf("jacobi(%Zd,%Zd)=%d\n",n,cinq,en);
		
	if(en == -1)
	{
		mpz_set_ui(engmp,1);
		mpz_neg(engmp,engmp);
		
		mpz_sub(nMoinsen,n,engmp);	
	}
	else
	{
		mpz_sub_ui(nMoinsen,n,en);
	}
	
	suiteFibo_or(Un,nMoinsen);
	
	//gmp_printf("suitefibo%Zd=%Zd\n",nMoinsen,Un);
	//gmp_printf("U(n-en)=%Zd\n",Un);
	
	mpz_mod(res,Un,n);
	
	mpz_clears(Un,engmp,nMoinsen,cinq,NULL);
}

/*! \fn Test_Lucas(mpz_t res,mpz_t n)
 * 	\brief Fonction permettant de calculer le theoreme de Lucas
 * 	\param res : resultat
 *	\param n : nombre entier
 */
void Test_Lucas(mpz_t res,mpz_t n)
{
	int en;
	mpf_set_default_prec(PRECISION);
		
	mpz_t Un,nMoinsen,engmp,cinq,a,b,delta,deltab2,pgcd_p_db2;
	mpz_inits(Un,engmp,nMoinsen,cinq,a,b,delta,deltab2,pgcd_p_db2,NULL);
	
	mpz_set_ui(a,1);
	mpz_set_ui(b,1);
	mpz_neg(b,b);
	
	calcul_discriminant(delta,a,b);
	
	mpz_mod_ui(b,b,2);
	mpz_mod(deltab2,b,delta);
	
	pgcd(pgcd_p_db2,n,deltab2);
	
	
	mpz_set_ui(cinq,5);
	en=jacobiSymbol(n,cinq);

	//gmp_printf("jacobi(%Zd,%Zd)=%d\n",n,cinq,en);
		
	if(en == -1)
	{
		mpz_set_ui(engmp,1);
		mpz_neg(engmp,engmp);
		
		mpz_sub(nMoinsen,n,engmp);	
	}
	else
	{
		mpz_sub_ui(nMoinsen,n,en);
	}
	
	suiteFibo_or(Un,nMoinsen);
	
	//gmp_printf("suitefibo%Zd=%Zd\n",nMoinsen,Un);
	//gmp_printf("U(n-en)=%Zd\n",Un);
	
	mpz_mod(res,Un,n);
	
	mpz_clears(Un,engmp,nMoinsen,cinq,a,b,delta,deltab2,pgcd_p_db2,NULL);
}

//En cours!!!!!!!!!!

/*! \fn LucasFrobenius(mpz_t n, mpz_t a, mpz_t b, mpz_t delta)
 * 	\brief Fonction permettant de calculer le theoreme de Lucas
 * 	\param n : nombre entier à tester strictement supérieur à 1
 *	\param a : nombre entier aléatoire
 *	\param b : nombre entier aléatoire
 *	\param delta : nombre entier
 */
void LucasFrobenius(mpz_t res, mpz_t n, mpz_t a, mpz_t b, mpz_t delta)
{
	int jac = -40; // juste une initialisation
	mpz_t u, v, V0, V1, A, m,test1, test1Mod, test2, test2Mod, aCarre, invB, jacobi, nMoins1, B, expo, test3;
	mpz_inits(u, v, V0, V1, A, m,test1, test1Mod, test2, test2Mod, aCarre, invB, jacobi,nMoins1, B, expo, test3, NULL);


	// 1) [Auxiliary parameters
	// A = a² b^(-1)  -  2 mod n
	// m = (n - (delta/n) ) / 2
	int exist = mpz_invert (invB , b , n );
	if(exist == 0)
	{
		printf("inverse de b n'existe pas\n");
		return;
	}
	
	mpz_mul(aCarre, a, a);
	mpz_mul(A, aCarre, invB);
	mpz_sub_ui(A, A, 2);
	mpz_mod(A, A, n);
	//gmp_printf("A = %Zd\n", A);

	// jac = jacobiSymbol(delta, n);
	// printf("jac = %d\n", jac);
	jac = jacobiSymbol(delta, n);
	mpz_set_si(jacobi, jac);
	//gmp_printf("jacobi(%Zd/%Zd) = %Zd\n", delta, n, jacobi);
	mpz_sub(m, n, jacobi);
	//gmp_printf("m = %Zd\n", m);
	mpz_div_ui(m, m, 2);
	//gmp_printf("m = %Zd\n", m);
	


	mpz_set_ui(V0, 2);
	mpz_set(V1, A);
	// [Binary Lucas chain]
	// 2) u = Vm, v = Vm+1
	chaineLucasBinaire(u, v, V0, V1, m, n);
	//gmp_printf("u = %Zd et v = %Zd\n", u, v);

	// 3) [Declaration]
	// test1 = AVm mod n
	// test2 = 2Vm+1 mod n
	mpz_mul(test1, A, u);
	mpz_mod(test1Mod, test1, n);
	mpz_mul(test2, V0, v);
	mpz_mod(test2Mod, test2, n);
	// gmp_printf("test1 = %Zd et test2 = %Zd\n", test1, test2);
	// gmp_printf("test1Mod = %Zd et test2Mod = %Zd\n", test1Mod, test2Mod);

	  if(mpz_cmp(test1Mod, test2Mod) == 0)
	  {
	  	gmp_printf("%Zd est un nombre de lucas problement 1er\n", n);
	  	//mpz_set_ui(res, 1);
	  	//mpz_clears(u, v, V0, V1, A, m,test1, test1Mod, test2, test2Mod, aCarre, invB, jacobi,nMoins1, B, expo, test3, NULL);
	  	//return;
	  }
	// 3')  [Lucas test]
	if(mpz_cmp(test1Mod, test2Mod) != 0)
	{
	 	gmp_printf("%Zd est un nombre composé de lucas\n", n);
	 	mpz_set_ui(res, 0);
	 	//mpz_clears(u, v, V0, V1, A, m,test1, test1Mod, test2, test2Mod, aCarre, invB, jacobi,nMoins1, B, expo, test3, NULL);
	 	//return;
	}
	
	// 4)  [Frobenius test]
	mpz_sub_ui(nMoins1, n, 1);
	mpz_div_ui(expo, nMoins1, 2);
	//gmp_printf("expo = %Zd\n", expo);
	squareAndMultiply(B, b, expo, n);
	mpz_mul(test3, B, u);
	//gmp_printf("test3 = %Zd\n", test3);
	mpz_mod(test3, test3, n);
	//gmp_printf("test3 = %Zd\n", test3);
	if(mpz_cmp(test3, V0) == 0)
	{
		gmp_printf("%Zd est un nombre de frobenius problement 1er\n", n);
		mpz_set_ui(res, 1);
		return;
	}


	gmp_printf("%Zd est un nombre composé de frobenius\n", n);
	mpz_set_ui(res, 0);
	mpz_clears(u, v, V0, V1, A, m,test1, test1Mod, test2, test2Mod, aCarre, invB, jacobi, nMoins1, B, expo, test3, NULL);
}


void LucasFrobenius_avecIteration(mpz_t res_t, mpz_t n_t, int iter, int intervalAlea)
{
	mpz_t  a_t, b_t, delta_t, abdelta, gcd,n,x, expo, racine,Test,alea;
	mpz_inits( a_t, b_t, delta_t, abdelta, gcd,n,x, expo,racine,Test,alea, NULL);
	mpz_set_ui(x, 2);
	mpz_set_ui(expo, intervalAlea);
	expoRapide(n, x, expo);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	for(int i = 0; i<iter; i++)
	{
		do
		{
			gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
			mpz_urandomm (alea , state , n);
			//mpz_set_ui(res_t, -1);
			// mpz_set_ui(n_t, 12);
			mpz_set(a_t, alea);
			
			mpz_set_ui(b_t, 1);
			calcul_discriminant(delta_t,a_t,b_t);
			mpz_sqrtrem(racine, Test, delta_t);;
			mpz_mul(abdelta, a_t, b_t);
			mpz_mul(abdelta, abdelta, delta_t);
			mpz_mul_ui(abdelta, abdelta, 2);
			pgcd(gcd, n_t, abdelta);
		}while(mpz_cmp_ui(Test, 0) == 0 && (mpz_cmp_ui(a_t, 0) == 0) && mpz_cmp_ui(gcd, 1) == 0);

		gmp_printf("alea %Zd\n", a_t);
		gmp_printf("delta %Zd\n", delta_t);
		gmp_printf("abdelta = %Zd\n\n", abdelta);

		LucasFrobenius(res_t, n_t, a_t, b_t, delta_t);
		
	}
	
		
	mpz_clears( a_t, b_t, delta_t, abdelta, gcd,n,x, expo, racine,Test,alea, NULL);
	gmp_randclear(state);
}