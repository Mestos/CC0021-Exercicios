#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define tam 150000000
#define max 20

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
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *estoque = NULL;
    int *conjunto = NULL;
    int *count = NULL;
    int *countp = NULL;
    int parte = (int)tam/nprocs;
    int total = 0;
    int i, j;
    double inicio, fim, tempo;

    if(rank == 0){
        srand(time(NULL));
        estoque = gerar_vetor(tam);
        countp = (int*)malloc(sizeof(int) * max);
    }
    count = (int*)malloc(sizeof(int) * max);
    for(i=0; i<max; i++){
        count[i] = 0;
    }
    conjunto = (int*)malloc(sizeof(int) * parte);

    if(rank == 0){
        inicio = MPI_Wtime();
    }
    MPI_Scatter(estoque, parte, MPI_INT, conjunto, parte, MPI_INT, 0, MPI_COMM_WORLD);
    for(i=0; i<parte; i++){   
        for(j=0; j<max; j++){
            if (conjunto[i] == j){
                count[j]++;
            }
        }
    }

    MPI_Reduce(count, countp, max, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        fim = MPI_Wtime();
        for(i=0; i<max; i++){
            printf("Gênero %d: %d \n", i, countp[i]);
            total += countp[i];
        }
        tempo = fim - inicio;
        printf("%d \n", total);
        printf("Tempo: %.5f \n", tempo);
    }


    free(estoque);
    free(conjunto);
    free(count);
    free(countp);
    estoque = NULL;
    count = NULL;
    conjunto = NULL;
    countp = NULL;
    MPI_Finalize();
    return 0;
}