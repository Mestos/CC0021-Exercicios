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
    inicio = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel private(x) num_threads(3)
    {
        #pragma omp for reduction (+:sum)
            for(i=0;i<num_steps;i++){
                x = (i+0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }
    }
    pi = step * sum;
    printf("Pi : %.5f \n", pi);
    fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo: %.5f", tempo);
    return 0;
}