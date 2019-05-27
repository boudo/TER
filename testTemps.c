#include <time.h>
#include "mesureTemps/mesure.h"
#include "testPrimalites/testProbabilistes/testProbabilistes.h"
#include "testPrimalites/testDeterministes/testDeterministes.h"

int main() {

	gmp_printf("\n###################### generation nbr premier ######################\n\n");
	float temps;
	clock_t t1, t2;
	t1 = clock();
	mesureTempsFichier("mesureTemps/mesure.txt",3,1024);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temp : %f\n", temps);
	
	mesureTempsPepin("mesureTemps/pepin.txt",15);

	mesureTempsLucas("mesureTemps/lucas.txt",1024);

	return 0;
}