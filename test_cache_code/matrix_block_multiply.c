#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define matrix_size 512

void initialize_matrix(double **matrix, int block_size) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

void matrix_multiplication(double **A, double **B, double **C, int block_size) {
    #pragma omp parallel for collapse(2)
    for (int ii = 0; ii < matrix_size; ii += block_size) {
        for (int jj = 0; jj < matrix_size; jj += block_size) {
            for (int kk = 0; kk < matrix_size; kk += block_size) {
                for (int i = ii; i < ii + block_size; i++) {
                    for (int j = jj; j < jj + block_size; j++) {
                        for (int k = kk; k < kk + block_size; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./matrix_multiplication_openmp BLOCK_SIZE THREAD_NUMBER\n");
        return 1;
    }

    int block_size = atoi(argv[1]);
    int thread_number = atoi(argv[2]);

    omp_set_num_threads(thread_number);

    double **A = (double **)malloc(matrix_size * sizeof(double *));
    double **B = (double **)malloc(matrix_size * sizeof(double *));
    double **C = (double **)malloc(matrix_size * sizeof(double *));

    for (int i = 0; i < matrix_size; i++) {
        A[i] = (double *)malloc(matrix_size * sizeof(double));
        B[i] = (double *)malloc(matrix_size * sizeof(double));
        C[i] = (double *)calloc(matrix_size, sizeof(double));
    }

    srand(time(NULL));
    initialize_matrix(A, matrix_size);
    initialize_matrix(B, matrix_size);

    double start_time = omp_get_wtime();
    matrix_multiplication(A, B, C, block_size);
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
