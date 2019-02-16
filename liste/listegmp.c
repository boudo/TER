#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listegmp.h"

listegmp creer_listegmp()
{
	return NULL;
}

listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i)
{
	listegmp new = malloc(sizeof(struct elemgmp));
	
	mpz_init(new->val);
	mpz_set(new->val,i);
	
	new->suiv = l;
	
	return new;
}

int est_videgmp(listegmp l)
{
	if(l == NULL)
		return 1;
	return 0;
}

void affiche_listegmp(listegmp l)
{
	
	if(est_videgmp(l))
	{
		gmp_printf("La liste est vide \n");
		return;
	}
	while(l)
	{
		gmp_printf("%Zd ",l->val);
		l = l->suiv;
	}
	gmp_printf("\n");
}

listegmp libere_listegmp(listegmp l)
{
	listegmp tmp;
	
	while(l)
	{
		tmp = l->suiv;
		//printf("libération de %d\n",l->val);
		mpz_clears(l->val,NULL);
		free(l);
		l = tmp;
	}
	return NULL;
}
