#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define tam 100000000

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int main(){
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float *v;
    float soma = 0;
    int i;
    if(rank == 0){
        v = gerar_vetor(tam);
        MPI_Bcast(v, tam, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Recv(&soma, 1, MPI_FLOAT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Soma 1: %.5f\n", soma);
        MPI_Recv(&soma, 1, MPI_FLOAT, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Soma 2: %.5f\n", soma);
    }
    else{
        v = (float *)malloc(sizeof(float) * tam);
        MPI_Bcast(v, tam, MPI_FLOAT, 0, MPI_COMM_WORLD);
        if(rank == 1){
            for(i=0; i<tam; i++){
                soma += v[i];
            }
            MPI_Send(&soma, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
        }
        if(rank == 2){
            for(i=0; i<tam; i++){
                soma += 2*v[i];
            }
            MPI_Send(&soma, 1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
        }
    }
    free(v);
    v = NULL;
    MPI_Finalize();
    return 0;
}