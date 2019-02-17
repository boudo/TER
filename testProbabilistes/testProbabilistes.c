#include "testProbabilistes.h"
// #include "../fonctions/fonctions.h"


// ************* Fermat ***************************
int Fermat(mpz_t n, int iter)
{
	printf("taille = %d\n", iter);
	mpz_t pgcd, sqm, alea, expo;
	gmp_randstate_t state;
	mpz_inits(pgcd, sqm, alea, expo, NULL);
	gmp_randinit_mt(state);
	mpz_sub_ui(expo, n, 1); // expo = n - 1
	for(int i=0; i<iter; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , n);
		if(mpz_cmp_ui(alea, 3) < 0)
		{
			mpz_add_ui(alea, alea, 3);
		}
		pgcd_gmp(pgcd, n, alea);
		if (mpz_cmp_ui(pgcd, 1) != 0)
		{
			gmp_printf("pgcd = %Zd et alea = %Zd donc %Zd est composé\n",pgcd,alea, n);
			mpz_clears(pgcd, sqm, alea, expo, NULL);
			gmp_randclear(state);
			return 0;
		}
		//mpz_sub_ui(expo, n, 1);printf("Fermat\n");
		// mpz_set(expo, n);
		// mpz_sub_ui(expo, n, 1);
		//printf("debut\n");
		squareAndMultiply_gmp(sqm, alea, expo, n);
		//printf("debut\n");
		//mpz_powm(sqm, alea, expo, n);
		//printf("Fermat\n");
		if(mpz_cmp_ui(pgcd, 1) == 0 && mpz_cmp_ui(sqm, 1) != 0)
		{
			gmp_printf("sqm = %Zd et alea = %Zd expo = %Zd donc  %Zd est composé pgcd = %Zd\n", sqm, alea, expo, n, pgcd);
			mpz_clears(pgcd, sqm, alea, expo, NULL);
			gmp_randclear(state);
			return 0;
		}
	}


	gmp_printf("sqm = %Zd et %Zd est 1er pgcd = %Zd et alea =  %Zd\n", sqm, n, pgcd, alea);
	mpz_clears(pgcd, sqm, alea, expo, NULL);
	gmp_randclear(state);
	return 1;
}

// ************* Miller ***************************
void Miller_Rabin(mpz_t n, int rep)
{
	mpz_t nMoins2, alea, temoin;
	mpz_inits(nMoins2, alea, temoin, NULL);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	mpz_sub_ui(nMoins2, n, 2); // n - 2

	for(int i=0; i<rep; i++)
	{
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , nMoins2);
		if(mpz_cmp_ui(alea, 2) < 0)
		{
			mpz_add_ui(alea, alea, 2);
		}
		temoinMiller(temoin, alea, n);
		if (mpz_cmp_ui(temoin, 0) > 0)
		{
			printf("ce nombre est composé\n");
			mpz_clears(nMoins2, alea, temoin, NULL);
			gmp_randclear(state);
			return ;
		}
	}
	printf("ce nombre est premier\n");
	mpz_clears(nMoins2, alea, temoin, NULL);
	gmp_randclear(state);
}


void temoinMiller(mpz_t res, mpz_t a, mpz_t n)
{
	mpz_t s, d, nMoins1, x;
	mpz_inits(s, d, nMoins1,x, NULL);

	mpz_sub_ui(nMoins1, n, 1);

	decomposition(nMoins1, s, d);

	squareAndMultiply_gmp(x, a, d, n);
	if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, nMoins1) == 0)
	{
		mpz_set_ui(res, 0);
		mpz_clears(s, d, nMoins1,x, NULL);
		return ;
	}
	while(mpz_cmp_ui(s, 1) > 0)
	{
		mpz_mul(x, x, x);
		mpz_mod(x, x, n);
		if(mpz_cmp(x, nMoins1) == 0)
		{
			mpz_set_ui(res, 0);
			mpz_clears(s, d, nMoins1,x, NULL);
			return ;
		}
		mpz_sub_ui(s, s, 1);
	}
	mpz_set_ui(res, 1);
	mpz_clears(s, d, nMoins1,x, NULL);
	return ;
}

void exponentiationModulaire (mpz_t resultat, mpz_t a, mpz_t k, mpz_t n) {
	mpz_t i,tmp,tmpa;
	mpz_inits(i,tmp,tmpa,NULL);
	mpz_set(tmpa,a);
	//parcours de boucle k = k/2
	for (mpz_set_ui(i,1); mpz_cmp_ui(k,0)>0; mpz_div_ui(k,k,2)) {
		mpz_mod_ui(tmp,k,2);
		// Si l'exposant k est different de 0
		if(mpz_cmp_ui(tmp,0) != 0){
			mpz_mul(i,i,tmpa);
			mpz_mod(i,i,n);
		}
		mpz_mul(tmpa,tmpa,tmpa);
		mpz_mod(tmpa,tmpa,n);
	}
	mpz_set(resultat,i);
	mpz_clears(i,tmp,tmpa,NULL);
}

