#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int num_steps = 100000000;
    double step;
    int i;
    double x, pi, sum = 0.0;

    step = 1.0/(double)num_steps;

    printf("Execução sequencial: \n");
    double inicio = omp_get_wtime();
    for(i=0;i<num_steps;i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;
    printf("Pi : %.5f \n", pi);
    double fim = omp_get_wtime();
    double tempo = fim - inicio;
    printf("Tempo: %.5f \n", tempo);
    
    printf("Execução em paralelo: \n");
    sum = 0.0;
    pi = 0.0;
    inicio = omp_get_wtime();
    #pragma omp parallel private(x) num_threads(3)
    {
        double x2, sum2=0.0;
        #pragma omp for
            for(i=0;i<num_steps; i++){
                x2 = (i+0.5)*step;
                sum2 = sum2 + 4.0/(1.0+x2*x2);
            }    
        #pragma omp critical
            pi += step * sum2;
    }
    printf("Pi : %.5f \n", pi);
    fim = omp_get_wtime();
    double tempo2 = fim - inicio;
    printf("Tempo: %.5f \n", tempo2);
    double speedup = tempo/tempo2;
    double ef = speedup*100/3;
    printf("Paralelo %.5f vez(es) mais rápido que o sequencial\n", speedup);
    printf("Eficiência: %.5f por cento\n", ef);
    return 0;
}