#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage: %s <N> <M> <Block_Size>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int BLOCK_SIZE = atoi(argv[3]);
    int i, j, sum_block = 0;
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

    clock_t start_block, end_block;

    // Block partitioning
    start_block = clock();
    for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < M; bj += BLOCK_SIZE) {
            for (i = bi; i < bi + BLOCK_SIZE && i < N; i++) {
                for (j = bj; j < bj + BLOCK_SIZE && j < M; j++) {
                    sum_block += matrix[j][i];
                }
            }
        }
    }
    end_block = clock();

    double block_time = (double)(end_block - start_block) / CLOCKS_PER_SEC;

    printf("Block sum: %d\n", sum_block);
    printf("Block time: %f seconds\n", block_time);

    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

