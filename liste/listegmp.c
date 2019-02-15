#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listegmp.h"

listegmp creer_listegmp()
{
	return NULL;
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
