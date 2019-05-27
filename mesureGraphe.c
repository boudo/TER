#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gnuplot_i/src/gnuplot_i.h"


void grapheProbabiliste(){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal pdfcairo size 10.5,7.86 ");
    gnuplot_cmd(g, "set output \"mesureTemps/Probabiliste.pdf\"");
    gnuplot_cmd(g, "set xlabel 'Nombre de bits'");
    gnuplot_cmd(g, "set ylabel 'temps(seconde)'");
    //gnuplot_cmd(g, "set yrange [0:0.009]");
    gnuplot_cmd(g, "plot \"mesureTemps/mesure.txt\" u 1:2 every 2 title 'fermat' with lines , \"mesureTemps/mesure.txt\" u 1:3 every 4 title 'miller' with lines, \"mesureTemps/mesure.txt\" u 1:4 every 2 title 'strassen' with lines, \"mesureTemps/mesure.txt\" u 1:5 every 2 title 'Lucas Frobinius' with lines");
    gnuplot_close(g);
}

void grapheRapportProbabiliste(){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal pdfcairo size 10.5,7.86 ");
    gnuplot_cmd(g, "set output \"mesureTemps/RapportProbabiliste.pdf\"");
    gnuplot_cmd(g, "set xlabel 'Nombre de bits'");
    gnuplot_cmd(g, "set ylabel 'Rapport Probalilité x Temps de calcule'");
    gnuplot_cmd(g, "set yrange [-0.000005:]");
    gnuplot_cmd(g, "plot \"mesureTemps/mesure.txt\" u 1:6 every 2 title 'fermat' with lines , \"mesureTemps/mesure.txt\" u 1:7 every 4 title 'miller' with lines, \"mesureTemps/mesure.txt\" u 1:8 every 2 title 'strassen' with lines, \"mesureTemps/mesure.txt\" u 1:9 every 2 title 'Frobenius' with lines");
    gnuplot_close(g);
}


void grapheDeterministe(){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal pdfcairo size 10.5,7.86 ");
    gnuplot_cmd(g, "set output \"mesureTemps/deterministe.pdf\"");
    gnuplot_cmd(g, "set xlabel 'Nombre de bits / N'");
    gnuplot_cmd(g, "set ylabel 'temps(seconde)'");
    gnuplot_cmd(g, "set yrange [0:0.003]");
    gnuplot_cmd(g, "plot \"mesureTemps/mesure.txt\" u 1:10 every 2 title 'erastothene' with lines, \"mesureTemps/lucas.txt\" u 1:3 every 2::1 title 'Lucas Lehmer' with lines, \"mesureTemps/pepin.txt\" u 1:3  title 'Pepin' with lines");
    gnuplot_close(g);
}

void grapheErastothene(){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal pdfcairo size 10.5,7.86 ");
    gnuplot_cmd(g, "set output \"mesureTemps/Erastothene.pdf\"");
    gnuplot_cmd(g, "set xlabel 'Nombre de bits'");
    gnuplot_cmd(g, "set ylabel 'temps(seconde)'");
    gnuplot_cmd(g, "plot \"mesureTemps/mesure.txt\" u 1:10 title 'Erastothene' with lines");
    gnuplot_close(g);
}

void grapheLucas(){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal pdfcairo size 10.5,7.86 ");
    gnuplot_cmd(g, "set output \"mesureTemps/lucas.pdf\"");
    gnuplot_cmd(g, "set xlabel 'n impair'");
    gnuplot_cmd(g, "set ylabel 'temps(seconde)'");
    gnuplot_cmd(g, "plot \"mesureTemps/lucas.txt\" u 1:3 every 2::1 title 'Lucas Lehmer' with lines");
    gnuplot_close(g);
}

void graphePepin(){
    gnuplot_ctrl * g = gnuplot_init();
    gnuplot_cmd(g, "set terminal pdfcairo size 10.5,7.86 ");
    gnuplot_cmd(g, "set output \"mesureTemps/pepin.pdf\"");
    gnuplot_cmd(g, "set xlabel 'Nombre de Fermat'");
    gnuplot_cmd(g, "set ylabel 'temps(seconde)'");
    gnuplot_cmd(g, "plot \"mesureTemps/pepin.txt\" u 1:3  title 'Pepin' with lines");
    gnuplot_close(g);
}



int main(int argc, char * argv[])
{
    grapheRapportProbabiliste();
    grapheProbabiliste();
    grapheDeterministe();
    grapheErastothene();
    grapheLucas();
    graphePepin();

    return 0 ;
}
