#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*! \file      fonctions.h
 *  \brief     Fichier contenant les différentes fonctions nécessaires au bon fonctionnement du programme
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

//LISTE

/*! \struct elem
 *  \brief Structure elem qui va permettre de stocker un element dans une liste
 */
struct elem{
	int val;/*!< valeur de l'élément*/
	struct elem *suiv;/*!< élément suivant*/
};

typedef struct elem* liste;/*!< typedef de la structure */

/*! \fn liste creer_liste()
 *  \brief Fonction qui créer une liste vide
 *  \return retourne la liste vide
 */
liste creer_liste();

/*! \fn int est_vide(liste l)
 *  \brief Fonction qui permet de savoir si une liste est vide ou non
 *  \param l : liste l
 *  \return retourne 1 si la liste est vide ,sinon 0
 */
int est_vide(liste l);

/*! \fn void affiche_liste(liste l)
 *  \brief Fonction qui permet d'afficher le contenu de la liste
 *  \param l : liste l
 */
void affiche_liste(liste l);

/*! \fn liste libere_liste(liste l)
 *  \brief Fonction qui permet de liberer la liste
 *  \param l : liste l
 *  \return retourne NULL quand la liste est vide
 */
liste libere_liste(liste l);

/*! \fn liste ajoute_elem_debut(liste l,int i);
 *  \brief Fonction qui ajoute au début un élément dans la liste
 *  \param l : liste l
 *  \param i : valeur i à ajouter
 *  \return retourne la liste avec l'élément ajouté
 */
liste ajoute_elem_debut(liste l,int i);

/*! \fn liste supprime_elem_debut(liste l)
 *  \brief Fonction qui supprime au début un élément dans la liste
 *  \param l : liste l
 *  \return retourne la liste moins l'élément qu'on a supprimé
 */
liste supprime_elem_debut(liste l);

/*! \fn liste getBinaire(const mpz_t expo)
 *  \brief Fonction qui calcule l'exposant en binaire
 *  \param expo : exposant
 *  \return retourne la liste contenant le nombre en binaire
 */
liste getBinaire(const mpz_t expo);

//LISTE GMP

/*! \struct elemgmp
 *  \brief Structure elemgmp qui va permettre de stocker un element dans une liste
 */
struct elemgmp{
	mpz_t val;/*!< valeur de l'élément*/
	int primalite;/*!< primalité de l'élément*/
	struct elemgmp *suiv;/*!< élément suivant*/
};

typedef struct elemgmp* listegmp;/*!< typedef de la structure */

/*! \fn listegmp creer_listegmp()
 *  \brief Fonction qui créer une liste vide
 *  \return retourne la liste vide
 */
listegmp creer_listegmp();

/*! \fn listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i,int p)
 *  \brief Fonction qui ajoute au début un élément dans la liste
 *  \param l : liste l
 *  \param i : valeur i à ajouter
 *  \param p : entier p représenant la primalité
 *  \return retourne la liste avec l'élément ajouté
 */
listegmp ajoute_elem_debutgmp(listegmp l,mpz_t i,int p);

/*! \fn int est_videgmp(listegmp l)
 *  \brief Fonction qui permet de savoir si une liste est vide ou non
 *  \param l : liste l
 *  \return retourne 1 si la liste est vide ,sinon 0
 */
int est_videgmp(listegmp l);

/*! \fn void affiche_listegmp(listegmp l)
 *  \brief Fonction qui permet d'afficher le contenu de la liste
 *  \param l : liste l
 */
void affiche_listegmp(listegmp l);

/*! \fn listegmp libere_listegmp(listegmp l)
 *  \brief Fonction qui permet de liberer la liste
 *  \param l : liste l
 *  \return retourne NULL quand la liste est vide
 */
listegmp libere_listegmp(listegmp l);

/*! \fn listegmp crible_era_gmp(mpz_t n)
 *  \brief Fonction qui renvoie les nombres composés et premiers jusqu'à n
 *  \param n : entier n
 *  \return retourne la liste contenant les nombres composés et premiers de 2 jusqu'à n
 */
listegmp crible_era_gmp(mpz_t n);


//FONCTIONS

/*! \fn void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b) 
 *  \brief Fonction qui calcule le pgcd entre a et b
 *  \param resultat : resultat
 *  \param a : nombre a
 *  \param b : nombre b
 */
