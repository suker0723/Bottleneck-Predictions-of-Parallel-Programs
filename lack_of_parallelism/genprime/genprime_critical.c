#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]){
    int t = atoi(argv[1]);
    long N = 100000000;
    int* is_prime = (int*)malloc((N+1) * sizeof(int));
    // FILE *fp;
    // char filename[100];
    // sprintf(filename, "%d", N);
    // fp = fopen(filename, "w");
    double tstart = 0.0, ttaken;

    // if (fp == NULL) {
    //     printf("Failed to open the file.\n");
    //     return 1;  // Return an error code
    // }

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
            if(is_prime[multiple * divisor] == 1)
             #pragma omp critical
                is_prime[multiple * divisor] = 0;
        }
    }
    ttaken = omp_get_wtime() - tstart;


    // int prime_rank = 1;
    // for(int i = 1; i <= N; i++){
    //     if(!is_prime[i]){
    //         continue;
    //     }
    //     char result[100];
    //     sprintf(result, "%d %d\n", prime_rank, i);
    //     fputs(result,fp);
    //     prime_rank++;
    // }
    
    // fclose(fp);
    printf("Time take for the main part: %f\n", ttaken);

    return 0;

}