#include "miller.h"

void Miller_Rabin(mpz_t n, mpz_t rep)
{
	gmp_randstate_t state;
	mpz_inits(pgcd, sqm, alea, expo, NULL);
	gmp_randinit_mt(state);
	mpz_sub_ui(expo, n, 1); // expo = n - 1
	for(int i=0; i<iter; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , n);
		if(mpz_cmp_ui(alea, 2) < 0)
		{
			mpz_add_ui(alea, alea, 2);
		}
}


void temoinMiller(mpz_t res, mpz_t a, mpz_t n)
{
	mpz_t s, mpz_t d, nMoins1, x;
	mpz_inits(s, d, nMoins1,x, NULL);

	mpz_sub_ui(nMoins1, n, 1);

	decomposition(nMoins1, s, d);

	squareAndMultiply_gmp(x, a, d, n);
	if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp_ui(x, nMoins1) == 0)
	{
		mpz_set_ui(res, 0);
		return ;
	}
	while(mpz_cmp_ui(s, 1) > 0)
	{
		mpz_mul(x, x, x);
		mpz_mod(x, x, n);
		if(mpz_cmp(x, nMoins1) == 0)
		{
			mpz_set_ui(res, 0);
			return ;
		}
		mpz_sub_ui(s, 1);
	}
	mpz_set_ui(res, 1);
	return ;
}