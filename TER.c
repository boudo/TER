#include <time.h>
#include "mesureTemps/mesure.h"
#include "testPrimalites/testPrimalites.h"

/*! \file      TER.c
 *  \brief     Fichier contenant le programme principal
 *  \author    ROBIN JORAN
 *  \author    BOUDO IBRAHIM
 *  \author    SLIMANI AREZKI
 *  \version   1.00
 *  \date      24 fevrier 2019
 */

/*! \fn int main()
 *  \brief Fonction qui exécute le programme
 *  \return retourne 0 une fois terminé
 */
int main()
{
	
	 int test, test1, test2, iter, cont;
 	 mpz_t m_test;
 	 mpz_inits(m_test,NULL);
 	 iter = 100;
 	 cont = 0;
 	 for (int i = 0; i < 10; ++i)
 	 {
 		mpz_set_ui(m_test,i);
 	
 		test = Fermat(m_test,iter);
 		test1 = Miller_Rabin(m_test, iter);
 		test2 = solovayStrassen(m_test, iter);
 		printf("%d\n", i);
 		printf("fermat = %d\n", test);
 		printf("miller = %d\n", test1);
 		printf("trassen  = %d\n", test2);
 		if(test != test1 || test1 != test2 || test != test2)
 		{
 			printf("************************************\n");
 			cont++;
 		}
 		
 	}	printf("cont = %d\n", cont);

 	mpz_clears(m_test, NULL);


	// mpz_t resultatJ, randomNumber, aTraiter;
	// mpz_inits(resultatJ, randomNumber, aTraiter, NULL);
	// for (int i = 1; i < 10; ++i)
	// {
	// 	mpz_set_ui(randomNumber, i*3+5-1);
	// 	mpz_set_ui(aTraiter, (25*i) % 1000);
	// 	jacobiSymbol(resultatJ, randomNumber, aTraiter);
	// 	gmp_printf("randomNumber %Zd\n", randomNumber);
	// 	gmp_printf("aTraiter %Zd\n", aTraiter);
	// 	gmp_printf("resultatJ %Zd\n", resultatJ);
	// 	printf("*****************************************\n");
	// }
	// mpz_clears(resultatJ, randomNumber, aTraiter,NULL);
	

	// int n = 5;
	// mpz_t res;
	// mpz_inits(res,NULL);
	// gmp_randstate_t state;
	// gmp_randinit_mt(state);
	// for (int i = 0; i < 50; ++i)
	// {
	// 	// gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
	// 	// mpz_urandomb(res, state, n);
	// 	genereAlea(res, state, n);
	// 	gmp_printf("res = %Zd\n", res);
	// }
	// mpz_clears(res,NULL);
	// gmp_randclear(state);


	// gmp_printf("\n###################### generation nbr premier ######################\n\n");
	// float temps;
	// clock_t t1, t2;
	// t1 = clock();
	// mesureTempsFichier("mesureTemps/mesure.txt",25,10);
	// t2 = clock();
	// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	// printf("temp : %f\n", temps);

	return 0;
}
