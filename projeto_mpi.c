#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define tam 10000000
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



    MPI_Finalize();
    return 0;
}