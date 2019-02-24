#ifndef LISTEGMP_H
#define LISTEGMP_H

#include <gmp.h>

/*! \file      listegmp.h
 *  \brief     Fichier Header contenant les fonctions listegmp
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

 /*! \struct elemgmp listegmp.h
 *  \brief Structure elemgmp qui va permettre de stocker un element dans une liste
 */
struct elemgmp{
	mpz_t val;/*!< valeur de l'élément*/
	int primalite;/*!< primalité de l'élément*/
	struct elemgmp *suiv;/*!< élément suivant*/
};

typedef struct elemgmp* listegmp;/*!< typedef de la structure */

listegmp creer_listegmp();//Fonction qui créer une liste gmp
listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i,int p);//Fonction qui ajoute un element au debut dans la liste
int est_videgmp(listegmp l);//Fonction qui retourne si la liste est vide ou non
void affiche_listegmp(listegmp l);// Fonction qui affiche le contenu de la liste
listegmp libere_listegmp(listegmp l);// Fonction qui libere la liste

#endif

