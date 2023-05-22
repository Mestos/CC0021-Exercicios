#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

#define tam 1000000
#define max 1000

int *gerar_vetor(int x){
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * x);
    for(i=0; i<x; i++){
        vetor[i] = rand()%max;
    }
    return vetor;
}

int main(){
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double soma = 0;
    double soma1 = 0;
    double *somas1 = NULL;
    double u = 0;
    int i;
    int parte = 250000;
    int *vet = NULL;
    int *subvet = NULL;

    if(rank==0){
        double *somas;
        double desviop = 0;
        somas = (double *)malloc(sizeof(double) * (nprocs));
        srand(time(NULL));
        vet = gerar_vetor(tam);
    }
    subvet = (int *)malloc(sizeof(int) * parte);
    MPI_Scatter(vet, parte, MPI_INT, subvet, parte, MPI_INT, 0, MPI_COMM_WORLD);
    for(i=0; i<parte; i++){
        soma1 += subvet[i];
    }
    somas1 = (double *)malloc(sizeof(double) * (nprocs));
    MPI_Allgather(&soma1, 1, MPI_DOUBLE, somas1, nprocs, MPI_DOUBLE, MPI_COMM_WORLD);
    for(i=0; i<nprocs; i++){
        u += somas1[i];
    }


    free(vet);
    vet = NULL;
    MPI_Finalize();
    return 0;
}
