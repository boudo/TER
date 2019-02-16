#include "testProbabilistes.h"
// #include "../fonctions/fonctions.h"


// ************* Fermat ***************************
int Fermat(mpz_t n, int iter)
{
	printf("taille = %d\n", iter);
	mpz_t pgcd, sqm, alea, expo;
	gmp_randstate_t state;
	mpz_inits(pgcd, sqm, alea, expo, NULL);
	gmp_randinit_mt(state);
	mpz_sub_ui(expo, n, 1); // expo = n - 1
	for(int i=0; i<iter; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , n);
		if(mpz_cmp_ui(alea, 3) < 0)
		{
			mpz_add_ui(alea, alea, 3);
		}
		pgcd_gmp(pgcd, n, alea);
		if (mpz_cmp_ui(pgcd, 1) != 0)
		{
			gmp_printf("pgcd = %Zd et alea = %Zd donc %Zd est composé\n",pgcd,alea, n);
			mpz_clears(pgcd, sqm, alea, expo, NULL);
			gmp_randclear(state);
			return 0;
		}
		//mpz_sub_ui(expo, n, 1);printf("Fermat\n");
		// mpz_set(expo, n);
		// mpz_sub_ui(expo, n, 1);
		//printf("debut\n");
		squareAndMultiply_gmp(sqm, alea, expo, n);
		//printf("debut\n");
		//mpz_powm(sqm, alea, expo, n);
		//printf("Fermat\n");
		if(mpz_cmp_ui(pgcd, 1) == 0 && mpz_cmp_ui(sqm, 1) != 0)
		{
			gmp_printf("sqm = %Zd et alea = %Zd expo = %Zd donc  %Zd est composé pgcd = %Zd\n", sqm, alea, expo, n, pgcd);
			mpz_clears(pgcd, sqm, alea, expo, NULL);
			gmp_randclear(state);
			return 0;
		}
	}


	gmp_printf("sqm = %Zd et %Zd est 1er pgcd = %Zd et alea =  %Zd\n", sqm, n, pgcd, alea);
	mpz_clears(pgcd, sqm, alea, expo, NULL);
	gmp_randclear(state);
	return 1;
}

// ************* Miller ***************************
void Miller_Rabin(mpz_t n, int rep)
{
	mpz_t nMoins2, alea, temoin;
	mpz_inits(nMoins2, alea, temoin, NULL);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_sub_ui(nMoins2, n, 2); // n - 2

	for(int i=0; i<rep; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , nMoins2);
		if(mpz_cmp_ui(alea, 2) < 0)
		{
			mpz_add_ui(alea, alea, 2);
		}
		temoinMiller(temoin, alea, n);
		if (mpz_cmp_ui(temoin, 0) > 0)
		{
			printf("ce nombre est composé\n");
			mpz_clears(nMoins2, alea, temoin, NULL);
			gmp_randclear(state);
			return ;
		}
	}
	printf("ce nombre est premier\n");
	mpz_clears(nMoins2, alea, temoin, NULL);
	gmp_randclear(state);
}


void temoinMiller(mpz_t res, mpz_t a, mpz_t n)
{
	mpz_t s, d, nMoins1, x;
	mpz_inits(s, d, nMoins1,x, NULL);

	mpz_sub_ui(nMoins1, n, 1);

	decomposition(nMoins1, s, d);

	squareAndMultiply_gmp(x, a, d, n);
	if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, nMoins1) == 0)
	{
		mpz_set_ui(res, 0);
		mpz_clears(s, d, nMoins1,x, NULL);
		return ;
	}
	while(mpz_cmp_ui(s, 1) > 0)
	{
		mpz_mul(x, x, x);
		mpz_mod(x, x, n);
		if(mpz_cmp(x, nMoins1) == 0)
		{
			mpz_set_ui(res, 0);
			mpz_clears(s, d, nMoins1,x, NULL);
			return ;
		}
		mpz_sub_ui(s, s, 1);
	}
	mpz_set_ui(res, 1);
	mpz_clears(s, d, nMoins1,x, NULL);
	return ;
}
