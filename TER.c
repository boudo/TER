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
	printf("\n################################# test probabiliste ##################################\n\n");


	printf("\n###################### Fermat Miller Strassen ######################\n\n");
	int test, test1, test2, iter, cont;
 	mpz_t m_test;
 	mpz_inits(m_test,NULL);
 	iter = 30;
 	cont = 0;
 	printf("Pour %d iération on: (1: premier, 0: composé)\n\n", iter);
 	for (int i = 86265959; i < 86265964; ++i)
 	{
 		mpz_set_ui(m_test,i);
 	
 		test = Fermat(m_test,iter);
 		test1 = Miller_Rabin(m_test, iter);
 		test2 = solovayStrassen(m_test, iter);
 		printf("************************************\n");
 		printf("pour n = %d\n\n", i);
 		printf("fermat = %d\n", test);
 		printf("miller = %d\n", test1);
 		printf("trassen  = %d\n", test2);
 		if(test != test1 || test1 != test2 || test != test2)
 		{
 			printf("************************************\n");
 			cont++;
 			// break;
 		}
 		
 	}
 	printf("cont = %d\n", cont);
 	mpz_clears(m_test, NULL);

 	printf("\n######################################## LucasFrobenius  #####################################\n\n");
	mpz_t res_t, n_t, a_t, b_t, delta_t, abdelta, gcd,n,x, expo, racine,Test,alea;
	mpz_inits(res_t, n_t, a_t, b_t, delta_t, abdelta, gcd,n,x, expo,racine,Test,alea, NULL);
	mpz_set_ui(x, 2);
	mpz_set_ui(expo, 10);
	expoRapide(n, x, expo);
	gmp_randstate_t state;
	gmp_randinit_mt(state);

	do
	{
		gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));
		mpz_urandomm (alea , state , n);
		//mpz_set_ui(res_t, -1);
		// mpz_set_ui(n_t, 12);
		mpz_set(a_t, alea);
		gmp_printf("alea %Zd\n", a_t);
		mpz_set_ui(b_t, 1);
		calcul_discriminant(delta_t,a_t,b_t);
		mpz_sqrtrem(racine, Test, delta_t);
		gmp_printf("delta %Zd\n", delta_t);
		gmp_printf("racine %Zd\n", racine);
		gmp_printf("test %Zd\n", Test);
	}while(mpz_cmp_ui(Test, 0) == 0 && (mpz_cmp_ui(a_t, 0) == 0));

	mpz_mul(abdelta, a_t, b_t);
	mpz_mul(abdelta, abdelta, delta_t);
	mpz_mul_ui(abdelta, abdelta, 2);
	gmp_printf("abdelta = %Zd\n\n", abdelta);
	int nb = 0;
	for (int i = mpz_get_ui(abdelta)+2; i < mpz_get_ui(abdelta)+mpz_get_ui(abdelta); ++i)
	{
		mpz_set_ui(n_t, i);
		pgcd(gcd, n_t, abdelta);
		 if(mpz_cmp_ui(gcd, 1) == 0 && mpz_cmp(n_t, abdelta) > 0)
		 {
			printf("*****************************************\n");
			LucasFrobenius(res_t, n_t, a_t, b_t, delta_t);
			gmp_printf("LucasFrobenius(%Zd) = %Zd\n",n_t , res_t);
			printf("*****************************************\n\n");
			if(mpz_cmp_ui(res_t, 1) == 0)
			{
				nb++;
			}
			if(nb == 5)
			{
				break;
			}
		 }
		
	}
	mpz_clears(res_t, n_t, a_t, b_t, delta_t, abdelta, gcd,n,x, expo, racine,Test,alea, NULL);
	gmp_randclear(state);

	printf("\n############################################ test deterministes ########################################\n\n");



	printf("\n###################### test Eratosthene ######################\n\n");
	mpz_t era;
	int earaN = 0;
	mpz_init(era);
	for (int i = 5484186; i < 5484196; ++i)
	{
		mpz_set_ui(era,i);
		printf("*****************************************\n");
		earaN = Eratosthene(era);
		gmp_printf("Eratosthene(%Zd) = %d\n",era , earaN);
		printf("*****************************************\n\n");
	}
	mpz_clears(era, NULL);
		
	printf("\n###################### Pepin ######################\n\n");

	mpz_t pepin;
	mpz_init(pepin);
	int pepinN = 0;
	
	for (int i = 10; i < 16; ++i)
	{
		mpz_set_ui(pepin,i);
		printf("*****************************************\n");
		pepinN = Pepin(pepin);
		gmp_printf("Pepin(%Zd) = %d\n",pepin , pepinN);
		printf("*****************************************\n\n");
	}
	mpz_clears(pepin, NULL);

	printf("\n###################### LucasLehmer ######################\n\n");

	mpz_t lucas;
	int i = 0;
	mpz_init(lucas);
	int lucasN = 0;
	lucasN = Pepin(lucas);
	i = 521;
	mpz_set_ui(lucas,i);
	printf("*****************************************\n");
	lucasN = LucasLehmer(lucas);
	gmp_printf("LucasLehmer(%Zd) = %d\n",lucas , lucasN);
	printf("*****************************************\n\n");
	i = 3217;
	mpz_set_ui(lucas,i);
	printf("*****************************************\n");
	lucasN = LucasLehmer(lucas);
	gmp_printf("LucasLehmer(%Zd) = %d\n",lucas , lucasN);
	printf("*****************************************\n\n");

	i = 9941;
	mpz_set_ui(lucas,i);
	printf("*****************************************\n");
	lucasN = LucasLehmer(lucas);
	gmp_printf("LucasLehmer(%Zd) = %d\n",lucas , lucasN);
	printf("*****************************************\n\n");

	i = 9940;
	mpz_set_ui(lucas,i);
	printf("*****************************************\n");
	lucasN = LucasLehmer(lucas);
	gmp_printf("LucasLehmer(%Zd) = %d\n",lucas , lucasN);
	printf("*****************************************\n\n");

	i = 23209;
	mpz_set_ui(lucas,i);
	printf("*****************************************\n");
	lucasN = LucasLehmer(lucas);
	gmp_printf("LucasLehmer(%Zd) = %d\n",lucas , lucasN);
	printf("*****************************************\n\n");

	mpz_clears(lucas, NULL);


	printf("\n###################### LucasFrobenius_avecIteration ######################\n\n");

	mpz_t res_tt, n_ttt;
	mpz_inits(res_tt, n_ttt, NULL);
	mpz_set_ui(n_ttt, 31);
	int iterr = 20;
	int intervalAlea = 10;
	printf("Pour %d iterations avec un a (alea) <= %d\n",iterr, intervalAlea);
	printf("*****************************************\n");
	LucasFrobenius_avecIteration(res_tt, n_ttt, iterr, intervalAlea);
	printf("*****************************************\n\n");

	mpz_clears(res_tt, n_ttt, NULL);



