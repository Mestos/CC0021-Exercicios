#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define tam 1000
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
    int total = 0;
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
        total += count[i];
    }
    printf("%d \n", total);
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);

    for (i=0; i<max; i++){
        count[i] = 0;
    }
    total = 0;

    printf("\nExecução em paralelo:\n");
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        int *c = (int*)malloc(sizeof(int) * max);
        for(i=0; i<max; i++){
            c[i] = 0;
        }
        #pragma omp for
            for(i=0; i<tam; i++){
                for(j=0; j<max; j++){
                    if (estoque[i] == j){
                        c[j]++;
                    }
                }
            }

        #pragma omp critical
            for(i=0; i<max; i++){
                count[i] += c[i];
            }
        free(c);
        c = NULL;
    }
    fim = omp_get_wtime();
    for (i=0; i<max; i++){
        printf("Gênero ID %d: %d livros\n", i, count[i]);
        total += count[i];
    }
    printf("%d \n", total);
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);



    free(estoque);
    free(count);
    estoque = NULL;
    count = NULL;
    return 0;
}