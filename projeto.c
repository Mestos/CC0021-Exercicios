#include <stdio.h>
#include <mpi.h>
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
    int count[tam];
    int i;
    int j;
    for (i=0; i<tam; i++){
        count[i] = 0;
    }
    for(i=0; i<tam; i++){
        for(j=0; j<max; j++){
            if (estoque[i] == j){
                count[j]++;
            }
        }
    }
    for (i=0; i<max; i++){
        printf("Gênero ID %d: %d livros\n", i, count[i]);
    }


    free(estoque);
    estoque = NULL;
    return 0;
}