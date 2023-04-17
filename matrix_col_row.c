#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rowMajor(double **matrix, int M, int N, int T) {
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

double colMajor(double **matrix, int M, int N, int T) {
    double temp = 0.0;
    int i, j;
#pragma omp parallel num_threads(T) reduction(+:temp) private(j)
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            temp += matrix[j][i];
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

    int i,j;
    double sum_row_major, sum_col_major;
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

    clock_t start_row_major, end_row_major, start_col_major, end_col_major;

    // Row-major order (contiguous)
    start_row_major = clock();
    sum_row_major = rowMajor(matrix, M, N, T);
    end_row_major = clock();

    // Column-major order (non-contiguous)
    start_col_major = clock();
    sum_col_major = colMajor(matrix, M, N, T);
    end_col_major = clock();

    double row_major_time = (double) (end_row_major - start_row_major) / CLOCKS_PER_SEC;
    double col_major_time = (double) (end_col_major - start_col_major) / CLOCKS_PER_SEC;

    printf("Row-major sum: %f\n", sum_row_major);
    printf("Column-major sum: %f\n", sum_col_major);
    printf("Row-major time: %f seconds in %d threads\n", row_major_time, T);
    printf("Column-major time: %f seconds in %d threads\n", col_major_time, T);

    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
