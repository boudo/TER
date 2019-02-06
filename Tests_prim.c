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

void deux_pow(mpz_t res,mpz_t s) // Fonction qui rentre 2^s dans res
{
  int i = 0;
  mpz_set_ui(res,1); // on initialise res à 2^0

  while(mpz_cmp_si(s,i) > 0 ) // On multiplie res par 2 tant que i < s
  {
    mpz_mul_ui(res,res,2);
    i++;
  }

}

void decomposition(mpz_t x,mpz_t s,mpz_t t) // Fonction qui décompose un entier x en 2^s * t
{                                    
	mpz_t y,S_pow;
	mpz_inits(y,S_pow,NULL);

	mpz_set_ui(y,0);

	while(mpz_cmp(y,x)!=0) // Tant que on trouve pas 2^s * t = x
	{
        mpz_set_ui(t,1); //On recommence avec t = 1
        mpz_mul(y,S_pow,t);// y = 2^s * t (on test les valeurs)

        while(mpz_cmp(y,x) < 0)// On arrette de tester quand 2^s * t > x
        {                      //
			mpz_add_ui(t,t,2); // t est impair donc on l'incremente de 2 en 2
			
			deux_pow(S_pow,s);
			mpz_mul(y,S_pow,t);
        }
        
        mpz_add_ui(s,s,1); // on test avec la puissante de 2 suivante
	}
	mpz_sub_ui(s,s,1);

	mpz_clears(y,S_pow,NULL);
}

int main()
{
	mpz_t pgcd_r,pgcd_a,pgcd_b,a,n,h;//Declaration r,pgcda,pgcdb
	mpz_inits(pgcd_r,pgcd_a,pgcd_b,a,n,h,NULL);//Init

	gmp_printf("\n###################### Test PGCD ######################\n\n");
	
	mpz_set_ui(pgcd_a,6);//Affectation
	mpz_set_ui(pgcd_b,4);
	
	pgcd_gmp(pgcd_r,pgcd_a,pgcd_b);
	
	gmp_printf("PGCD(%Zd,%Zd)=%Zd\n",pgcd_a,pgcd_b,pgcd_r);//Affichage
	
	
	
	gmp_printf("\n###################### Test SQUARE AND MULTIPLY ######################\n\n");
	
	mpz_t sm_r;
	mpz_inits(sm_r,NULL);
	
	mpz_set_ui(a,188);
	mpz_set_ui(n,527);
	mpz_set_ui(h,2);
	
	squareAndMultiply_gmp(sm_r,a,h,n);
	
	gmp_printf("SQUARE=%Zd mod %Zd\n\n",sm_r,n);
	
	gmp_printf("\n###################### Test FERMAT ######################\n\n");
	
	mpz_t f,e_a,e_exp;
	mpz_inits(f,e_a,e_exp,NULL);
	
	mpz_set_ui(e_a,2);
	mpz_set_ui(e_exp,521);
	
	expoRapide_gmp(f,e_a,e_exp);
	mpz_sub_ui(f,f,1);
	
	Fermat(f,5);
	
	gmp_printf("\n###################### Test Decomposition ######################\n\n");
	
	mpz_t d_a,d_r,d_exp;
	mpz_inits(d_a,d_r,d_exp,NULL);
	
	mpz_set_ui(d_r,561);
	gmp_printf("%Zd=",d_r);
	mpz_sub_ui(d_r,d_r,1);
	
	decomposition(d_r,d_exp,d_a);
	
	gmp_printf("%Zd-1=2^%Zd*%Zd\n",d_r,d_exp,d_a);
	
	mpz_clears(pgcd_r,d_a,d_r,d_exp,pgcd_a,pgcd_b,f,e_a,e_exp, sm_r,a,n,h,NULL);//Clears
	
	return 0;
}
