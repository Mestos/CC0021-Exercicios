#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define max 1000
#define tam 100000

int main(){
    srand(time(NULL))
    int vet[tam];
    int i;
    double soma = 0;
    double desviop;
    double u, inicio, fim, tempo;
    scanf("%f", &u);
    for(i=0 ; i<tam; i++){
        vet[i] = rand()%max;
    }
    printf("Execução sequencial: \n");
    inicio = omp_get_wtime();
    for(i=0; i<tam; i++){
        soma += (vet[i] - u)**2;
    }
    desviop = (soma/tam)**0.5;
    printf("Desvio padrão: %.5f \n", desviop);
    fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f \n", tempo);

    soma = 0;
    desviop =0;
    printf("\nExecução em paralelo: \n");
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction(+:soma)
            for(i=0; i<tam; i++){
                soma += (vet[i] - u)**2;
            }
    }
    desviop = (soma/tam)**0.5;
    printf("Desvio padrão: %.5f \n", desviop);
    fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f \n", tempo);


    return 0;
}