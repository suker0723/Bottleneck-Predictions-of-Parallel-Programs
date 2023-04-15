#include <omp.h>
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

    int i, j, sum = 0;
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

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) private(j)
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            // Accessing elements in a non-contiguous manner to cause cache misses
            sum += matrix[j][i];
        }
    }

    double end_time = omp_get_wtime();

    printf("Sum: %d\n", sum);
    printf("Time taken: %f seconds\n", end_time - start_time);

    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
