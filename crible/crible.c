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
