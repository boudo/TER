#include "fonctions.h"

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


void decomposition(mpz_t x,mpz_t s,mpz_t t) // Fonction qui décompose un entier x en 2^s * t
{                                    
	mpz_t y,S_pow, deux;
	mpz_inits(y,S_pow, deux, NULL);

	mpz_set_ui(y,0);
	mpz_set_ui(deux, 2);

	while(mpz_cmp(y,x)!=0) // Tant que on trouve pas 2^s * t = x
	{
        mpz_set_ui(t,1); //On recommence avec t = 1
        mpz_mul(y,S_pow,t);// y = 2^s * t (on test les valeurs)

        while(mpz_cmp(y,x) < 0)// On arrette de tester quand 2^s * t > x
        {                      //
			mpz_add_ui(t,t,2); // t est impair donc on l'incremente de 2 en 2
			
			//deux_pow(S_pow,s);
			expoRapide_gmp(S_pow, deux, s);
			mpz_mul(y,S_pow,t);
        }
        
        mpz_add_ui(s,s,1); // on test avec la puissante de 2 suivante
	}
	mpz_sub_ui(s,s,1);

	mpz_clears(y,S_pow, deux,NULL);
}
