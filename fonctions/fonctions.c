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

/*! \fn liste liste ajoute_elem_debut(liste l,int i)
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

/*! \fn listegmp crible_era_gmp(mpz_t n)
 *  \brief Fonction qui renvoie les nombres composés et premiers jusqu'à n
 *  \param n : entier n
 *  \return retourne la liste contenant les nombres composés et premiers de 2 jusqu'à n
 */
listegmp crible_era_gmp(mpz_t n)//amelioré avec la condition des multiples de nbr 1er qui sont composés
{
	mpz_t i,j,x,borne_sup_premier,carre_val_prim,multiple_val;
	mpz_inits(i,j,x,borne_sup_premier,carre_val_prim,multiple_val,NULL);
	
	listegmp lg = creer_listegmp();
	
	for(mpz_set(i,n);mpz_cmp_ui(i,1)>0;mpz_sub_ui(i,i,1))//On initialise la liste des nombres de 2 à N comme premiers(primalité=1).
	{	
		lg = ajoute_elem_debutgmp(lg,i,1);
	}
	
	// Amélioration : ne garder que les nombres premiers
	// On marque "composé" tous les nombres composés de la liste

	mpz_set(borne_sup_premier,n);
	listegmp tmp = lg;
	
	//~ listegmp debut = lg;
	//~ listegmp parcours;
	//~ listegmp tmp;
	
	while(tmp->suiv)
	{
		if(tmp->primalite == 1)
		{
			//Condition d'arret
			mpz_mul(carre_val_prim,tmp->val,tmp->val);
			
			if (mpz_cmp(carre_val_prim,borne_sup_premier)>0)
			{
				mpz_clears(i,j,x,borne_sup_premier,carre_val_prim,multiple_val,NULL);
				return lg;
			}
			
			//les multiples d'un nbr 1er sont composés
			listegmp compo = tmp;

			int m = 2;
			mpz_mul_ui(multiple_val,tmp->val,m);
			
			while(mpz_cmp(multiple_val,n) <= 0) 
			{
				for(mpz_set_ui(j,0);mpz_cmp(tmp->val,j)>0;mpz_add_ui(j,j,1)) 
				{
					//MAJ de la borne sup premier
					if(compo->primalite == 1)
					{
						mpz_set(borne_sup_premier, compo->val);
					}

					compo=compo->suiv;
				}
				compo->primalite = 0;
				m++;
				mpz_mul_ui(multiple_val,tmp->val,m);
			}		
		}
		tmp = tmp->suiv;
	}
	mpz_clears(i,j,x,borne_sup_premier,carre_val_prim,multiple_val,NULL);
	
	return lg;
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
	char* expoEnBin = NULL;
	int taille = 0;
	int i = 1;
	mpz_set(resultat, x);
	expoEnBin = mpz_get_str(NULL, 2, expo);
	taille = strlen(expoEnBin);
	// liste expoB = creer_liste();
	// expoB = getBinaire(expo);
	//printf("OK pour expoBinMPZ\n");
	// expoB = supprime_elem_debut(expoB);

	while(i < taille)
	{
		mpz_mul(resultat, resultat, resultat);
		mpz_mod(resultat, resultat, modul);
		if(expoEnBin[i] == '1')
		{
			mpz_mul(resultat, resultat, x);
			mpz_mod(resultat, resultat, modul);
		}

		// expoB = supprime_elem_debut(expoB);
		i++;
	}
	
	// expoB = libere_liste(expoB);
	free(expoEnBin);
}

/*! \fn liste getBinaire(const mpz_t expo)
 *  \brief Fonction qui calcule l'exposant en binaire
 *  \param expo : exposant
 *  \return retourne la liste contenant le nombre en binaire
 */
// liste getBinaire(const mpz_t expo)
// {
// 	int r = 0;
// 	liste maListe = creer_liste();
// 	mpz_t rest, tmp;
// 	mpz_inits(rest, tmp, NULL);
// 	mpz_set(tmp, expo);

// 	while(mpz_cmp_ui(tmp, 0) > 0)
// 	{
// 		r = (int) mpz_cdiv_r_ui(rest, tmp, 2);
// 		//printf("r = %d\n", r);
// 		maListe = ajoute_elem_debut(maListe, r);
// 		mpz_div_ui(tmp, tmp, 2);

