#include "mesure.h"

/*! \file      mesure.c
 *  \brief     Fichier contenant les tests de mesures
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

/*! \fn int estPremier(mpz_t nombre,int nombreIteration)
 *  \brief Fonction qui permet de dire si un nombre est premier ou non
 *  \param nombre : nombre à tester
 *  \param nombreIteration : nombre d'iterations
 * 	\return retourne 1 si premier sinon 0
 */
int estPremier(mpz_t nombre,int nombreIteration) 
{
	if(Fermat(nombre,nombreIteration) && Miller_Rabin(nombre,nombreIteration) && solovayStrassen(nombre,nombreIteration))
	{
		return 1;
	}
	
	return 0;
}

/*! \fn void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration)
 *  \brief Fonction qui permet de generer un nombre premier
 *  \param resultat : nombre à tester
 *  \param nbrBit : nombrede bits
 *  \param nombreIteration : nombre d'iterations
 */
//fonction de generation d'un nombre prenier a n bits
void generNbrPremier(mpz_t resultat, int nbrBit,int nombreIteration) 
{
	mpz_t bornSup,bornInf,diff,exposant,exposer,alea;
	
	mpz_inits(bornSup,bornInf,diff,exposant,exposer,alea,NULL);
	
	mpz_set_ui(exposer,2);
	mpz_set_ui(exposant,nbrBit);
	
	expoRapide(bornSup,exposer,exposant);
	mpz_sub_ui(exposant,exposant,1);
	
	expoRapide(bornInf,exposer,exposant);
	mpz_sub(diff,bornSup,bornInf);
	mpz_add_ui(alea,bornInf,1);
	//gmp_printf("chiffre : %Zd\n",bornInf);
	do {
		mpz_add_ui(alea,alea,2);
		mpz_add(resultat,alea,bornInf);
	}while(!estPremier(resultat,nombreIteration));
	//gmp_printf("chiffre : %Zd\n",resultat);
	mpz_clears(bornSup,bornInf,diff,exposant,exposer,alea,NULL);
}

/*! \fn void mesureTempsFichier(char *nomFichier,int nbrIteration)
 *  \brief Fonction qui permet d'ecrire les mesures dans un fichier
 *  \param nomFichier : nom du Fichier où seront stockés les mesures
 *  \param nbrIteration : nombre d'iterations
 */

void mesureTempsFichier(char *nomFichier,int nbrIteration,int nbrBitMax) 
{
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "w");
	
 	float temps;
    clock_t t1, t2;
    
    mpz_t nbrPremier;
    mpz_inits(nbrPremier,NULL);
    
    if(fichier != NULL)
    {
    	//fprintf(fichier,"  Fermat    Miller  Strassen   Eratos\n");
    	fprintf(fichier,"  Fermat    Miller  Strassen Erastotene\n");
    	for(int i=1; i<=nbrBitMax; i++){
    		fprintf(fichier,"%d ", i);
    		
    		if(i != 1)
    		{
    			generNbrPremier(nbrPremier,i,nbrIteration);
    		}
    		
    		else 
    		{
    			mpz_set_ui(nbrPremier,1);
    		}
    		
    		//Fermat
	    	t1 = clock();
	    	Fermat(nbrPremier,nbrIteration);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	        fprintf(fichier,"%f ", temps);
	        
	        //Miller
	        if(i != 1)
	        {
	        	t1 = clock();
		    	Miller_Rabin(nbrPremier,nbrIteration);
		    	t2 = clock();
		    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	        }
	        
	        else 
	        {
	        	temps = 0.000000;
	        }
	        fprintf(fichier,"%f ", temps);
	        
	        //Solovay
	        t1 = clock();
	    	solovayStrassen(nbrPremier,nbrIteration);
	    	t2 = clock();
	    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	        fprintf(fichier,"%f ", temps);
	        
	        //Erastothene
	        if(i != 1)
	        {
				t1 = clock();
				Eratosthene(nbrPremier);
				t2 = clock();
				temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	    	}	
	    	else 
	    	{
	        	temps = 0.000000;
	        }
	         fprintf(fichier,"%f\n", temps);
	        
    	}
    	
        fclose(fichier);
    }
    mpz_clears(nbrPremier,NULL);
}
