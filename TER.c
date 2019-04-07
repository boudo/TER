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
	//  int test, test1, test2, iter, cont;
 // 	 mpz_t m_test;
 // 	 mpz_inits(m_test,NULL);
 // 	 iter = 30;
 // 	 cont = 0;
 // 	 for (int i = 0; i < 100000; ++i)
 // 	 {
 // 		mpz_set_ui(m_test,i);
 	
 // 		test = Fermat(m_test,iter);
 // 		test1 = Miller_Rabin(m_test, iter);
 // 		test2 = solovayStrassen(m_test, iter);
 // 		printf("%d\n", i);
 // 		printf("fermat = %d\n", test);
 // 		printf("miller = %d\n", test1);
 // 		printf("trassen  = %d\n", test2);
 // 		if(test != test1 || test1 != test2 || test != test2)
 // 		{
 // 			printf("************************************\n");
 // 			cont++;
 // 			// break;
 // 		}
 		
 // 	}
 // 	printf("cont = %d\n", cont);
 // 	mpz_clears(m_test, NULL);

	// gmp_printf("\n###################### LUCAS ######################\n\n");
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

	// gmp_printf("\n###################### generation nbr premier ######################\n\n");
	// float temps;
	// clock_t t1, t2;
	// t1 = clock();
	// mesureTempsFichier("mesureTemps/mesure.txt",25,11);
	// t2 = clock();
	// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	// printf("temp : %f\n", temps);
	
	// mesureTempsPepin("mesureTemps/pepin.txt",10);

	// mesureTempsLucas("mesureTemps/lucas.txt",521);
	
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

	gmp_printf("\n###################### Test chaine de Lucas ######################\n\n");
	mpz_t nn, u, v, x0, x1, A, a, b;
	mpz_inits(nn, u, v, x0, x1, A, a, b, NULL);
	mpz_set_ui(nn, 10);
	mpz_set_ui(u, 1);
	mpz_set_ui(v, 1);
	mpz_set_ui(x0, 2);
	mpz_set_ui(a, 5);
	mpz_set_ui(b, 3);

	mpz_invert(A, b , nn);
	mpz_mul(a, a, a);
	mpz_mod(a, a, nn);
	mpz_mul(A, A, a);
	mpz_mod(A, A, nn);
	mpz_sub_ui(A, A, 2);
	mpz_mod(A, A, nn);
	mpz_set(x1, A);

	chaineLucas(nn, u, v, x0, x1);
	gmp_printf("x0 = %Zd\n", x0);
	gmp_printf("x1 = %Zd\n", x1);
	gmp_printf("u = %Zd\n", u);
	gmp_printf("v = %Zd\n", v);


	mpz_clears(nn, u, v, x0, x1, A, a, b, NULL);

	gmp_printf("\n###################### Poly Lucas ######################\n\n");
	
	mpz_t P,Q,n,poly, v1, v0;
	mpz_inits(P,Q,n, v1, v0, a, b, poly,NULL);
	
	mpz_set_ui(Q,1);
	mpz_set_ui(n,3);
	mpz_set_ui(poly,1);
	mpz_neg(Q,Q);
	
	// mpz_set_ui(n,10);
	mpz_set_ui(P,2);
	
	for(mpz_set_ui(P,1);mpz_cmp_ui(P,1)<=0;mpz_add_ui(P,P,1))
	{
		mpz_set(a,P);
		mpz_set(b,Q);
		mpz_set(v1,a);
		mpz_set_ui(v0,2);
		gmp_printf("Suite de parametres P=%Zd et Q=%Zd\n\n",P,Q);
		for(mpz_set_ui(n,0);mpz_cmp_ui(n, 40)<=0;mpz_add_ui(n,n,1))
		{
			
			// PolyLucas(poly,P,Q,n);
			// gmp_printf("TestPoly(%Zd) : %Zd\n",n,poly);
			PolyLucas_or(poly,P,Q,n);
			gmp_printf("TPoly_or(%Zd) : %Zd\n",n,poly);
		}
	
	}
	mpz_clears(P,Q,n, v1, v0, a, b, poly,NULL);

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