// 	}
// 	mpz_clears(rest, tmp, NULL);
// 	//affiche_liste(maListe);
// 	//maListe = libere_liste(maListe);
// 	return maListe;
// }

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

	char* expoEnBin = NULL;
	int taille = 0;
	int i = 1;
	mpz_set(resultat, x);
	expoEnBin = mpz_get_str(NULL, 2, expo);
	taille = strlen(expoEnBin);
	// liste expoB = creer_liste();
	// expoB = getBinaire(expo);
	//printf("OK pour expoBinMPZ\n");
	// expoB = supprime_elem_debut(expoB);

	while(i < taille)
	{
		mpz_mul(resultat, resultat, resultat);
		// mpz_mod(resultat, resultat, modul);
		if(expoEnBin[i] == '1')
		{
			mpz_mul(resultat, resultat, x);
			// mpz_mod(resultat, resultat, modul);
		}

		// expoB = supprime_elem_debut(expoB);
		i++;
	}
	
	// expoB = libere_liste(expoB);
	free(expoEnBin);
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

/*! \fn void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n)
 * 	\brief Fonction permettant de generer un nombre aléatoire
 * 	\param alea : nombre aléatoire
 * 	\param state : etat pour modifier le random 
 * 	\param n : nombre de bits
 */
void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n)
{
	gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
	mpz_urandomb(alea, state, n);
}

/*! \fn void temoinMiller(mpz_t res, mpz_t a, mpz_t n)
 * 	\brief Fonction permettant de trouver les temoins de Miller
 * 	\param res : On renvoie le resultat.
 * 	\param a : a est le futur temoin de miller(ou non)
 * 	\param n : n est le nombre à tester
 */
void temoinMiller(mpz_t res, mpz_t a, mpz_t n)
{//printf("ici dans temoin\n");
	mpz_t s, d, nMoins1, modul, i, tmp, deux, tmp1;
	mpz_inits(s, d, nMoins1,modul, i, tmp, deux, tmp1, NULL);

	mpz_set_ui(deux, 2);
	mpz_sub_ui(nMoins1, n, 1);
	//printf("ici dans temoin test decomposition\n");
	// decomposition(nMoins1, s, d);
	decomposition(s, d, nMoins1);
	//printf("ici dans temoin\n");
	squareAndMultiply(modul, a, d, n);
	//printf("ici dans temoin ok\n");
	if(mpz_cmp_ui(modul, 1) == 0 || mpz_cmp(modul, nMoins1) == 0)
	{
		// printf("ce nombre n'est pas un temoin de composition 1\n");
		mpz_set_ui(res, 0);
		mpz_clears(s, d, nMoins1,modul, i, tmp, deux, tmp1, NULL);
		return ;
	}
	for(mpz_set_ui(i,1); mpz_cmp(i,s) < 0; mpz_add_ui(i, i, 1))
	{
		expoRapide(tmp, deux, i);
		mpz_mul(tmp1, d, tmp);
		squareAndMultiply(modul, a, tmp1, n);
		if(mpz_cmp(modul, nMoins1) == 0)
		{
			// printf("ce nombre n'est pas un temoin de composition 2\n");
			mpz_set_ui(res, 0);
			mpz_clears(s, d, nMoins1,modul, i, tmp, deux, tmp1, NULL);
			return ;
		}
		if(mpz_cmp_ui(modul, 1) == 0)
		{
			// printf("ce nombre est un temoin de composition 2\n");
			mpz_set_ui(res, 1);
			mpz_clears(s, d, nMoins1,modul, i, tmp, deux, tmp1, NULL);
			return ;
		}

	}
	expoRapide(tmp, deux, s);
	mpz_mul(tmp1, d, tmp);
	squareAndMultiply(modul, a, tmp1, n);
	if(mpz_cmp_ui(modul, 1) == 0)
	{	
		// gmp_printf("s %Zd\n", s);
		// gmp_printf("d %Zd\n", d);
		// gmp_printf("tmp %Zd\n", tmp);
		// gmp_printf("tmp1 %Zd\n", tmp1);
		// gmp_printf("alea %Zd\n", a);
		// gmp_printf("modul %Zd\n", x);
		// printf("ce nombre n'est pas un temoin de composition 3\n");
		mpz_set_ui(res, 0);
		mpz_clears(s, d, nMoins1,modul, i, tmp, deux, tmp1, NULL);
		return ;
	}

	// printf("ce nombre est un temoin de composition 4\n");
	mpz_set_ui(res, 1);
	mpz_clears(s, d, nMoins1,modul, i, tmp, deux, tmp1, NULL);
	return ;
}

