#ifndef LISTE_H
#define LISTE_H

//#include <gmp.h>

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


//Genere un entier entre 0 et n
int alea(int n);

liste creer_liste();

int est_vide(liste l);

void affiche_liste(liste l);

liste libere_liste(liste l);

liste ajoute_elem_debut(liste l,int i);

liste ajoute_elem_fin(liste l, int i);

liste ajoute_elem_trie(liste l,int i);

liste generer_liste(liste l,int Nmax, int mode);

int compare_liste(liste l, liste ll);

int compte_elems(liste l);

//renvoi l'indice du premier element qui à la valeur val dans la liste
int recherche_elem(liste l, int i);

//supprime l'element d'indice i
liste supprime_elem(liste l, int i);
liste supprime_elem_debut(liste l);

//retourne l1.l2
liste concatener_listes(liste l1, liste l2);

liste entrelacer_tries(liste l1, liste l2);

liste tri_a_bulles(liste l);

liste renverse(liste l);

liste tri_fusion(liste l,int taille);

liste crible_era(int n);

liste_liste creer_liste_liste(int k);

liste_liste ajoute_elem_classement(liste_liste liste,int val,int k);

void affiche_liste_liste(liste_liste liste, int k);

liste_liste libere_liste_liste(liste_liste liste,int k);

#endif