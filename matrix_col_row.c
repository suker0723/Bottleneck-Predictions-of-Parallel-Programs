#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <N> <M>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);


    int i, j, sum_row_major = 0, sum_col_major = 0;
    int **matrix;

    matrix = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
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
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            sum_row_major += matrix[i][j];
        }
    }
    end_row_major = clock();

    // Column-major order (non-contiguous)
    start_col_major = clock();
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            sum_col_major += matrix[j][i];
        }
    }
    end_col_major = clock();

    double row_major_time = (double)(end_row_major - start_row_major) / CLOCKS_PER_SEC;
    double col_major_time = (double)(end_col_major - start_col_major) / CLOCKS_PER_SEC;

    printf("Row-major sum: %d\n", sum_row_major);
    printf("Column-major sum: %d\n", sum_col_major);
    printf("Row-major time: %f seconds\n", row_major_time);
    printf("Column-major time: %f seconds\n", col_major_time);

    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
