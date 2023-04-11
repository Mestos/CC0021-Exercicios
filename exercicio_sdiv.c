#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define max 100000000

int main(){
    int i;
    long int soma = 0;

    printf("Execução sequencial: \n");
    double inicio = omp_get_wtime();
    for(i=1; i<=max; i++){
        if(max%i == 0){
            soma = soma + i;
        }
    }
    printf("Soma dos divisores: %d\n", soma);
    double fim = omp_get_wtime();
    double tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);
    soma = 0;

    printf("\nExecução paralela estática pelo reduction: \n");
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:soma)
            for(i=1; i<=max; i++){
                if(max%i == 0){
                    soma = soma + i;
                }
            }
    }
    printf("Soma dos divisores: %d\n", soma);
    fim = omp_get_wtime();
    double tempo1 = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo1);
    soma = 0;

    printf("\nExecução paralela estática pelo critical: \n");
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        int aux = 0;
        #pragma omp for
            for(i=1; i<=max; i++){
                if(max%i == 0){
                    aux = aux + i;
                }
            }
            #pragma omp critical
                soma = soma + aux;
    }
    printf("Soma dos divisores: %d\n", soma);
    fim = omp_get_wtime();
    double tempo2 = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo2);
    soma = 0;

    printf("\nExecução paralela dinâmica com reduction: \n");
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for schedule(dynamic) reduction (+:soma)
            for(i=1; i<=max; i++){
                if(max%i == 0){
                    soma = soma + i;
                }
            }
    }
    printf("Soma dos divisores: %d\n", soma);
    fim = omp_get_wtime();
    double tempo3 = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo3);

    double speedup = tempo/tempo1;
    double speedup1 = tempo/tempo2;
    double speedup2 = tempo/tempo3;
    printf("\nParalelo com reduction %.5f vez(es) mais rápido que o sequencial\n", speedup);
    printf("Paralelo com critical %.5f vez(es) mais rápido que o sequencial\n", speedup1);
    printf("Paralelo dinâmico com reduction %.5f vez(es) mais rápido que o sequencial\n", speedup2);

    return 0;
}