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

void mesureTempsFichier(char *nomFichier,int nbrIteration) {
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "w");
 	float temps;
    clock_t t1, t2;
    mpz_t nbrPremier;
    mpz_inits(nbrPremier,NULL);
    if (fichier != NULL)
    {
    	fprintf(fichier,"  Fermat    Miller  Strassen   Erasto\n");
    	for(int i=1; i<=10; i++){
    		fprintf(fichier,"%d ", i);
    		if(i != 1){
    			generNbrPremier(nbrPremier,i,nbrIteration);
    		}else {
    			mpz_set_ui(nbrPremier,1);
    		}
	    	t1 = clock();
	    	Fermat(nbrPremier,nbrIteration);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	        fprintf(fichier,"%f ", temps);
	        if(i != 1){
	        	t1 = clock();
		    	Miller_Rabin(nbrPremier,nbrIteration);
		    	t2 = clock();
		    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	        }else {
	        	temps = 0.000000;
	        }
	        fprintf(fichier,"%f ", temps);
	        t1 = clock();
	    	solovayStrassen(nbrPremier,nbrIteration);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	        fprintf(fichier,"%f ", temps);
	        if(i != 1){
	        t1 = clock();
	    	crible_era_gmp(nbrPremier);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	    	}else {
	        	temps = 0.000000;
	        }
	        fprintf(fichier,"%f\n", temps);
    	}
    	
        fclose(fichier);
    }
    mpz_clears(nbrPremier,NULL);
}
