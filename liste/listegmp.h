#ifndef LISTEGMP_H
#define LISTEGMP_H

#include <gmp.h>

struct elemgmp{
	mpz_t val;
	struct elemgmp *suiv;
};

typedef struct elemgmp* listegmp;


struct elem_listegmp{
	listegmp l;
	struct elem_listegmp *suiv;
};

typedef struct elem_listegmp* liste_listegmp;

listegmp creer_listegmp();
int est_videgmp(listegmp l);
void affiche_listegmp(listegmp l);

#endif

