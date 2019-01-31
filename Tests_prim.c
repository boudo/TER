#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include <gmp.h>
#include <time.h>



void pgcd_gmp(mpz_t resultat, const mpz_t a, const mpz_t b) // pgcd(1,1)
{
	if(mpz_cmp(a,b) == 0)
	{
		mpz_set(resultat, a);
		//printf("a == b\n");
	}
	else if(mpz_cmp(a, b) > 0) // si la val mpz_cmp positif
	{
		if(mpz_cmp_ui(b, 0) == 0) // si la val mpz_cmp == 0
		{
			mpz_set(resultat, a);
			//printf("b == 0\n");
		}
		else if(mpz_cmp_ui(b, 1) == 0)
		{
			mpz_set_ui(resultat, 1);
			//printf("b == 1\n");

		}
		else
		{
			mpz_t reste;
			mpz_init(reste);

			mpz_mod(reste, a, b);
			pgcd_gmp(resultat, b, reste);
			//printf("pgcd b a mod b\n");

			mpz_clear(reste);
		}
	}
	else
	{
		pgcd_gmp(resultat, b, a);
		//printf("pgcd b a\n");
	}
}

liste expoEnBinMpz(const mpz_t expo)
{
	int r = 0;
	liste maListe = creer_liste();
	mpz_t rest, tmp;
	mpz_inits(rest, tmp, NULL);
	mpz_set(tmp, expo);

	while(mpz_cmp_ui(tmp, 0) > 0)
	{
		r = (int) mpz_cdiv_r_ui(rest, tmp, 2);
		//printf("r = %d\n", r);
		maListe = ajoute_elem_debut(maListe, r);
		mpz_div_ui(tmp, tmp, 2);

	}
	mpz_clears(rest, tmp, NULL);
	//affiche_liste(maListe);
	//maListe = libere_liste(maListe);
	return maListe;
}

liste expoEnBinMpz2(const mpz_t expo)
{
	int r = 0;
	liste maListe = creer_liste();
	mpz_t rest, tmp, deux;
	mpz_inits(rest, tmp, deux, NULL);
	mpz_set(tmp, expo);
	mpz_set_ui(deux, 2);

	while(mpz_cmp_ui(tmp, 0) > 0)
	{
		mpz_mod(rest, tmp, deux);
		r = mpz_get_ui(rest);
		//printf("r = %d\n", r);
		maListe = ajoute_elem_debut(maListe, r);
		mpz_div(tmp, tmp, deux);
	}
	mpz_clears(rest, tmp, deux, NULL);
	//affiche_liste(maListe);
	return maListe;
}

void deuxFois(mpz_t res, int expo)
{
	mpz_set_ui(res, 1);
	for (int i = 0; i < expo; i++)
	{
		mpz_mul_ui(res, res, 2);
	}
}

void expoRapide_gmp(mpz_t resultat, const mpz_t x, const mpz_t expo)
{
	mpz_set(resultat, x);
	liste expoB = creer_liste();
	expoB = expoEnBinMpz(expo);
	expoB = supprime_elem_debut(expoB);

	while(!est_vide(expoB))
	{
		mpz_mul(resultat, resultat, resultat);
		//printf("sq\n");
		if(expoB->val == 1)
		{
			mpz_mul(resultat, resultat, x);
			//printf("mul\n");
		}
		expoB = supprime_elem_debut(expoB);
	}
}

void expoRapide_gmp1(mpz_t resultat, const mpz_t x, const mpz_t expo)
{
	mpz_set(resultat, x);
	liste expoB = creer_liste();
	expoB = expoEnBinMpz(expo);
	expoB = supprime_elem_debut(expoB);

	while(!est_vide(expoB))
	{
		mpz_mul(resultat, resultat, resultat);
		//printf("sq\n");
		if(expoB->val == 1)
		{
			mpz_mul(resultat, resultat, x);
			//printf("mul\n");
		}
		expoB = supprime_elem_debut(expoB);
	}
}

void squareAndMultiply_gmp(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul)
{
	mpz_set(resultat, x);
	liste expoB = creer_liste();
	expoB = expoEnBinMpz(expo);
	//printf("OK pour expoBinMPZ\n");
	expoB = supprime_elem_debut(expoB);

	while(!est_vide(expoB))
	{
		mpz_mul(resultat, resultat, resultat);
		mpz_mod(resultat, resultat, modul);
		if(expoB->val == 1)
		{
			mpz_mul(resultat, resultat, x);
			mpz_mod(resultat, resultat, modul);
		}
		expoB = supprime_elem_debut(expoB);
	}
	expoB = libere_liste(expoB);
}

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
		printf("debut\n");
		//squareAndMultiply_gmp(sqm, alea, expo, n);
		printf("debut\n");
		mpz_powm(sqm, alea, expo, n);
		printf("Fermat\n");
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


int main()
{	
	mpz_t pgcdM, pgcdG, base, expo, modul, base1, expo1, modul1, deux, tmp, tmp1,ex, f;
	mpz_inits(pgcdM, pgcdG,base, expo, modul, base1, expo1, modul1,deux, tmp, tmp1,ex,f,  NULL);
	
	
	mpz_set_ui(deux, 2);
	mpz_set_ui(pgcdM, 0);
	mpz_set_ui(pgcdG, 0);
	
	mpz_set_ui(ex, 2281);
	expoRapide_gmp(expo, deux, ex);
	//mpz_init2(t, 23209);
	//expoRapide_gmp1(t, deux, ex);
	mpz_pow_ui(expo1, deux, 2281);

	mpz_sub_ui(tmp, expo, 100000000000000);
	mpz_sub_ui(tmp1, expo1, 100000000000000);

	mpz_set(base, tmp);
	mpz_set(base1, tmp1);

	mpz_sub_ui(expo, expo, 1);
	mpz_sub_ui(expo1, expo1, 1);
	deuxFois(f, 2281);

	gmp_printf("mon modul = %Zd\n", expo);
	//gmp_printf("ttt modul = %Zd\n", t);
	gmp_printf("duex foi    %Zd\n", f);
	gmp_printf("gmp modul = %Zd\n", expo1);
	// mpz_set_ui(expo, 3099999999999);
	// mpz_set_ui(expo1, 3099999999999);
	mpz_set(modul, expo);
	mpz_set(modul1, expo1);
	mpz_sub_ui(expo, expo, 1);
	mpz_sub_ui(expo1, expo1, 1);

	liste l = creer_liste();
	liste ll = creer_liste();
	l = expoEnBinMpz(expo);
	ll = expoEnBinMpz2(expo);
	printf("les duex liste = %d\n", compare_liste(l,ll));
	l = libere_liste(l);
	ll = libere_liste(ll);

	//pgcd_gmp(pgcdM, base, expo);
	//squareAndMultiply_gmp(pgcdM, base, expo, modul);
	gmp_printf("mon pgcd = %Zd\n", pgcdM);

	//mpz_gcd(pgcdG, base1, expo1);
	//mpz_powm(pgcdG, base1, expo1, modul1);
	gmp_printf("gmp pgcd = %Zd\n", pgcdG);

	mpz_clears(pgcdM, pgcdG,base, expo, modul, base1, expo1, modul1,deux,tmp,tmp1,ex,f, NULL);
	return 0;
}
