#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int t = atoi(argv[1]);
    unsigned long long N = 10000000;

    unsigned long long i;
    long double sum = 0;
    double tstart = 0.0, ttaken;

    double* arr = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }
    tstart = omp_get_wtime();
    #pragma omp parallel for num_threads(t)
    for (i = 0; i < N; i++) {
        #pragma omp critical
        sum += arr[i];
    }
    ttaken = omp_get_wtime() - tstart;

    printf("Time take for the main part: %f\n", ttaken);
    printf("Sum: %Lf\n", sum);

    return 0;
}