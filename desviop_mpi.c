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
    double *somas = NULL;
    double u = 0;
    double su = 0;
    int i;
    int parte = tam/nprocs;
    int *vet = NULL;
    int *subvet = NULL;

    if(rank==0){
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
        su += somas1[i];
    }
    u = su/tam;
    for(i=0; i<parte; i++){
        soma += (subvet[i] - u) * (subvet[i] - u);
    }
    if(rank == 0){
        somas = (double *)malloc(sizeof(double) * (nprocs));
    }
    MPI_Gather(&soma, 1, MPI_DOUBLE, somas, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(rank == 0){
        double desviop;
        double stotal = 0;
        for(i=0; i<nprocs; i++){
            stotal += somas[i];
        }
        desviop = pow((stotal/tam), 0.5);
        printf("Desvio padrão: %.5f \n", desviop);
    }


    free(vet);
    free(subvet);
    free(somas);
    free(somas1);
    vet = NULL;
    subvet = NULL;
    somas = NULL;
    somas1 = NULL;
    MPI_Finalize();
    return 0;
}
