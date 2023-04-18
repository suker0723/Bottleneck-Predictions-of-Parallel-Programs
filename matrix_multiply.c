#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void initialize_matrix(double **matrix, int matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

void matrix_multiplication(double **A, double **B, double **C, int matrix_size) {
    #pragma omp parallel for
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./matrix_multiplication_openmp MATRIX_SIZE THREAD_NUMBER\n");
        return 1;
    }

    int matrix_size = atoi(argv[1]);
    int thread_number = atoi(argv[2]);

    omp_set_num_threads(thread_number);

    double **A = (double **)malloc(matrix_size * sizeof(double *));
    double **B = (double **)malloc(matrix_size * sizeof(double *));
    double **C = (double **)malloc(matrix_size * sizeof(double *));

    for (int i = 0; i < matrix_size; i++) {
        A[i] = (double *)malloc(matrix_size * sizeof(double));
        B[i] = (double *)malloc(matrix_size * sizeof(double));
        C[i] = (double *)malloc(matrix_size * sizeof(double));
    }

    srand(time(NULL));
    initialize_matrix(A, matrix_size);
    initialize_matrix(B, matrix_size);

    double start_time = omp_get_wtime();
    matrix_multiplication(A, B, C, matrix_size);
    double end_time = omp_get_wtime();

    printf("Matrix multiplication completed in %.4f seconds.\n", end_time - start_time);

    for (int i = 0; i < matrix_size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
