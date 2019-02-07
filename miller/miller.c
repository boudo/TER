#include "miller.h"

void Miller_Rabin(mpz_t n, int rep)
{
	mpz_t nMoins1, alea, temoin;
	mpz_inits(nMoins1, alea, temoin, NULL);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_sub_ui(nMoins1, n, 1); // n - 1

	for(int i=0; i<rep; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , nMoins1);
		if(mpz_cmp_ui(alea, 2) < 0)
		{
			mpz_add_ui(alea, alea, 2);
		}
		temoinMiller(temoin, alea, n);
		if (mpz_cmp_ui(temoin, 0) > 0)
		{
			printf("ce nombre est composé\n");
			mpz_clears(nMoins1, alea, temoin, NULL);
			gmp_randclear(state);
			return ;
		}
	}
	printf("ce nombre est premier\n");
	mpz_clears(nMoins1, alea, temoin, NULL);
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