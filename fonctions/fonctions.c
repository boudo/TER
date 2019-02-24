#include "fonctions.h"

/*! \file      fonctions.c
 *  \brief     Fichier contenant les différentes fonctions nécessaires au bon fonctionnement du programme
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

/*! \fn void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b) 
 *  \brief Fonction qui calcule le pgcd entre a et b
 *  \param resultat : resultat
 *  \param a : nombre a
 *  \param b : nombre b
 */
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

/*! \fn void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul)
 *  \brief Fonction qui calcule le square and multiply
 *  \param resultat : resultat
 *  \param x : entier x
 *  \param expo : exposant
 *  \param modul : modulo
 */
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

/*! \fn liste expoEnBin(const mpz_t expo)
 *  \brief Fonction qui calcule l'exponention binaire
 *  \param expo : exposant
 *  \return retourne la liste contenant le nombre en binaire
 */
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

/*! \fn void expoRapide(mpz_t resultat, const mpz_t x, const mpz_t expo)
 *  \brief Fonction qui calcule l'exponention rapide
 *  \param resultat : resultat
 *  \param x : entier x
 *  \param expo : exposant
 */
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

/*! \fn void decomposition(mpz_t x,mpz_t s,mpz_t t)
 *  \brief Fonction qui decompose un entier x en 2^s * t
 *  \param x : entier x
 *  \param s : exposant s
 *  \param t : entier t
 */
void decomposition(mpz_t x,mpz_t s,mpz_t t) // Fonction qui décompose un entier x en 2^s * t
{                                    
	mpz_t y,S_pow, deux;
	mpz_inits(y,S_pow, deux, NULL);

	mpz_set_ui(y,0);
	mpz_set_ui(deux, 2);

	while(mpz_cmp(y,x)!=0) // Tant que on trouve pas 2^s * t = x
	{//printf("ici dans decom while 1\n"); // boucle infini
        mpz_set_ui(t,1); //On recommence avec t = 1
        mpz_mul(y,S_pow,t);// y = 2^s * t (on test les valeurs)

        while(mpz_cmp(y,x) < 0)// On arrette de tester quand 2^s * t > x
        {//printf("ici dans decom while 2\n");        //
			mpz_add_ui(t,t,2); // t est impair donc on l'incremente de 2 en 2
			
			//deux_pow(S_pow,s);
			expoRapide(S_pow, deux, s);
			mpz_mul(y,S_pow,t);
        }
        
        mpz_add_ui(s,s,1); // on test avec la puissante de 2 suivante
	}
	mpz_sub_ui(s,s,1);

	mpz_clears(y,S_pow, deux,NULL);
}

/*! \fn void decomposition1(mpz_t s,mpz_t d,mpz_t nMoins1)
 *  \brief Fonction qui decompose un entier x en 2^s * d
 *  \param s : entier s
 *  \param d : exposant d
 *  \param nMoins1 : entier nMoins1
 */
void decomposition1(mpz_t s,mpz_t d, mpz_t nMoins1)
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