/*! \fn int jacobiSymbol(mpz_t a, mpz_t b) 
 * 	\brief Fonction permettant de calculer le Symbole de jacobi (a/p) et de determiner si p divise a ou pas puis si a est un résidu quadratique modulo p ou non
 * 	\param a : a est un résidu quadratique ou non de b
 * 	\param b : b est un residu quadratique ou non de a ?
 */
int jacobiSymbol(mpz_t a, mpz_t b) 
{
	mpz_t tmpa,tmpb,tmp,tmp2;
	int t;
	mpz_inits(tmpa,tmpb,tmp,tmp2,NULL);
	mpz_set(tmpa,a);
	mpz_set(tmpb,b);
	if(mpz_cmp_ui(tmpa,1) == 0) {
		return 1;
	}
	mpz_mod(tmpa,tmpa,tmpb);// a = a % b
	t=1;
	while(mpz_cmp_ui(tmpa,0) != 0) {
		mpz_mod_ui(tmp,tmpa,2);
		while(mpz_cmp_ui(tmp,0) == 0) { //Tant que a % 2 = 0
			mpz_div_ui(tmpa,tmpa,2);
			mpz_mod_ui(tmp,tmpb,8);
			if ((mpz_cmp_ui(tmp,3) == 0 || mpz_cmp_ui(tmp,5) == 0)) //Si b % 8 = 3 ou b % 8 = 5
				t = -t;
			mpz_mod_ui(tmp,tmpa,2);
		}
		mpz_set(tmp,tmpa);
		mpz_set(tmpa,tmpb);
		mpz_set(tmpb,tmp);
		mpz_mod_ui(tmp,tmpa,4);
		mpz_mod_ui(tmp2,tmpb,4);
		if (mpz_cmp_ui(tmp,3) == 0 && mpz_cmp_ui(tmp2,3) == 0) //Si a % 4 = 3 et b % 4 = 3
			t = - t;
		mpz_mod(tmpa,tmpa,tmpb);
	}
	if (mpz_cmp_ui(tmpb,1) == 0){
		mpz_clears(tmp,tmp2,tmpa,tmpb,NULL);
		return t; //Si b = 1	
	} else {
		mpz_clears(tmp,tmp2,tmpa,tmpb,NULL);
		return 0;
	}
}

/*! \fn void critere_euler(mpz_t res,mpz_t random,mpz_t aTraiter)
 * 	\brief Fonction permettant de calculer le critère d'Euler
 * 	\param res : On renvoie le resultat.
 * 	\param random : random est un nombre aléatoire
 * 	\param aTraiter : aTraiter est le nombre à traiter
 */
void critere_euler(mpz_t res,mpz_t random,mpz_t aTraiter)
{
		mpz_t aTraiterMoins1,r,expo;
		mpz_inits(aTraiterMoins1,r,expo,NULL);
		
		mpz_sub_ui(aTraiterMoins1,aTraiter,1);
		
		mpz_cdiv_q_ui(expo,aTraiterMoins1,2);
		mpz_mod_ui(r, aTraiterMoins1, 2);
		mpz_sub(expo,expo,r);
		squareAndMultiply(res,random,expo,aTraiter);
		
		mpz_clears(aTraiterMoins1,r,expo,NULL);	
}

/*! \fn nombre_fermat(mpz_t res,mpz_t n)
 * 	\brief Fonction permettant de calculer un nombre de fermat
 * 	\param res : On renvoie le resultat.
 * 	\param n : n est le n-ieme nombre de fermat
 */
void nombre_fermat(mpz_t res,mpz_t n)
{
	mpz_t DeuxPowN,Deux,DeuxPowDeuxN;
	mpz_inits(DeuxPowN,DeuxPowDeuxN,Deux,NULL);
	
	mpz_set_ui(Deux,2);
	
	expoRapide(DeuxPowN,Deux,n);
	expoRapide(DeuxPowDeuxN,Deux,DeuxPowN);
	
	mpz_add_ui(res,DeuxPowDeuxN,1);
	
	mpz_clears(DeuxPowN,Deux,DeuxPowDeuxN,NULL);	
}

