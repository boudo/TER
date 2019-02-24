// #include <stdio.h>
// #include <stdlib.h>
// #include <gmp.h>
#include <time.h>

// #include "liste/liste.h"
// #include "fermat/fermat.h"
// #include "fonctions/fonctions.h"
// #include "miller/miller.h"
#include "mesureTemps/mesure.h"
#include "crible/crible.h"
#include "testProbabilistes/testProbabilistes.h"
#include "liste/listegmp.h"

/*! \file      tests_prim.c
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
	
	// int test, test1, test2;
 // 	mpz_t m_test;
 // 	mpz_inits(m_test,NULL);
 // 	for (int i = 1; i < 100; ++i)
 // 	{
 // 		mpz_set_ui(m_test,i);
 	
 // 		test = Fermat(m_test,25);
 // 		test1 = Miller_Rabin(m_test, 25);
 // 		// test2 = solovayStrassen(m_test, 25);
 // 		printf("%d\n", i);
 // 		printf("fermat = %d\n", test);
 // 		printf("miller = %d\n", test1);
 // 		// printf("trassen  = %d\n", test2);
 		
 // 	}	
 // 	mpz_set_ui(m_test,2147483647);
 // 	test = Fermat(m_test,25);
 // 	test1 = Miller_Rabin(m_test, 25);
 // 	// test2 = solovayStrassen(m_test, 25);
 // 	printf("%d\n", 2147483647);
 // 	printf("fermat = %d\n", test);
 // 	printf("miller = %d\n", test1);
 // 	// printf("trassen  = %d\n", test2);
 // 	mpz_clears(m_test, NULL);

	// mpz_t resultat, a, b;
	// mpz_inits(resultat, a, b,NULL);
	// mpz_set_ui(resultat, 10);
	// mpz_set_ui(a, 541);
	// mpz_set_ui(b, 2011);
	// jacobiSymbol(resultat, a, b); // 3 blocs perdus a chaque lancement (plus memoire dans le future)
	// gmp_printf("jaco = %Zd", resultat);
	// mpz_clears(resultat, a, b);

	int n = 5;
	mpz_t res;
	mpz_inits(res,NULL);
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	for (int i = 0; i < 50; ++i)
	{
		// gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
		// mpz_urandomb(res, state, n);
		genereAlea(res, state, n);
		gmp_printf("res = %Zd\n", res);
	}
	mpz_clears(res,NULL);
	gmp_randclear(state);


 	gmp_printf("\n###################### generation nbr premier ######################\n\n");
 	float temps;
    clock_t t1, t2;
 	t1 = clock();
	mesureTempsFichier("mesureTemps/mesure.txt",10,1024);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temp : %f\n", temps);


	return 0;
}