//************************************************************************************************************************************************/

	// gmp_printf("\n###################### LUCAS ######################\n\n");LucasLehmer(mpz_t n);
	// int luca;
	// mpz_t n;
	// mpz_init(n);
	// mpz_set_ui(n, 521);
	// luca = Lucas(n);	
	// printf("lucas = %d\n", luca);
	// mpz_clears(n, NULL);

	// int era;
	// mpz_t n;
	// mpz_init(n);
	// mpz_set_ui(n, 31);
	// era = Eratosthene(n);
	// printf("era = %d\n", era);
	// mpz_clears(n, NULL);


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
 	
 	//~ gmp_printf("\n###################### Pepin ######################\n\n");
 	
 	//~ mpz_t a;
 	//~ int test3,i;
 	//~ mpz_inits(a,NULL);

	//~ for(i=1 ;i<=17;i++)
	//~ {
		//~ mpz_set_ui(a,i);
		
		//~ float temps;
    //~ clock_t t1, t2;
 	//~ t1 = clock();
	//~ test3=Pepin(a);
	//~ t2 = clock();
	//~ temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    //~ gmp_printf("F%Zd \n pepin=%d\n temp :%f\n",a, test3,temps);
	//~ gmp_printf("**********************\n");
	//~ }
 	
 	//~ mpz_clears(a,NULL);


	// mpz_t finalultatJ, randomNumber, aTraiter;
	// mpz_inits(finalultatJ, randomNumber, aTraiter, NULL);
	// for (int i = 1; i < 10; ++i)
	// {
	// 	mpz_set_ui(a,i);
	// 	test3=Pepin(a);
	// 	gmp_printf("pepin=%d\n",test3);
	// 	gmp_printf("**********************\n");
	// }
 	
 // 	mpz_clears(a,NULL);
	// gmp_printf("\n###################### Test binaire ######################\n\n");

	// char* valRetour = NULL;
	// mpz_t val;
	// mpz_init(val);
	// mpz_set_ui(val, 521);

	// valRetour = mpz_get_str(NULL, 2, val);

	// printf("valRetour = %s\n", valRetour);
	// free(valRetour);
	// mpz_clears(val, NULL);

	
	// gmp_printf("\n###################### Test Lucas ######################\n\n");
	// int i;
	// mpz_t n,lucas;
	// mpz_inits(n,lucas,NULL);
	
	// for(int i=3;i<=100;i+=2)
	//  {
	// 	mpz_set_ui(n,i);
	// 	//Test_Lucas(lucas,n);
	// 	Test_Fibo(lucas,n);
	// 	gmp_printf("TestLucas(%Zd) : %Zd\n",n,lucas);
	// }
	
	// mpz_clears(n,lucas,NULL);

	//~ gmp_printf("\n###################### Poly Lucas ######################\n\n");
	
	//~ mpz_t P,Q,n,poly, v1, v0;
	//~ mpz_inits(P,Q,n, v1, v0, poly,NULL);
	
	//~ mpz_set_ui(Q,1);
	//~ mpz_set_ui(n,11);
	//~ mpz_set_ui(poly,1);
	//~ mpz_neg(Q,Q);
	
	//~ // mpz_set_ui(n,10);
	//~ mpz_set_ui(P,3);
	
	//~ // for(mpz_set_ui(P,1);mpz_cmp_ui(P,1)<=0;mpz_add_ui(P,P,1))
	//~ // {
	//~ // 	gmp_printf("Suite de parametres P=%Zd et Q=%Zd\n\n",P,Q);
	//~ // 	for(mpz_set_ui(n,0);mpz_cmp_ui(n, 10)<=0;mpz_add_ui(n,n,1))
	//~ // 	{
			
			//~ // PolyLucas(poly,P,Q,n);
			//~ // gmp_printf("TestPoly(%Zd) : %Zd\n",n,poly);
			//~ PolyLucas_or(poly,P,Q,n);
			//~ gmp_printf("TPoly_or(%Zd) : %Zd\n",n,poly);
	//~ // 	}
	
	//~ // }
	//~ mpz_clears(P,Q,n, poly,NULL);
	// gmp_printf("\n###################### LucasFrobenius ######################\n\n");
	// mpz_t res_t, n_t, a_t, b_t, delta_t, abdelta, gcd;
	// mpz_inits(res_t, n_t, a_t, b_t, delta_t, abdelta, gcd, NULL);
	// //mpz_set_ui(res_t, -1);
	// // mpz_set_ui(n_t, 12);
	// mpz_set_ui(a_t, 3);
	// mpz_set_ui(b_t, 1);
	// calcul_discriminant(delta_t,a_t,b_t);

	// mpz_mul(abdelta, a_t, b_t);
	// mpz_mul(abdelta, abdelta, delta_t);
	// mpz_mul_ui(abdelta, abdelta, 2);
	// // gmp_printf("abdelta = %Zd\n\n", abdelta);
	// for (int i = 1; i < 100; i++)
	// {
	// 	mpz_set_ui(n_t, i);
	// 	pgcd(gcd, n_t, abdelta);
	// 	 if(mpz_cmp_ui(gcd, 1) == 0 && mpz_cmp(n_t, abdelta) > 0)
	// 	 {
	// 		gmp_printf("*****************************************\n");
	// 		LucasFrobenius(res_t, n_t, a_t, b_t, delta_t);
	// 		gmp_printf("LucasFrobenius(%Zd) = %Zd\n",n_t , res_t);
	// 		gmp_printf("*****************************************\n\n");
	// 	 }
	// 	 else
	// 	 {
	// 	 	gmp_printf("pgcd = %Zd\n", gcd);
	// 	 	gmp_printf("LucasFrobenius(%Zd) = indéfinit car pgcd != 1\n\n",n_t);
	// 	 }
		
	// }
	// mpz_clears(res_t, n_t, a_t, b_t, delta_t, abdelta, gcd, NULL);

	// gmp_printf("\n###################### lucas_or ######################\n\n");
	// mpz_t n_test, suite;
	// mpz_inits(n_test, suite,NULL);

	// for (int i = 0; i < 10000; ++i)
 // 	 {
 // 		mpz_set_ui(n_test,i);
 // 		// suiteFibo_or(suite,n_test);
 // 		// gmp_printf("suiteF(%Zd) : %Zd\n",n_test,suite);
	// 	suiteLucas_or(suite,n_test);
	// 	gmp_printf("suiteL(%Zd) : %Zd\n",n_test,suite);
 		
 // 	}
 // 	mpz_clears(n_test, suite,NULL);



	return 0;
}