/*! \fn void calculSequence(mpz_t seq, mpz_t modul, mpz_t k)
 * 	\brief Fonction permettant de calculer la sequence de lucas
 * 	\param seq : On renvoie le resultat de la sequence.
 * 	\param modul : modul est le nombre de merssen 2^n - 1
 *	\param k : un nombre impaire
 */
void calculSequence(mpz_t seq, mpz_t modul, mpz_t k)
{
	// mpz_t tmp, i;
	// mpz_inits(tmp, i, NULL);
	// mpz_sub_ui(tmp, k, 2);
	// // gmp_printf("tmp = %Zd\n", tmp);
	// for (mpz_set_ui(i,1);mpz_cmp(i, tmp) <= 0;mpz_add_ui(i,i,1))
	// {
	// 	// printf("ici\n");
	// 	mpz_mul(seq, seq, seq);
	// 	mpz_sub_ui(seq, seq, 2);
	// 	mpz_mod(seq, seq, modul);
	// 	// gmp_printf("seq = %Zd\n", seq);
	// }
	// // gmp_printf("seq = %Zd\n", seq);
	// // gmp_printf("modul = %Zd\n", modul);
	// mpz_clears(tmp, i, NULL);
	mpz_t tmp, kk;
	mpz_inits(tmp, kk, NULL);
	mpz_set(kk, k);
	if(mpz_cmp_ui(kk,0)<=0)
	{
		mpz_set_ui(seq, 4);
		mpz_clears(tmp, kk, NULL);
		return;
	}
	else
	{
		mpz_sub_ui(kk, kk, 1);
		calculSequence(tmp, modul, kk);
		mpz_mul(seq, tmp, tmp);
		mpz_sub_ui(seq, seq, 2);
		mpz_mod(seq, seq, modul);
		// gmp_printf("seq = %Zd\n", seq);
		mpz_clears(tmp, kk, NULL);
		return;
	}


}

/*! \fn void mersen(mpz_t m, mpz_t n)
 * 	\brief Fonction permettant de calculer la sequence de lucas
 * 	\param m : On renvoie le resultat de calcul du nombre de mersen
 *	\param n : un nombre impaire (premier)
 */
void mersen(mpz_t m, mpz_t n)
{
	mpz_t deux;
	mpz_init(deux);
	mpz_set_ui(deux, 2);
	expoRapide(m, deux, n);
	mpz_sub_ui(m, m, 1);
	mpz_clear(deux);
	// gmp_printf("meren = %Zd\n", m);
}

/*! \fn void suiteFibo(mpz_t res, mpz_t n)
 * 	\brief Fonction permettant de calculer la suite de Fibonacci
 * 	\param res : On renvoie le resultat
 *	\param n : un nombre entier
 */
void suiteFibo(mpz_t res, mpz_t n)
{
	mpz_t nMoins1,nMoins2,rec,FiboMoins1,FiboMoins2;
	mpz_inits(nMoins1,nMoins2,rec,FiboMoins1,FiboMoins2,NULL);
	
	if(mpz_cmp_ui(n,1)<=0 && mpz_cmp_ui(n,0)>=0)
	{
		mpz_set(res,n);
		mpz_clears(nMoins1,nMoins2,rec,FiboMoins1,FiboMoins2,NULL);
	}
	
	else
	{
		mpz_sub_ui(nMoins1,n,1);
		mpz_sub_ui(nMoins2,n,2);
	
		suiteFibo(FiboMoins1,nMoins1);
		suiteFibo(FiboMoins2,nMoins2);
		
		mpz_add(rec,FiboMoins1,FiboMoins2);
		
		mpz_set(res,rec);
		
		mpz_clears(nMoins1,nMoins2,rec,FiboMoins1,FiboMoins2,NULL);
	}
}

/*! \fn void nombreLucas(mpz_t res, mpz_t n)
 * 	\brief Fonction permettant de calculer la suite de Lucas
 * 	\param res : On renvoie le resultat
 *	\param n : un nombre entier 
 */
