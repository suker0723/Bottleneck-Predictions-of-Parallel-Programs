#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int t = atoi(argv[1]);
    unsigned long long N = atoi(argv[2]);

    unsigned long long i;
    long double sum = 0.0;
    double tstart = 0.0, ttaken;

    double* arr = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    tstart = omp_get_wtime();
    #pragma omp parallel for num_threads(t) reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += arr[i];
    }
    ttaken = omp_get_wtime() - tstart;

    printf("Time take for the main part: %f\n", ttaken);
    printf("Sum: %Lf\n", sum);

    return 0;
}