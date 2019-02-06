#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

#include "liste/liste.h"
#include "fermat/fermat.h"
#include "fonctions/fonctions.h"
#include "miller/miller.h"

int main()
{
	mpz_t pgcd_r,pgcd_a,pgcd_b,a,n,h;//Declaration r,pgcda,pgcdb
	mpz_inits(pgcd_r,pgcd_a,pgcd_b,a,n,h,NULL);//Init

	gmp_printf("\n###################### Test PGCD ######################\n\n");
	
	mpz_set_ui(pgcd_a,6);//Affectation
	mpz_set_ui(pgcd_b,4);
	
	pgcd_gmp(pgcd_r,pgcd_a,pgcd_b);
	
	gmp_printf("PGCD(%Zd,%Zd)=%Zd\n",pgcd_a,pgcd_b,pgcd_r);//Affichage
	
	
	
	gmp_printf("\n###################### Test SQUARE AND MULTIPLY ######################\n\n");
	
	mpz_t sm_r;
	mpz_inits(sm_r,NULL);
	
	mpz_set_ui(a,188);
	mpz_set_ui(n,527);
	mpz_set_ui(h,2);
	
	squareAndMultiply_gmp(sm_r,a,h,n);
	
	gmp_printf("SQUARE=%Zd mod %Zd\n\n",sm_r,n);
	
	gmp_printf("\n###################### Test FERMAT ######################\n\n");
	
	mpz_t f,e_a,e_exp;
	mpz_inits(f,e_a,e_exp,NULL);
	
	mpz_set_ui(e_a,2);
	mpz_set_ui(e_exp,521);
	
	expoRapide_gmp(f,e_a,e_exp);
	mpz_sub_ui(f,f,1);
	
	Fermat(f,5);
	
	gmp_printf("\n###################### Test Decomposition ######################\n\n");
	
	mpz_t d_a,d_r,d_exp;
	mpz_inits(d_a,d_r,d_exp,NULL);
	
	mpz_set_ui(d_r,561);
	gmp_printf("%Zd=",d_r);
	mpz_sub_ui(d_r,d_r,1);
	
	decomposition(d_r,d_exp,d_a);
	
	gmp_printf("%Zd-1=2^%Zd*%Zd\n",d_r,d_exp,d_a);
	
	mpz_clears(pgcd_r,d_a,d_r,d_exp,pgcd_a,pgcd_b,f,e_a,e_exp, sm_r,a,n,h,NULL);//Clears
	
	return 0;
}