void nombreLucas(mpz_t res, mpz_t n)
{
	mpz_t nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins2,nPlus2;
	mpz_inits(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins2,nPlus2,NULL);
	
	if(mpz_cmp_ui(n,0)==0)
	{
		mpz_add_ui(nPlus2,n,2);
		mpz_set(res,nPlus2);
		mpz_clears(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins2,nPlus2,NULL);
	}
	
	else if(mpz_cmp_ui(n,1)==0)
	{
		mpz_set(res,n);
		mpz_clears(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins2,nPlus2,NULL);
	}
	
	else
	{
		mpz_sub_ui(nMoins1,n,1);
		mpz_sub_ui(nMoins2,n,2);
	
		nombreLucas(nombreLucasMoins1,nMoins1);
		nombreLucas(nombreLucasMoins2,nMoins2);
	
		mpz_add(rec,nombreLucasMoins1,nombreLucasMoins2);
		
		mpz_set(res,rec);
		
		mpz_clears(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins2,nPlus2,NULL);
	}
}

/*! \fn void nombreOr(mpf_t res)
 * 	\brief Fonction permettant de calculer le nombre d'or
 * 	\param res : On renvoie le resultat
 */
void nombreOr(mpf_t res)
{
	mpf_t or,racineCinq,racineCinqPlusUn,Cinq;
	mpf_inits(or,racineCinq,racineCinqPlusUn,Cinq,NULL);
	
	mpf_set_ui(Cinq,5);
	
	mpf_sqrt(racineCinq,Cinq);
	
	mpf_add_ui(racineCinqPlusUn,racineCinq,1);
	
	mpf_div_ui(res,racineCinqPlusUn,2);
	
	mpf_clears(or,racineCinq,racineCinqPlusUn,Cinq,NULL);
}

/*! \fn void suiteFibo_or(mpz_t res, mpz_t n)
 * 	\brief Fonction permettant de calculer la suite de Fibonacci
 * 	\param res : On renvoie le resultat
 *	\param n : un nombre entier
 */
void suiteFibo_or(mpz_t res, mpz_t n)
{
	mpf_set_default_prec(PRECISION);
	mpf_t fi, fiPrim, fiPuisN, fiPrimPuisN, tmp, un, racineCinq, Cinq, fibTmp, resTmp;
	mpf_inits(fi, fiPrim, fiPuisN, fiPrimPuisN, tmp, un, racineCinq, Cinq, fibTmp, resTmp, NULL);
	
	mpf_set_ui(un, 1);
	mpf_set_ui(Cinq,5);
	mpf_sqrt(racineCinq,Cinq);
	mpz_t test;
	mpz_init(test);

	// initialisation
	nombreOr(fi);
	mpf_div(tmp, un, fi);
	mpf_neg(fiPrim, tmp);

	mpf_pow_ui(fiPuisN, fi, mpz_get_ui(n));
	mpf_pow_ui(fiPrim, fiPrim, mpz_get_ui(n));
	mpf_sub(fibTmp, fiPuisN, fiPrimPuisN);
	mpf_div(resTmp, fibTmp, racineCinq);
	mpf_trunc(tmp, resTmp);
	mpf_add_ui(tmp, tmp, arrondi(tmp, resTmp));
	mpz_set_f(res,tmp);
	mpf_clears(fi, fiPrim, fiPuisN, fiPrimPuisN, tmp, un, racineCinq, Cinq, fibTmp, resTmp, NULL);
	mpz_clear(test);

}

/*! \fn void suiteLucas_or(mpz_t res, mpz_t n)
 * 	\brief Fonction permettant de calculer la suite de Fibonacci
 * 	\param res : On renvoie le resultat
 *	\param n : un nombre entier
 */
