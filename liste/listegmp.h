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

listegmp creer_listegmp();//Fonction qui créer une liste gmp
listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i);//Fonction qui ajoute un element au debut dans la liste
int est_videgmp(listegmp l);//Fonction qui retourne si la liste est vide ou non
void affiche_listegmp(listegmp l);// Fonction qui affiche le contenu de la liste
listegmp libere_listegmp(listegmp l);// Fonction qui libere la liste

#endif

