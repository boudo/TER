#ifndef LISTE_H
#define LISTE_H


struct elem{
	int val;
	struct elem *suiv;
};

typedef struct elem* liste;


struct elem_liste{
	liste l;
	struct elem_liste *suiv;
};

typedef struct elem_liste* liste_liste;


liste creer_liste();

int est_vide(liste l);

void affiche_liste(liste l);

liste libere_liste(liste l);

liste ajoute_elem_debut(liste l,int i);

liste ajoute_elem_fin(liste l, int i);

int compte_elems(liste l);

liste supprime_elem_debut(liste l);

int compare_liste(liste l, liste ll);


#endif
