#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double matrixSum(double **matrix, int M, int N, int T) {
    double temp = 0.0;
    int i, j;
#pragma omp parallel num_threads(T) reduction(+:temp) private(j)
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            temp += matrix[i][j];
        }
    }
    return temp;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <N> <M> <T>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int T = atoi(argv[3]);

    int i, j;
    double sum;
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

    double start_time = omp_get_wtime();

    sum = matrixSum(matrix, M, N, T);

    double end_time = omp_get_wtime();

    printf("Sum: %f\n", sum);
    printf("Time taken: %f seconds\n", end_time - start_time);

    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
