#include "fonctions.h"

void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b) // pgcd(1,1)
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
			pgcd(resultat, b, reste);
			//printf("pgcd b a mod b\n");

			mpz_clear(reste);
		}
	}
	else
	{
		pgcd(resultat, b, a);
		//printf("pgcd b a\n");
	}
}

void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul)
{
	mpz_set(resultat, x);
	liste expoB = creer_liste();
	expoB = expoEnBin(expo);
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

liste expoEnBin(const mpz_t expo)
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

void expoRapide(mpz_t resultat, const mpz_t x, const mpz_t expo)
{

	if(mpz_cmp_ui(expo, 0) == 0)
	{
		mpz_set_ui(resultat, 1);
		return ;
	}

	mpz_set(resultat, x);
	liste expoB = creer_liste();
	expoB = expoEnBin(expo);
	// printf("expo en bin\n");
	// affiche_liste(expoB);
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

void decomposition(mpz_t s,mpz_t d, mpz_t nMoins1)
{
	mpz_set_ui(s, 0);
	mpz_set_ui(d,0);
	mpz_t tmp, tmp1, deux,res;
	mpz_inits(tmp, tmp1, deux, res, NULL);
	mpz_set_ui(deux, 2);
	mpz_set(tmp, nMoins1);
	while(mpz_cmp_ui(tmp, 1) > 0)
	{	mpz_mod_ui(res, tmp, 2);
		if(mpz_cmp_ui(res, 0) == 0)
		{
			mpz_add_ui(s, s, 1);
			mpz_div_ui(tmp, tmp, 2);
		}
		else
		{
			break;
		}
	}
	// gmp_printf("ici nMoins1 = %Zd\n", nMoins1);
	// gmp_printf("ici s = %Zd\n", s);
	expoRapide(tmp1,deux, s);
	// gmp_printf("ici tmp1 = %Zd\n", tmp1);
	mpz_div(d, nMoins1, tmp1);
	// gmp_printf("ici d = %Zd\n", d);
	mpz_clears(tmp, tmp1, deux,res, NULL);
}