void suiteLucas_or(mpz_t res, mpz_t a, mpz_t n)
{
	// printf("suis dans suiteLucas_or\n");
	if(mpz_cmp_ui(n, 0) == 0)
	{
		mpz_set_ui(res, 2);
		// gmp_printf("res = %Zd\n", res);
		return;
	}
	if(mpz_cmp_ui(n, 1) == 0)
	{
		mpz_set(res, a);
		// gmp_printf("res = %Zd\n", res);
		return;
	}
	mpf_set_default_prec(PRECISION);
	mpf_t fi, fiPrim, fiPuisN, fiPrimPuisN, tmp, un, racineCinq, Cinq, fibTmp, resTmp;
	mpf_inits(fi, fiPrim, fiPuisN, fiPrimPuisN, tmp, un, racineCinq, Cinq, fibTmp, resTmp, NULL);
	
	mpf_set_ui(un, 1);
	// mpf_set_ui(Cinq,5);
	// mpf_sqrt(racineCinq,Cinq);
	mpz_t test;
	mpz_init(test);

	// initialisation
	nombreOr(fi);
	mpf_div(tmp, un, fi);
	mpf_neg(fiPrim, tmp);

	mpf_pow_ui(fiPuisN, fi, mpz_get_ui(n));
	mpf_pow_ui(fiPrim, fiPrim, mpz_get_ui(n));
	mpf_add(fibTmp, fiPuisN, fiPrimPuisN);
	mpf_set(resTmp, fibTmp);
	// gmp_printf("fibTmp = %Ff\n", fibTmp);
	// mpf_sub(fibTmp, fiPuisN, fiPrimPuisN);
	// mpf_div(resTmp, fibTmp, racineCinq);
	// gmp_printf("luc = %Ff\n", fibTmp);
	mpf_trunc(tmp, resTmp);
	mpf_add_ui(tmp, tmp, arrondi(tmp, resTmp));
	mpz_set_f(res,tmp);
	mpf_clears(fi, fiPrim, fiPuisN, fiPrimPuisN, tmp, un, racineCinq, Cinq, fibTmp, resTmp, NULL);
	mpz_clear(test);

}

/*! \fn unsigned long int arrondi(mpf_t ent, mpf_t n)
 * 	\brief Fonction permettant de calculer la suite de Fibonacci
 * 	\param ent : On renvoie le resultat
 *	\param n : un nombre entier
 *	\return : 0 pour la partie entiere inférieur ou 1 pour la partie entiere superieur
 */
unsigned long int arrondi(mpf_t ent, mpf_t n)
{
	// gmp_printf("ent = %Zd\n", ent);
	mpf_t deci, tmpEnt;
	mpf_inits(deci, tmpEnt, NULL);
	// mpf_set_z(tmpEnt, ent);

	mpf_sub(deci, n, ent);

	if( mpf_cmp_d(deci, 0.5) >= 0)
	{
		mpf_clears(deci, tmpEnt, NULL);
		return 1;
	}

	mpf_clears(deci, tmpEnt, NULL);
	return 0;
}

/*! \fn void PolyFibo(mpz_t res,mpz_t a,mpz_t b,mpz_t n)
 * 	\brief Fonction permettant de calculer la suite de Fibonacci en Polynome
 * 	\param res : On renvoie le resultat
 * 	\param a : un nombre aléatoire a
 * 	\param b : un nombre aléatoire b
 *	\param n : un nombre entier
 */
void PolyFibo(mpz_t res,mpz_t a,mpz_t b,mpz_t n)
{
	mpz_t nMoins1,nMoins2,rec,FiboMoins1,FiboMoins1_a,FiboMoins2,FiboMoins2_b;
	mpz_inits(nMoins1,nMoins2,rec,FiboMoins1,FiboMoins1_a,FiboMoins2,FiboMoins2_b,NULL);
	
	if(mpz_cmp_ui(n,1)<=0)
	{
		mpz_set(res,n);
		mpz_clears(nMoins1,nMoins2,rec,FiboMoins1,FiboMoins1_a,FiboMoins2,FiboMoins2_b, NULL);
	}
	
	else
	{
		mpz_sub_ui(nMoins1,n,1);
		mpz_sub_ui(nMoins2,n,2);
	
		PolyFibo(FiboMoins1, a, b, nMoins1);
		mpz_mul(FiboMoins1_a,a,FiboMoins1);
		
		PolyFibo(FiboMoins2, a, b, nMoins2);
		mpz_mul(FiboMoins2_b,b,FiboMoins2);
		
		mpz_sub(rec,FiboMoins1_a,FiboMoins2_b);
		
		mpz_set(res,rec);
		
		mpz_clears(nMoins1,nMoins2,rec,FiboMoins1,FiboMoins1_a,FiboMoins2,FiboMoins2_b,NULL);
	}
}
/*! \fn calcul_discriminant(mpz_t res,mpz_t a,mpz_t b)
 * 	\brief Fonction permettant de calculer le discriminant
 * 	\param res : On renvoie le resultat
 * 	\param a : un nombre aléatoire a
 * 	\param b : un nombre aléatoire b
 */
