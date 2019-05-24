#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Para executar em Linux:
// gcc produto_c.c -o produto_c -fopenmp
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

    int i_matriz;
    int j_matriz;

    // Construindo a matriz de valores aleatorios
    #pragma omp parallel for num_threads(4) private(i_matriz,j_matriz) shared(matriz)
    for (int i_matriz = 0; i_matriz<atoi(argv[1]); i_matriz++){
        for (int j_matriz = 0; j_matriz<atoi(argv[2]); j_matriz=j_matriz+1){
            matriz[i_matriz][j_matriz]=rand()/1000.0;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Construcao da matriz completa\n");
    printf("Tempo de execucao: %f\n\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);

    int i_vetor;

    // Construindo o vetor de numeros aleatorios
    #pragma omp parallel for num_threads(4) private(i_vetor) shared(vetor)
    for (int i_vetor=0; i_vetor<atoi(argv[2]); i_vetor++){
        vetor[i_vetor]=rand()/1000.0;
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Construcao do vetor completa\n");
    printf("Tempo de execucao: %f\n\n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);

    int i_linha;
    int j_linha;

    // Calculando produto em linha
    #pragma omp parallel for num_threads(4) private(i_linha, j_linha) shared(resultado)
    for (int i_linha=0; i_linha<atoi(argv[1]); i_linha++){
        resultado[i_linha]=0.0;
        for (int j_linha=0; j_linha<atoi(argv[2]); j_linha++){
            resultado[i_linha]=resultado[i_linha]+matriz[i_linha][j_linha]*vetor[j_linha];
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

    int i_coluna;
    int j_coluna;

    // Calculando o produto em coluna
    #pragma omp parallel for num_threads(4) private(i_coluna, j_coluna) shared(resultado)
    for (int j_coluna=0; j_coluna<atoi(argv[2]); j_coluna++){
        for (int i_coluna=0; i_coluna<atoi(argv[1]); i_coluna++){
            resultado[i_coluna]=resultado[i_coluna]+matriz[i_coluna][j_coluna]*vetor[j_coluna];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Calculo por coluna finalizado com sucesso\n");
    printf("Tempo de execucao em segundos: %f\n", elapsed);

    return 0;
}