/**
* Cette fonction permet de calculer le Symbole de jacobi (a/p) et de determiner si
* si p divise a ou pas ainsi que si a est un résidu quadratique modulo p ou non
* @param resultat : On renvoi le resultat.
* @param a : a est un résidu quadratique ou non de b
* @param b 
*/
void jacobiSymbol (mpz_t resultat, mpz_t a, mpz_t b) {
	mpz_t tmp,tmp2,i;
	mpz_inits(tmp,tmp2,i,NULL); // on initialise la liste de variable
	mpz_mod_ui(tmp,b,2); // tmp = b % 2
	//Si b % 2 est egale a 0 ou b = 0
	if ( mpz_cmp_ui(b,0) <= 0 || mpz_cmp_ui(tmp,0) == 0 )
		mpz_set_ui(resultat, 0);
	mpz_set_ui(i,1);
	if( mpz_cmp_ui(a,0) < 0 ) { //Si a < 0
		mpz_neg( a, a);
		mpz_mod_ui(tmp,b,4);
		if (( mpz_cmp_ui(tmp,3) == 0)) //si b % 4 = 3
			mpz_neg(i,i); // i =- i
	}
	while (mpz_cmp_ui(a,0) != 0) {
		mpz_mod_ui(tmp,a,2);
		while (mpz_cmp_ui(tmp,0) == 0) { //Tant que a % 2 = 0
			mpz_div_ui(a,a,2);
			mpz_mod_ui(tmp,b,8);
			if ((mpz_cmp_ui(tmp,3) == 0 || mpz_cmp_ui(tmp,5) == 0)) //Si b % 8 = 3 ou b % 8 = 5
				mpz_neg(i,i);
			mpz_mod_ui(tmp,a,2);
		}
		mpz_set(tmp,a);
		mpz_set(a,b);
		mpz_set(b,tmp);
		mpz_mod_ui(tmp,a,4);
		mpz_mod_ui(tmp2,b,4);
		if (mpz_cmp_ui(tmp,3) == 0 && mpz_cmp_ui(tmp2,3) == 0) //Si a % 4 = 3 et b % 4 = 3
			mpz_neg(i,i);
		mpz_mod(a,a,b);
	}
	if (mpz_cmp_ui(b,1) == 0){ mpz_set(resultat,i); } //Si b = 1
	else mpz_set_ui(resultat,0);
	mpz_clears(tmp,tmp2,i,NULL); // on libere la mémoire 
}

/**
* Cette fonction permet de calculer si un nombre est premier ou composé.
* @param aTraiter : le nombre que l'on désire traiter.
* @param iterations : le nombre d'iterations que l'on désire faire lors du teste.
* @return on return 1 s'il est premier ou bien 0 s'il est composé
*/
int solovayStrassen(mpz_t aTraiter, mpz_t iterations) {
	
	if (mpz_cmp_ui(aTraiter,2) < 0)
		return 0;
	
	mpz_t tmp;
	mpz_init(tmp);
	mpz_mod_ui(tmp,aTraiter,2);
	if (mpz_cmp_ui(tmp,0) == 0){ // SI aTraiter % 2 est egale a 0
		mpz_clear(tmp);
		return 0;
	}

	mpz_t i,randomNumber,resultatJ,exposant,resultatM,randomTmp,aTraiterTmp;
	mpz_inits(i,randomNumber,resultatJ,exposant,resultatM,randomTmp,aTraiterTmp,NULL);
	//on initialise tout les parametre pour avoir des nombres aleatoire
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state,time(NULL));

	mpz_sub_ui(exposant,aTraiter,1); //On fait exposant-1
	mpz_div_ui(exposant,exposant,2); // puis on fait (exposant-1)/2

	mpz_sub_ui(tmp, aTraiter, 2); // on soustrait 2 pour avoir l'ensemble de définition compris entre 2 et n-1 pour les nombre aléatoire

	for (mpz_set_ui(i,0); mpz_cmp(i,iterations) < 0; mpz_add_ui(i, i, 1)) {
		//on creer notre nombre aleatoire
		mpz_urandomm(randomNumber,state,tmp);
		mpz_add_ui(randomNumber, randomNumber, 2); // on reajoute le 2 qu'on a soustrait precedemment
		//On utilise des variable de copie
		mpz_set(aTraiterTmp,aTraiter);
		mpz_set(randomTmp,randomNumber);
		jacobiSymbol(resultatJ, randomTmp, aTraiterTmp);
		exponentiationModulaire(resultatM, randomNumber, exposant, aTraiterTmp);
		// Si jacobie donne 0 et que jacobi est different de l'exponentiation modulaire, alors on renvoi 0
		if(mpz_cmp_ui(resultatJ,0) == 0 && mpz_cmp(resultatJ,resultatM) != 0){

			mpz_clears(i,randomNumber,tmp,resultatJ,resultatM,randomTmp,aTraiterTmp,NULL);
			return 0;
		}
	}
	mpz_clears(i,randomNumber,tmp,resultatJ,resultatM,randomTmp,aTraiterTmp,NULL);
	return 1;
}