void calcul_discriminant(mpz_t res,mpz_t a,mpz_t b)
{
	mpz_t carre_a,quatre,b4,disc;
	mpz_inits(carre_a,quatre,b4,disc,NULL);
	
	mpz_mul(carre_a,a,a);
	mpz_set_ui(quatre,4);
	mpz_mul_ui(b4,b,4);
	
	mpz_sub(disc,carre_a,b4);
	
	mpz_set(res,disc);
	
	mpz_clears(carre_a,quatre,b4,disc,NULL);
}

/*! \fn void PolyLucas(mpz_t res,mpz_t a,mpz_t b,mpz_t n)
 * 	\brief Fonction permettant de calculer la suite de Lucas en Polynome
 * 	\param res : On renvoie le resultat
 * 	\param a : un nombre aléatoire a
 * 	\param b : un nombre aléatoire b
 *	\param n : un nombre entier
 */
void PolyLucas(mpz_t res,mpz_t a,mpz_t b,mpz_t n)
{
	mpz_t nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins1_a,nombreLucasMoins2,nombreLucasMoins2_b,nPlus2;
	mpz_inits(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins1_a,nombreLucasMoins2,nombreLucasMoins2_b,nPlus2,NULL);
	
	if(mpz_cmp_ui(n,0)==0)
	{
		mpz_add_ui(nPlus2,n,2);
		mpz_set(res,nPlus2);
		mpz_clears(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins1_a,nombreLucasMoins2,nombreLucasMoins2_b,nPlus2,NULL);
	}
	
	else if(mpz_cmp_ui(n,1)==0)
	{
		mpz_set(res,a);
		mpz_clears(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins1_a,nombreLucasMoins2,nombreLucasMoins2_b,nPlus2,NULL);
	}
	
	else
	{
		mpz_sub_ui(nMoins1,n,1);
		mpz_sub_ui(nMoins2,n,2);
	
		// suiteLucas_or(nombreLucasMoins1,nMoins1);
		PolyLucas(nombreLucasMoins1, a, b, nMoins1);
		mpz_mul(nombreLucasMoins1_a,nombreLucasMoins1,a);
		
		// suiteLucas_or(nombreLucasMoins2,nMoins2);
		PolyLucas(nombreLucasMoins2, a, b, nMoins2);
		mpz_mul(nombreLucasMoins2_b,nombreLucasMoins2,b);
	
		mpz_sub(rec,nombreLucasMoins1_a,nombreLucasMoins2_b);
		
		mpz_set(res,rec);
		
		mpz_clears(nMoins1,nMoins2,rec,nombreLucasMoins1,nombreLucasMoins1_a,nombreLucasMoins2,nombreLucasMoins2_b,nPlus2,NULL);
	}
}

// Mieux PolyLucas
void PolyLucas_or(mpz_t res,mpz_t a,mpz_t b,mpz_t n)
{
	if(mpz_cmp_ui(n, 0) == 0)
	{
		mpz_set_ui(res, 2);
		return;
	}
	if(mpz_cmp_ui(n, 1) == 0)
	{
		mpz_set(res, a);
		return;
	}
	mpz_t resNmoins1, resNmoins2;
	mpz_inits(resNmoins1, resNmoins2, NULL);
	mpz_sub_ui(resNmoins1, n, 1);
	// gmp_printf("resNmoins1 = %Zd\n", resNmoins1);
	mpz_sub_ui(resNmoins2, n, 2);
	// gmp_printf("resNmoins2 = %Zd\n", resNmoins2);
	
	if(mpz_cmp_ui(n, 2) == 0)
	{
		
		


		suiteLucas_or(resNmoins1, a, resNmoins1);
		// gmp_printf("resNmoins1 = %Zd\n", resNmoins1);
		suiteLucas_or(resNmoins2, a, resNmoins2);
		// gmp_printf("resNmoins2 = %Zd\n", resNmoins2);
		mpz_mul(resNmoins1, resNmoins1, a);
		mpz_mul(resNmoins2, resNmoins2, b);
		mpz_sub(res, resNmoins1, resNmoins2);
		mpz_clears(resNmoins1, resNmoins2, NULL);
		return;
	}

	PolyLucas_or(resNmoins1, a, b, resNmoins1);
	PolyLucas_or(resNmoins2, a, b, resNmoins2);
	mpz_mul(resNmoins1, resNmoins1, a);
	mpz_mul(resNmoins2, resNmoins2, b);
	mpz_sub(res, resNmoins1, resNmoins2);
	mpz_clears(resNmoins1, resNmoins2, NULL);
	return;

}

