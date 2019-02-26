#include "fonctions.h"

/*! \file      fonctions.c
 *  \brief     Fichier contenant les différentes fonctions nécessaires au bon fonctionnement du programme
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */
 
//LISTE

/*! \fn liste creer_liste()
 *  \brief Fonction qui créer une liste vide
 *  \return retourne la liste vide
 */
liste creer_liste(){return NULL;}

/*! \fn int est_vide(liste l)
 *  \brief Fonction qui permet de savoir si une liste est vide ou non
 *  \param l : liste l
 *  \return retourne 1 si la liste est vide ,sinon 0
 */
int est_vide(liste l)
{
	if(l == NULL)
		return 1;
	return 0;
}

/*! \fn void affiche_liste(liste l)
 *  \brief Fonction qui permet d'afficher le contenu de la liste
 *  \param l : liste l
 */
void affiche_liste(liste l)
{
	
	if(est_vide(l))
	{
		printf("La liste est vide \n");
		return;
	}
	while(l)
	{
		printf("%d ",l->val);
		l = l->suiv;
	}
	printf("\n");
}

/*! \fn liste libere_liste(liste l)
 *  \brief Fonction qui permet de liberer la liste
 *  \param l : liste l
 *  \return retourne NULL quand la liste est vide
 */
liste libere_liste(liste l)
{
	liste tmp;
	while(l)
	{
		tmp = l->suiv;
		free(l);
		l = tmp;
	}
	return NULL;
}

/*! \fn liste ajoute_elem_debut(liste l,mpz_t i,int p)
 *  \brief Fonction qui ajoute au début un élément dans la liste
 *  \param l : liste l
 *  \param i : valeur i à ajouter
 *  \return retourne la liste avec l'élément ajouté
 */
liste ajoute_elem_debut(liste l,int i)
{
	liste new = malloc(sizeof(struct elem));
	new->val = i;
	new->suiv = l;
	return new;
}

/*! \fn liste supprime_elem_debut(liste l)
 *  \brief Fonction qui supprime au début un élément dans la liste
 *  \param l : liste l
 *  \return retourne la liste moins l'élément qu'on a supprimé
 */
liste supprime_elem_debut(liste l)
{
	if(est_vide(l))
	{
		return l;
	}

	liste tmp;
	tmp = l->suiv;
	free(l);
	return tmp;
}

//LISTE GMP

/*! \fn listegmp creer_listegmp()
 *  \brief Fonction qui créer une liste vide
 *  \return retourne la liste vide
 */
listegmp creer_listegmp()
{
	return NULL;
}

/*! \fn listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i,int p)
 *  \brief Fonction qui ajoute au début un élément dans la liste
 *  \param l : liste l
 *  \param i : valeur i à ajouter
 *  \param p : entier p représenant la primalité
 *  \return retourne la liste avec l'élément ajouté
 */
listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i,int p)
{
	listegmp new = malloc(sizeof(struct elemgmp));
	
	mpz_init(new->val);
	mpz_set(new->val,i);
	
	new->primalite = p;
	new->suiv = l;
	
	return new;
}

/*! \fn int est_videgmp(listegmp l)
 *  \brief Fonction qui permet de savoir si une liste est vide ou non
 *  \param l : liste l
 *  \return retourne 1 si la liste est vide ,sinon 0
 */
int est_videgmp(listegmp l)
{
	if(l == NULL)
		return 1;
	return 0;
}

/*! \fn void affiche_listegmp(listegmp l)
 *  \brief Fonction qui permet d'afficher le contenu de la liste
 *  \param l : liste l
 */
void affiche_listegmp(listegmp l)
{
	if(est_videgmp(l))
	{
		gmp_printf("La liste est vide \n");
		return;
	}
	while(l)
	{
		gmp_printf("%Zd(%d) ",l->val,l->primalite);
		l = l->suiv;
	}
	gmp_printf("\n");
}

/*! \fn listegmp libere_listegmp(listegmp l)
 *  \brief Fonction qui permet de liberer la liste
 *  \param l : liste l
 *  \return retourne NULL quand la liste est vide
 */
listegmp libere_listegmp(listegmp l)
{
	listegmp tmp;
	
	while(l)
	{
		tmp = l->suiv;

		mpz_clears(l->val,NULL);
		free(l);
		l = tmp;
	}
	return NULL;
}

//FONCTIONS

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
	expoB = getBinaire(expo);
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

/*! \fn liste getBinaire(const mpz_t expo)
 *  \brief Fonction qui calcule l'exposant en binaire
 *  \param expo : exposant
 *  \return retourne la liste contenant le nombre en binaire
 */
liste getBinaire(const mpz_t expo)
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
	expoB = getBinaire(expo);
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


/*! \fn void decomposition(mpz_t s,mpz_t d,mpz_t nMoins1)
 *  \brief Fonction qui decompose un entier x en 2^s * d
 *  \param s : entier s
 *  \param d : exposant d
 *  \param nMoins1 : entier nMoins1
 */
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

void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n)
{
	gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
	mpz_urandomb(alea, state, n);
}
