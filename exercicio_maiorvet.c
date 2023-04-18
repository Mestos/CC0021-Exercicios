#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define max 10000000
#define tam 100000

int main(){
    srand(time(NULL));
    int vet[tam];
    int i;
    int maior;
    int indice = 0;
    int maiores[3];
    double inicio, fim, tempo, tempo1;
    for(i=0;i<tam;i++){
        vet[i] = rand()%max;
    }
    maior = vet[0];
    printf("Execução sequencial:\n");
    inicio = omp_get_wtime();
    for(i=0;i<tam;i++){
        if(vet[i]> maior){
            maior = vet[i];
            indice = i;
        }
    }
    printf("Maior valor do vetor: %d\n", maior);
    printf("Índice: %d\n", indice);
    fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);
    indice = 0;
    maior = vet[0];
    int maior1;

    printf("\nExecução em paralelo:\n");
    inicio = omp_get_wtime();
    #pragma omp parallel firstprivate(maior) num_threads(3)
    {
        #pragma omp for
            for(i=0;i<tam;i++){
                if(vet[i]> maior){
                    maior = vet[i];
                    maiores[omp_get_thread_num()] = maior;
                }
            }
        for(i=1; i<4;i++){
            if(i == 1){
                maior1 = maiores[i];
            }
            else if(maiores[i]> maior1){
                maior1 = maiores[i];
            }
        }   
    }
    printf("Maior valor do vetor: %d\n", maior1);
    printf("Índice: %d\n", indice);
    fim = omp_get_wtime();
    tempo1 = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo1);

    return 0;
}