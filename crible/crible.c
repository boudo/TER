#include "crible.h"

/*! \file      crible.c
 *  \brief     Fichier contenant le crible d'erastotene
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

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

/*! \fn int Test_Era(mpz_t n)
 *  \brief Fonction Deterministe qui utilise le crible d'erastotene pour dire si un nombre est premier ou non
 *  \param n : entier n
 *  \return retourne 1 si premier ,0 si composé et -1 si erreur
 */
int Eratosthene(mpz_t n)
{
	//Si n < 2
	if (mpz_cmp_ui(n, 2) < 0)
	{
		return -1;
	}
	
	//Si n = 2
	if (mpz_cmp_ui(n, 2) == 0)
	{
		return 1;
	}

	mpz_t racine_n,resteDiv,nmoins1;
	mpz_inits(racine_n,resteDiv,nmoins1,NULL);

	//Liste des nombres premiers < à racine_n
	mpz_sqrt(racine_n,n);
	listegmp premier = creer_listegmp();
	
	if(mpz_cmp_ui(n,3)==0)//Cas pour 3
	{
		mpz_sub_ui(nmoins1,n,1);
		premier = crible_era_gmp(nmoins1);
	}
	else
	{
		premier = crible_era_gmp(racine_n); 
	}

	//On teste si chacun de ces nombres premiers / n
	listegmp tmp = premier;

	while (tmp->val != NULL)
	{
		if (tmp->primalite == 1)
		{
			mpz_mod(resteDiv,n,tmp->val);
			
			//Cas quand composé
			if (mpz_cmp_ui(resteDiv,0) == 0 ) 
			{
				mpz_clears(resteDiv, racine_n,nmoins1, NULL);
				libere_listegmp(premier);
				return 0;
			}
		}
		tmp = tmp->suiv;
	}
		
	//Cas quand 1er
	mpz_clears(resteDiv,racine_n,nmoins1,NULL);
	libere_listegmp(premier);
	return 1;
}
