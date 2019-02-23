#include "mesure.h"

int estPremier(mpz_t nombre,int nombreIteration) {
	if(Fermat(nombre,nombreIteration) && Miller_Rabin(nombre,nombreIteration) && solovayStrassen(nombre,nombreIteration)){
		return 1;
	}
	return 0;
}

//fonction de generation d'un nombre prenier a n bits
void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration) {
	mpz_t bornSup,bornInf,diff,exposant,exposer,alea;
	gmp_randstate_t state;
	mpz_inits(bornSup,bornInf,diff,exposant,exposer,alea,NULL);
	gmp_randinit_mt(state);
	mpz_set_ui(exposer,2);
	mpz_set_ui(exposant,nbrBit);
	expoRapide(bornSup,exposer,exposant);
	mpz_sub_ui(exposant,exposant,1);
	expoRapide(bornInf,exposer,exposant);
	mpz_sub(diff,bornSup,bornInf);
	
	do {
		gmp_randseed_ui(state, time(NULL));
		mpz_urandomm (alea , state , diff);
		mpz_add(resultat,alea,bornInf);
	}while(!estPremier(resultat,nombreIteration));
	
	mpz_clears(bornSup,bornInf,diff,exposant,exposer,alea,NULL);
}