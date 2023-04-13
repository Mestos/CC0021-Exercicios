#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define max 1000
#define tam 100000000


int main(){
    srand(time(NULL));
    int *vetor;
    vetor = (int*)malloc(sizeof(int)*tam);
    int i;
    int count = 0;
    double inicio, fim, tempo, tempo1;
    int x;
    printf("Digite um número: \n");
    scanf("%d", &x);

    printf("Execução sequencial: \n");
    for(i=0; i<tam; i++){
        vetor[i] = rand()%max;
    }
    inicio = omp_get_wtime();
    for(i=0; i<tam; i++){
        if(vetor[i] == x){
            count++;
        }
    }
    printf("Seu número apareceu %d vezes \n", count);
    fim = omp_get_wtime();
    count = 0;
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);

    printf("\nExecução em paralelo: \n");
    
 /*   #pragma omp parallel num_threads(3)
    {
        #pragma omp for
            for(i=0; i<tam; i++){
                vetor[i] = rand()%max;
            }
    }*/
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction(+:count)
            for(i=0; i<tam; i++){
                if(vetor[i] == x){
                    count++;
                }
            }
    }
    printf("Seu número apareceu %d vezes \n", count);
    fim = omp_get_wtime();
    free(vetor);
    vetor = NULL;
    tempo1 = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo1);
    double speedup = tempo/tempo1;
    printf("\nSpeedup: %.5f\n", speedup);
    printf("Eficiência: %.5f\n", speedup/3);

    return 0;
}