// resultat pas bon
void PolyLucas_or2(mpz_t res, mpz_t v1, mpz_t v0, mpz_t a, mpz_t b, mpz_t n)
{
	if(mpz_cmp_ui(n, 0) == 0)
	{
		mpz_set_ui(res, 2);
		return;
	}
	if(mpz_cmp_ui(n, 1) == 0)
	{
		mpz_set(res, v1);
		return;
	}

	mpz_t Nmoins1, tmp;
	mpz_inits(Nmoins1, tmp, NULL);

	mpz_set(v0, v1);
	mpz_mul(v1, v1, a);
	mpz_mul(tmp, v0, b);
	mpz_sub(v1, v1, tmp);

	
	mpz_sub_ui(Nmoins1, n, 1);

	PolyLucas_or(res, v1, v0, Nmoins1);
	mpz_set(res, v1);
	mpz_clears(Nmoins1, tmp, NULL);
	return;
}

// Afaire
void PolyLucas_dinamyk(mpz_t res,mpz_t a,mpz_t b,mpz_t n)
{
	
}

// En cours !!!!!!!!!!!!!!

/*! \fn void chaineLucasBinaire(mpz_t u, mpz_t v, mpz_t V0, mpz_t V1, mpz_t n, mpz_t modul)
 * 	\brief Fonction permettant de calculer la chaine de Lucas
 * 	\param u : le terme u = Vn
 * 	\param v : le terme v = Vn+1
 * 	\param V0 : 1er valeur d'initialisation de la séquence
 * 	\param V1 : 2ème valeur d'initialisation de la séquence
 * 	\param n : entier positive
 * 	\param modul : entier positive servant pour le modulo
 */
void chaineLucasBinaire(mpz_t u, mpz_t v, mpz_t V0, mpz_t V1, mpz_t n, mpz_t modul)
{
	mpz_t resU, resV, Vj;
	mpz_inits(resU, resV, Vj,NULL);
	// x0 = 2;
	// x1 = A;
	// u = x0;
	mpz_set(u, V0);
	// v = x1;
	mpz_set(v, V1);
	int nbBit = 0;
	char* nEnBin = NULL;
	nEnBin = mpz_get_str(NULL, 2, n);
	nbBit = strlen(nEnBin);
	//printf("m_bin = %s\n", nEnBin);
	printf("taille m = %d\n", nbBit);
	for(int j = 0; j < nbBit; j++)
	{
		if(nEnBin[j] == '1')
		{
			// u = u rond v mod modul;
			rond(resU, u, v, V1, modul);
			mpz_set(u, resU);
			etoile(resV, v, V0, modul);
			mpz_set(v, resV);
			//gmp_printf("u = %Zd\n", u);
			//gmp_printf("v = %Zd\n", v);
			
		}
		else
		{
			// u = u * u;
			etoile(resU, u, V0, modul);
			// v = u rond v;
			rond(resV, u, v, V1, modul);
			mpz_set(u, resU);
			//gmp_printf("u = %Zd\n", u);
			mpz_set(v, resV);
			//gmp_printf("v = %Zd\n", v);
		}
	}
	free(nEnBin);
	mpz_clears(resU, resV, Vj, NULL);
}

void rond(mpz_t res, mpz_t u, mpz_t v, mpz_t V1, mpz_t modul)
{
	// V2j+1 = Vj Vj+1 - b^j
	mpz_mul(res, u, v);
	mpz_sub(res, res, V1);
	mpz_mod(res, res, modul);
}

void etoile(mpz_t res, mpz_t u, mpz_t V0, mpz_t modul)
{
	// V2j = Vj Vj - 2
	mpz_mul(res, u, u);
	mpz_sub(res, res, V0);
	mpz_mod(res, res, modul);
}
