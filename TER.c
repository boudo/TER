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
	
	 //~ int test, test1, test2,compteur=0;
  	//~ mpz_t m_test;
  	//~ mpz_inits(m_test,NULL);
 	//~ for (int i = 1; i < 10000; ++i)
  	//~ {
 		//~ mpz_set_ui(m_test,i);
 	
 		//~ test = Fermat(m_test,25);
 		//~ test1 = Miller_Rabin(m_test, 25);
 		//~ test2 = solovayStrassen(m_test, 25);
  		//~ printf("%d\n", i);
 		//~ printf("fermat = %d\n", test);
 		//~ printf("miller = %d\n", test1);
 		//~ printf("trassen  = %d\n", test2);
 		//~ if(test != test1 || test1 != test2 || test != test2){
 			//~ printf("merde!!!!!!!!!!!!!!!!!!!!\n");
 			//~ compteur++;
 			//~ return 0;
 		//~ }
 		
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

 	//~ gmp_printf("\n###################### generation nbr premier ######################\n\n");
 	//~ float temps;
    //~ clock_t t1, t2;
 	//~ t1 = clock();
	//~ mesureTempsFichier("mesureTemps/mesure.txt",10,1024);
	//~ t2 = clock();
	//~ temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    //~ printf("temp : %f\n", temps);
	

	// int moi,lui;
	// mpz_t a,b;
	// mpz_inits(a,b,NULL);
	// for(int i=1; i<100; i++){
	// 	for(int y=1; y<100; y++){
	// 		mpz_set_ui(a,i);
	// 		mpz_set_ui(b,y);
	// 		moi = jacobiSymbol2(a,b);
	// 		lui = mpz_jacobi(a,b);
	// 		gmp_printf("a : %Zd b : %Zd : : :: : :: ",a,b);
	// 		printf("moi : %d lui : %d\n", moi,lui);
	// 		if(moi != lui){
	// 			printf("petite pute !!!!!\n");
	// 		}
	// 	}
	// }
	// // mpz_set_ui(a,2586);
	// // mpz_set_ui(b,2900);
	// // i = jacobiSymbol(a,b);
	// // printf("i : %d\n", i);
	// mpz_clears(a,b,NULL);

	return 0;
}
