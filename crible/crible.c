#include "crible.h"

liste crible_era(int n)
{
	int i;
	liste l = creer_liste();
	for(i=n;i>1;i--)
	{	
		l = ajoute_elem_debut(l,i);
	}
	liste debut = l;
	liste parcours;
	liste tmp;
	while(l->suiv)
	{
		parcours = l;
		while(parcours->suiv)
		{
			if(!(parcours->suiv->val % l->val))//divisible par l->val
			{
				tmp = parcours->suiv;
				parcours->suiv = parcours->suiv->suiv;
				free(tmp);
			}
			parcours = parcours->suiv;
			if(parcours == NULL)break;
		}
		l = l->suiv;
	}
	return debut;
}

listegmp crible_era_gmp(mpz_t n)
{
	mpz_t i,x;
	mpz_inits(i,x,NULL);
	
	listegmp lg = creer_listegmp();
	
	
	for(mpz_set(i,n);mpz_cmp_ui(i,1)>0;mpz_sub_ui(i,i,1))
	{	
		lg = ajoute_elem_debutgmp(lg,i);
	}
	
	listegmp debut = lg;
	listegmp parcours;
	listegmp tmp;
	
	while(lg->suiv)
	{
		parcours = lg;
		while(parcours->suiv)
		{
			mpz_mod(x,parcours->suiv->val,lg->val);
			
			if(mpz_cmp_ui(x,0)!= 1)//divisible par l->val
			{
				tmp = parcours->suiv;
				parcours->suiv = parcours->suiv->suiv;
				free(tmp);
			}
			parcours = parcours->suiv;
			
			if(est_videgmp(parcours))
			{
				break;
			}
			
		}
		lg = lg->suiv;
	}
	
	mpz_clears(i,x,NULL);
	
	return debut;
}
