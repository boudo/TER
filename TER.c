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
 	 iter = 30;
 	 cont = 0;
 	 for (int i = 0; i < 10000000; ++i)
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
 			break;
 		}
 		
 	}	printf("cont = %d\n", cont);
 		mpz_clears(m_test, NULL);



 	// gmp_printf("\n###################### Nombre De Fermat ######################\n\n");
 	
 	// mpz_t nbr_fermat,sept;
 	// mpz_inits(nbr_fermat,sept,NULL);

 	// mpz_set_ui(sept,3);
 	
 	
 	// nombre_fermat(nbr_fermat,sept);
 	
 	// gmp_printf("F%Zd=%Zd\n",sept,nbr_fermat);
 	
 	// mpz_clears(nbr_fermat,sept,NULL);


	// gmp_printf("\n###################### generation nbr premier ######################\n\n");
	// float temps;
	// clock_t t1, t2;
	// t1 = clock();
	// mesureTempsFichier("mesureTemps/mesure.txt",25,10);
	// t2 = clock();
	// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	// printf("temp : %f\n", temps);

 	// gmp_printf("\n###################### generation nbr premier ######################\n\n");
 	// float temps;
 	// clock_t t1, t2;
 	// t1 = clock();
 	// mesureTempsFichier("mesureTemps/mesure.txt",20,1024);
 	// t2 = clock();
 	// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
 	// printf("temp : %f\n", temps);
	

	return 0;
}
