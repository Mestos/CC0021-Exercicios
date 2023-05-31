#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define tam 1000000
#define max 10

int *gerar_vetor(int x){
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * x);
    for (i=0;i<x;i++) {
        int id = rand()%max;
        vetor[i] = id;
    }
    return vetor;
}

int main(){
    srand(time(NULL));
    int *estoque = gerar_vetor(tam);
    int *count = (int*)malloc(sizeof(int) * max);
    int i;
    int j;
    double inicio,tempo, fim;
    for (i=0; i<max; i++){
        count[i] = 0;
    }
    inicio = omp_get_wtime();
    for(i=0; i<tam; i++){
        for(j=0; j<max; j++){
            if (estoque[i] == j){
                count[j]++;
            }
        }
    }
    fim = omp_get_wtime();
    for (i=0; i<max; i++){
        printf("Gênero ID %d: %d livros\n", i, count[i]);
    }
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);
    for (i=0; i<max; i++){
        count[i] = 0;
    }
    printf("\nExecução em paralelo:\n");
    inicio = omp_get_wtime();
    #pragma omp parallel firstprivate(count) num_threads(3)
    {
        #pragma omp for
            for(i=0; i<tam; i++){
                for(j=0; j<max; j++){
                    if (estoque[i] == j){
                        count[j]++;
                    }
                }
            }

        #pragma omp critical
        printf("Thread %d \n", omp_get_thread_num());
        for(i=0; i<max; i++){
            printf("%d: %d \n", i, count[i]);
        }

        free(count);
        count = NULL;
    }
    fim = omp_get_wtime();
   /* for (i=0; i<max; i++){
        printf("Gênero ID %d: %d livros\n", i, total[i]);
    } */
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);



    free(estoque);
    free(count);
    estoque = NULL;
    count = NULL;
    return 0;
}