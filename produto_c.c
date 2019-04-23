#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Para executar em Linux:
// gcc produto_c.c -o produto_c
// ./produto_c num_linhas num_colunas

int main(int argc,char *argv[]){

    if (argc != 3 || atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
        printf("Formato: ./produto num_linhas num_colunas \n");
    }

    double **matriz;

    matriz = (double **)malloc(atoi(argv[1])*sizeof(double));
    for (int j=0; j<atoi(argv[1]);j++) {
        matriz[j] = (double*)malloc(atoi(argv[2])*sizeof(double));
    }

    double *vetor = (double*)malloc(atoi(argv[2])*sizeof(double));
    double *resultado = (double*)malloc(atoi(argv[1])*sizeof(double));
    srand(time(NULL));

    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Construindo a matriz de valores aleatorios
    for (int i=0; i<atoi(argv[1]); i++){
        for (int j=0; j<atoi(argv[2]); j=j+1){
            matriz[i][j]=rand()/1000.0;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Construcao da matriz completa\n");
    printf("Tempo de execucao: %f\n\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Construindo o vetor de numeros aleatorios
    for (int i=0; i<atoi(argv[2]); i++){
        vetor[i]=rand()/1000.0;
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Construcao do vetor completa\n");
    printf("Tempo de execucao: %f\n\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Calculando produto em linha
    for (int i=0; i<atoi(argv[1]); i++){
        resultado[i]=0.0;
        for (int j=0; j<atoi(argv[2]); j++){
            resultado[i]=resultado[i]+matriz[i][j]*vetor[j];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Calculo por linha finalizado com sucesso\n");
    printf("Tempo de execucao em segundos: %f\n\n", elapsed);

    // Retornado o vetor de resultados a 0
    for (int i=0; i<atoi(argv[1]); i++){
        resultado[i]=0.0;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Calculando o produto em coluna
    for (int j=0; j<atoi(argv[2]); j++){
        for (int i=0; i<atoi(argv[1]); i++){
            resultado[i]=resultado[i]+matriz[i][j]*vetor[j];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Calculo por coluna finalizado com sucesso\n");
    printf("Tempo de execucao em segundos: %f\n", elapsed);

    return 0;
}
