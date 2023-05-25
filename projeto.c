#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define tam 2000000
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
    int count[max];
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
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
            for(i=0; i<tam; i++){
                #pragma omp critical
                for(j=0; j<max; j++){
                    if (estoque[i] == j){
                        count[j]++;
                    }
                }
            }
    }
    fim = omp_get_wtime();
    for (i=0; i<max; i++){
        printf("Gênero ID %d: %d livros\n", i, count[i]);
    }
    tempo = fim - inicio;
    printf("Tempo de execução: %.5f\n", tempo);



    free(estoque);
    estoque = NULL;
    return 0;
}