void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b);

/*! \fn void expoRapide(mpz_t resultat, const mpz_t x, const mpz_t expo)
 *  \brief Fonction qui calcule l'exponention rapide
 *  \param resultat : resultat
 *  \param x : entier x
 *  \param expo : exposant
 */
void expoRapide(mpz_t resultat, const mpz_t x, const mpz_t expo);

/*! \fn void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul)
 *  \brief Fonction qui calcule le square and multiply
 *  \param resultat : resultat
 *  \param x : entier x
 *  \param expo : exposant
 *  \param modul : modulo
 */
void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul);

/*! \fn void decomposition(mpz_t s,mpz_t d,mpz_t nMoins1)
 *  \brief Fonction qui decompose un entier x en 2^s * d
 *  \param s : entier s
 *  \param d : exposant d
 *  \param nMoins1 : entier nMoins1
 */
void decomposition(mpz_t s,mpz_t d, mpz_t nMoins1);

/*! \fn void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n)
 * 	\brief Fonction permettant de generer un nombre aléatoire
 * 	\param alea : nombre aléatoire
 * 	\param state : etat pour modifier le random 
 * 	\param n : nombre de bits
 */
void genereAlea(mpz_t alea, gmp_randstate_t state, mp_bitcnt_t n);

/*! \fn void temoinMiller(mpz_t res, mpz_t a, mpz_t n)
 * 	\brief Fonction permettant de trouver les temoins de Miller
 * 	\param res : On renvoie le resultat.
 * 	\param a : a est le futur temoin de miller(ou non)
 * 	\param n : n est le nombre à tester
 */
void temoinMiller(mpz_t res, mpz_t a, mpz_t n);

/*! \fn int jacobiSymbol(mpz_t a, mpz_t b)
 * 	\brief Fonction permettant de calculer le Symbole de jacobi (a/p) et de determiner si p divise a ou pas puis si a est un résidu quadratique modulo p ou non
 * 	\param a : a est un résidu quadratique ou non de b
 * 	\param b : b est un residu quadratique ou non de a ?
 */
int jacobiSymbol(mpz_t a, mpz_t b);

/*! \fn void critere_euler(mpz_t res,mpz_t random,mpz_t aTraiter)
 * 	\brief Fonction permettant de calculer le critère d'Euler
 * 	\param res : On renvoie le resultat.
 * 	\param random : random est un nombre aléatoire
 * 	\param aTraiter : aTraiter est le nombre à traiter
 */
void critere_euler(mpz_t res,mpz_t random,mpz_t aTraiter);

/*! \fn nombre_fermat(mpz_t res,mpz_t n)
 * 	\brief Fonction permettant de calculer un nombre de fermat
 * 	\param res : On renvoie le resultat.
 * 	\param n : n est le n-ieme nombre de fermat
 */
void nombre_fermat(mpz_t res,mpz_t n);

/*! \fn void calculSequence(mpz_t seq, mpz_t modul, mpz_t k)
 * 	\brief Fonction permettant de calculer la sequence de lucas
 * 	\param seq : On renvoie le resultat de la sequence.
 * 	\param modul : modul est le nombre de merssen 2^n - 1
 *	\param k : un nombre impaire
 */
void calculSequence(mpz_t seq, mpz_t modul, mpz_t k);

/*! \fn void mersen(mpz_t m, mpz_t n)
 * 	\brief Fonction permettant de calculer la sequence de lucas
 * 	\param m : On renvoie le resultat de calcul du nombre de mersen
 *	\param n : un nombre impaire (premier)
 */
void mersen(mpz_t m, mpz_t n);

/*! \fn suiteFibo(mpz_t res, mpz_t n);
 * 	\brief Fonction permettant de calculer la suite de Fibonacci
 * 	\param res : On renvoie le resultat
 *	\param n : un nombre entier
 */
void suiteFibo(mpz_t res, mpz_t n);

/*! \fn suiteLucas(mpz_t rez, mpz_t n);
 * 	\brief Fonction permettant de calculer la suite de Lucas
 * 	\param res : On renvoie le resultat
 *	\param n : un nombre entier 
 */
void nombreLucas(mpz_t res, mpz_t n);

#endif
