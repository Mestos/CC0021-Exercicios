#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam 10000000

int *gerar_vetor_binario(int n) {
  int *vetor;
  int i; 
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
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

    int *v = NULL;
    int parte = (int)tam/nprocs;
    int *subv = NULL;

    if(rank==0){
        srand(time(NULL));
        v = gerar_vetor_binario(tam);
    }
    subv = (int*)malloc(sizeof(int) * parte);
    MPI_Scatter(v, parte, MPI_INT, subv, parte, MPI_INT, 0, MPI_COMM_WORLD);

    int count1 = 0;
    int countz = 0;
    int i;
    for(i=0; i<parte; i++){
        if(subv[i] == 0){
            countz++;
        }
        else{
            count1++;
        }
    }

    int *vzero = NULL;
    int *v1 = NULL;
    if(rank==0){
        v1 = (int*)malloc(sizeof(int) * nprocs);
        vzero = (int*)malloc(sizeof(int) * nprocs);
    }
    MPI_Gather(&countz, 1, MPI_INT, vzero, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&count1, 1, MPI_INT, v1, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank==0){
        int umt = 0;
        int zerot = 0;
        for(i=0; i<nprocs; i++){
            umt += v1[i];
            zerot += vzero[i];
        }
        printf("Número de zeros: %d\n", zerot);
        printf("Número de 1: %d\n", umt);
        if(umt % 2 != 0){
            printf("Número de 1 não é par\n");
            v = (int*)realloc(v, sizeof(int) * (tam+1));
            v[tam+1] = 1;
        }
    }


    free(v);
    free(subv);
    free(v1);
    free(vzero);
    v = NULL;
    subv = NULL;
    v1 = NULL;
    vzero = NULL;

    MPI_Finalize();
    return 0;
}