#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void tarefa1(int x){
    int i;
    for(i=0; i<x; i++){
        printf("(%d) - (%d) \n", omp_get_thread_num(), i);
    }
}

void tarefa2(int x, int y){
    printf("(%d) - (%d) \n", omp_get_thread_num(), x + y);
}

int main(){
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                tarefa1(10);

            #pragma omp section
                tarefa2(20,30);
        }
    }
    return 0;
}