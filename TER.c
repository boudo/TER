#include <time.h>
#include "mesureTemps/mesure.h"
#include "testPrimalites/testProbabilistes/testProbabilistes.h"
#include "testPrimalites/testDeterministes/testDeterministes.h"

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
	// gmp_printf("\n###################### test probabiliste ######################\n\n");
	 // int test, test1, test2, iter, cont;
 	//  mpz_t m_test;
 	//  mpz_inits(m_test,NULL);
 	//  iter = 30;
 	//  cont = 0;
 	//  for (int i = 0; i < 10000000; ++i)
 	//  {
 	// 	mpz_set_ui(m_test,i);
 	
 	// 	test = Fermat(m_test,iter);
 	// 	test1 = Miller_Rabin(m_test, iter);
 	// 	test2 = solovayStrassen(m_test, iter);
 	// 	printf("%d\n", i);
 	// 	printf("fermat = %d\n", test);
 	// 	printf("miller = %d\n", test1);
 	// 	printf("trassen  = %d\n", test2);
 	// 	if(test != test1 || test1 != test2 || test != test2)
 	// 	{
 	// 		printf("************************************\n");
 	// 		cont++;
 	// 		break;
 	// 	}
 		
 	// }	printf("cont = %d\n", cont);
 	// 	mpz_clears(m_test, NULL);
	gmp_printf("\n###################### LUCAS ######################\n\n");
	int luca;
	mpz_t n;
	mpz_init(n);
	mpz_set_ui(n, 23209);
	luca = Lucas(n);
	printf("lucas = %d\n", luca);


 	// gmp_printf("\n###################### Nombre De Fermat ######################\n\n");
 	
 	// mpz_t nbr_fermat,sept;
 	// mpz_inits(nbr_fermat,sept,NULL);

 	// mpz_set_ui(sept,3);
 	
 	
 	// nombre_fermat(nbr_fermat,sept);
 	
 	// gmp_printf("F%Zd=%Zd\n",sept,nbr_fermat);
 	
 	// mpz_clears(nbr_fermat,sept,NULL);
 	//~ }	
 	//~ printf("compteur : %d\n", compteur);
 	//~ mpz_clears(m_test, NULL);
 	
 	//~ gmp_printf("\n###################### Nombre De Fermat ######################\n\n");
 	
 	//~ mpz_t nbr_fermat,b;
 	//~ mpz_inits(nbr_fermat,b,NULL);

 	//~ mpz_set_ui(b,3);
 	
 	
 	//~ nombre_fermat(nbr_fermat,b);
 	
 	//~ gmp_printf("F%Zd=%Zd\n",b,nbr_fermat);
 	
 	//~ mpz_clears(nbr_fermat,b,NULL);
 	
 	gmp_printf("\n###################### Pepin ######################\n\n");
 	
 	mpz_t a;
 	int test3,i;
 	mpz_inits(a,NULL);

	for(i=1 ;i<=17;i++)
	{
		mpz_set_ui(a,i);
		
		float temps;
    clock_t t1, t2;
 	t1 = clock();
	test3=Pepin(a);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    gmp_printf("F%Zd \n pepin=%d\n temp :%f\n",a, test3,temps);
	gmp_printf("**********************\n");
	}
 	
 	mpz_clears(a,NULL);


	// mpz_t resultatJ, randomNumber, aTraiter;
	// mpz_inits(resultatJ, randomNumber, aTraiter, NULL);
	// for (int i = 1; i < 10; ++i)
	// {
	// 	mpz_set_ui(a,i);
	// 	test3=Pepin(a);
	// 	gmp_printf("pepin=%d\n",test3);
	// 	gmp_printf("**********************\n");
	// }
 	
 // 	mpz_clears(a,NULL);


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
