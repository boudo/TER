#include <stdio.h>
#include <stdlib.h>

#include "liste.h"



liste creer_liste(){return NULL;}

int est_vide(liste l)
{
	if(l == NULL)
		return 1;
	return 0;
}

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
liste ajoute_elem_debut(liste l,int i)
{
	liste new = malloc(sizeof(struct elem));
	new->val = i;
	new->suiv = l;
	return new;
}

liste ajoute_elem_fin(liste l, int i)
{
	liste new = malloc(sizeof(struct elem));
	new->val = i;
	new->suiv = NULL;
	if(est_vide(l))
	{
		return new;
	}
	liste debut = l;
	//on place le pointeur sur le dernier element de la liste
	while(l->suiv)
		l = l->suiv;
	l->suiv = new;
	return debut;
}

int compte_elems(liste l)
{
	if(est_vide(l))return 0;
	int compteur = 1;
	while(l->suiv)
	{
		compteur++;
		l = l->suiv;
	}
	return compteur;
}

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

int compare_liste(liste l, liste ll)
{
	if(l == NULL &&  ll == NULL)
	{
		return 1;
	}
	else if((l == NULL && ll != NULL) || (l != NULL && ll == NULL))
	{
		return 0;
	}
	else if(l->val != ll->val)
	{
		return 0;
	}
	else if(l->val == ll->val)
	{
		return compare_liste(l->suiv, ll->suiv);
	}
	
	return 0;
}
