#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Usage: ./genprime_atomic THREAD_NUMBER\n");
        return 1;
    }
    
    int t = atoi(argv[1]);
    long N = 100000000;
    int* is_prime = (int*)malloc((N+1) * sizeof(int));
    double tstart = 0.0, ttaken;

    for(int i = 0; i <= N; i++){
        is_prime[i] = 1;
    }
    is_prime[1] = 0;

    tstart = omp_get_wtime(); 
    long max_divisor = floor((N + 1)/ 2);
    long divisor;
    #pragma omp parallel for num_threads(t) private(divisor) schedule(static,1)
    for(divisor = 2; divisor <= max_divisor; divisor++){
        if(!is_prime[divisor]){
            continue;
        }
        long max_multiple = floor(N/divisor);
        for(long multiple = 2; multiple <= max_multiple; multiple++){
            if(is_prime[multiple * divisor] == 1){
                #pragma omp atomic write
                is_prime[multiple * divisor] = 0;
            }
        }
    }
    ttaken = omp_get_wtime() - tstart;
    printf("Time take for the main part: %f\n", ttaken);

    return 0;

}