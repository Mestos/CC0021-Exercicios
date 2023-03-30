#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define max 500000000

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int main(){
    float *vetor = gerar_vetor(max);
    float n = 0.3578;
    int k;
    printf("Execução sequencial: \n");
    double inicio = omp_get_wtime();
    for (k=0;k<max;k++){
        if(vetor[k] == n){
            printf("Achou \n");
        }
    }
    double fim = omp_get_wtime();
    double tempos = fim - inicio;
    printf("Tempo de execução: %.5f \n", tempos);

    printf("\nExecução em paralelo: \n");
    double iniciop = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
            for (k=0;k<max;k++){
                if(vetor[k] == n){
                    printf("Achou \n");
                }
            }
    }
    double fimp = omp_get_wtime();
    double temposp = fimp - iniciop;
    printf("Tempo de execução: %.5f \n", temposp);
    printf("\nParalelo %.5f vez(es) mais rápido que sequencial\n", tempos/temposp);
    return 0;
}