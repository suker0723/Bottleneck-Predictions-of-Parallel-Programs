#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double blockSum(double **matrix, int M, int N, int BLOCK_SIZE) {
    double sum_block = 0.0;
    int i, j;

#pragma omp parallel for private(j) reduction(+:sum_block)
    for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < M; bj += BLOCK_SIZE) {
            for (i = bi; i < bi + BLOCK_SIZE && i < N; i++) {
                for (j = bj; j < bj + BLOCK_SIZE && j < M; j++) {
                    sum_block += matrix[j][i];
                }
            }
        }
    }

    return sum_block;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage: %s <N> <M> <block_size>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int BLOCK_SIZE = atoi(argv[3]);

    int i, j;
    double sum_block;
    double **matrix;

    matrix = (double **) malloc(N * sizeof(double *));
    for (i = 0; i < N; i++) {
        matrix[i] = (double *) malloc(M * sizeof(double));
    }

    srand(time(NULL));
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    double start_block, end_block;

    // Block partitioning
    start_block = omp_get_wtime();

    sum_block = blockSum(matrix, M, N, BLOCK_SIZE);

    end_block = omp_get_wtime();

    double block_time = end_block - start_block;

    printf("Block sum: %f\n", sum_block);
    printf("Block time: %f seconds\n", block_time);

    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
